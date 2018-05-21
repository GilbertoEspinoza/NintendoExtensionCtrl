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

#ifndef NXC_Nunchuk_h
#define NXC_Nunchuk_h

#include "ExtensionController.h"

namespace NintendoExtensionCtrl {
	struct AccelControlMap {
		ControlIndex msb;    // Index in the control data array, MSB (8:2)
		uint8_t offset;      // Offset for the high byte (shifted left)
		ControlByteMap lsb;  // Map for the LSB (1:0)
	};
}

constexpr static NintendoExtensionCtrl::ControlIndex NXC_CTRLBYTE_NUNCHUK_JOYX = { 0 };
constexpr static NintendoExtensionCtrl::ControlIndex NXC_CTRLBYTE_NUNCHUK_JOYY = { 1 };

constexpr static NintendoExtensionCtrl::AccelControlMap NXC_CTRLBYTE_NUNCHUK_ACCELX = { 2, 2,  5, 2, 2, 2 };
constexpr static NintendoExtensionCtrl::AccelControlMap NXC_CTRLBYTE_NUNCHUK_ACCELY = { 3, 2,  5, 2, 4, 4 };
constexpr static NintendoExtensionCtrl::AccelControlMap NXC_CTRLBYTE_NUNCHUK_ACCELZ = { 4, 2,  5, 2, 6, 6 };

constexpr static NintendoExtensionCtrl::ControlBitMap  NXC_CTRLBIT_NUNCHUK_C = { 5, 1 };
constexpr static NintendoExtensionCtrl::ControlBitMap  NXC_CTRLBIT_NUNCHUK_Z = { 5, 0 };

class Nunchuk : public ExtensionController {
public:
	Nunchuk(NXC_I2C_TYPE& i2cBus = NXC_I2C_DEFAULT);
	Nunchuk(ExtensionData& busData);

	uint8_t joyX() const;  // 8 bits, 0-255
	uint8_t joyY() const;

	uint16_t accelX() const;  // 10 bits, 0-1023
	uint16_t accelY() const;
	uint16_t accelZ() const;

	boolean buttonC() const;
	boolean buttonZ() const;

	void joyX(uint8_t dataIn);
	void joyY(uint8_t dataIn);

	void accelX(uint16_t dataIn);
	void accelY(uint16_t dataIn);
	void accelZ(uint16_t dataIn);

	void buttonC(boolean bitIn);
	void buttonZ(boolean bitIn);

	float rollAngle() const;  // -180.0 to 180.0
	float pitchAngle() const;

	void printDebug(Stream& stream=NXC_SERIAL_DEFAULT) const;

protected:
	uint16_t decodeAccelData(const NintendoExtensionCtrl::AccelControlMap map) const {
		return (uint16_t)getControlData(map.msb) << map.offset |
			NXCtrl::sliceByte(getControlData(map.lsb.index), map.lsb.size, map.lsb.position, map.lsb.offset);
	}

	void setAccelControlData(uint16_t newData, const NintendoExtensionCtrl::AccelControlMap map) {
		setControlData((uint8_t) ((newData >> map.offset) & 0xFF), map.msb);
		setControlData((uint8_t)(newData & 0xFF), map.lsb);
	}
};

#endif
