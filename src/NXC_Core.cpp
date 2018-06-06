/*
*  Project     Nintendo Extension Controller Library
*  @author     David Madison
*  @link       github.com/dmadison/NintendoExtensionCtrl
*  @license    LGPLv3 - Copyright (c) 2018 David Madison
*
*  This file is part of the Nintendo Extension Controller Library.
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU Lesser General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "NXC_Core.h"

namespace NintendoExtensionCtrl {

	boolean requestIdentity(NXC_I2C_TYPE& i2c, uint8_t * idData) {
		const uint8_t IDPointer = 0xFA;
		ExtensionComms comms(i2c);

		return comms.readDataArray(IDPointer, IDHeaderSize, idData);
	}

	NXC_ControllerType identifyController(const uint8_t * idData) {
		if (idData[2] == 0xA4 && idData[3] == 0x20) {  // All valid IDs
			// Nunchuk ID: 0x0000
			if (idData[4] == 0x00 && idData[5] == 0x00) {
				return NXC_Nunchuk;
			}

			// Classic Con. ID: 0x0101
			else if (idData[4] == 0x01 && idData[5] == 0x01) {
				return NXC_ClassicController;
			}

			// Guitar Hero Controllers: 0x##00, 0xA420, 0x0103
			else if (idData[1] == 0x00
				&& idData[4] == 0x01 && idData[5] == 0x03) {

				// Guitar: 0x00
				if (idData[0] == 0x00) {
					return NXC_GuitarController;
				}
				// Drums: 0x01
				else if (idData[0] == 0x01) {
					return NXC_DrumController;
				}
				// DJ Turntable: 0x03
				else if (idData[0] == 0x03) {
					return NXC_DJTurntable;
				}
			}
		}

		return NXC_UnknownController;  // No matches
	}

	NXC_ControllerType identifyController(NXC_I2C_TYPE& i2c) {
		uint8_t idData[IDHeaderSize];

		if (!requestIdentity(i2c, idData)) {
			return NXC_NoController;  // Bad response from device
		}
		return identifyController(idData);
	}

	boolean verifyData(const uint8_t * dataIn, uint8_t dataSize) {
		byte orCheck = 0x00;   // Check if data is zeroed (bad connection)
		byte andCheck = 0xFF;  // Check if data is maxed (bad init)

		for (int i = 0; i < dataSize; i++) {
			orCheck |= dataIn[i];
			andCheck &= dataIn[i];
		}

		if (orCheck == 0x00 || andCheck == 0xFF) {
			return false;  // No data or bad data
		}

		return true;
	}

	void printRaw(const uint8_t * dataIn, uint8_t dataSize, uint8_t baseFormat, Stream& stream) {
		char padChar = ' ';
		if (baseFormat == BIN || baseFormat == HEX) {
			padChar = '0';
		}

		// Calculate max # of spaces for the base
		uint8_t maxInput = 0xFF;
		uint8_t maxNPlaces = 0;
		while (maxInput != 0) {
			maxInput /= baseFormat;
			maxNPlaces++;
		}

		for (int i = 0; i < dataSize; i++) {
			uint8_t dataOut = dataIn[i];

			if (baseFormat == HEX) {
				stream.print("0x");  // Hex prefix
			}

			// Calculate # of spaces that will be printed. Max - n = # to pad.
			uint8_t nPlaces = 0;
			uint8_t tempOut = dataOut;
			do {
				tempOut /= baseFormat;
				nPlaces++;
			} while (tempOut != 0);


			// Print pad characters
			for (int padOut = 0; padOut < (maxNPlaces - nPlaces); padOut++) {
				stream.print(padChar);
			}

			stream.print(dataOut, baseFormat);

			if (i != dataSize - 1) {  // Print separators
				stream.print(" | ");
			}
		}
		stream.println();
	}

	void printRaw(uint8_t dataIn, uint8_t baseFormat, Stream& stream) {
		printRaw(&dataIn, 1, baseFormat, stream);
	}

	void printRepeat(char c, uint8_t nPrint, Stream& stream) {
		for (int i = 0; i < nPrint; i++) {
			stream.print(c);
		}
	}

	RolloverChange::RolloverChange(uint8_t min, uint8_t max) :
		minValue(min), maxValue(max) {}

	int8_t RolloverChange::getChange(uint8_t valIn) {
		if (valIn == lastValue ||
			valIn < minValue || valIn > maxValue) {
			return 0;  // No change, or out of range
		}

		int8_t outValue = 0;
		if (abs(valIn - lastValue) >= halfRange()){  // Assume rollover
			// Rollover, going up
			if (valIn < lastValue) {
				outValue = rolloverOut(valIn, lastValue);
			}
			// Rollover, going down
			else if (valIn > lastValue) {
				outValue = -rolloverOut(lastValue, valIn);
			}
		}
		else {  // Normal change
			outValue = valIn - lastValue;
		}

		lastValue = valIn;  // Store current value for comparison next time
		return outValue;
	}

	int8_t RolloverChange::rolloverOut(uint8_t c1, uint8_t c2) const {
		return (maxValue - c2) + c1 + 1;
	}

	uint8_t RolloverChange::halfRange() const {
		return ((maxValue - minValue) / 2) + 1;
	}
}

