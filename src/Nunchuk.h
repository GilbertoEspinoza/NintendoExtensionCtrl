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

#define NXC_CTRLBYTE_NUNCHUK_JOYX 0
#define NXC_CTRLBYTE_NUNCHUK_JOYY 1

#define NXC_CTRLBYTE_NUNCHUK_ACCELX 2,  5, 2, 2, 2
#define NXC_CTRLBYTE_NUNCHUK_ACCELY 3,  5, 2, 4, 4
#define NXC_CTRLBYTE_NUNCHUK_ACCELZ 4,  5, 2, 6, 6

#define NXC_CTRLBIT_NUNCHUK_C 5, 1
#define NXC_CTRLBIT_NUNCHUK_Z 5, 0

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
	uint16_t decodeAccelData(uint8_t indx1, uint8_t indx2, uint8_t size2, uint8_t pos2, uint8_t shift2) const {
		return (uint16_t)getControlData(indx1) << 2 |
			NXCtrl::sliceByte(getControlData(indx2), size2, pos2, shift2);
	}

	void setAccelControlData(uint16_t newData, uint8_t indx1, uint8_t indx2, uint8_t size2, uint8_t pos2, uint8_t shift2) {
		setControlData((uint8_t) ((newData >> 2) & 0xFF), indx1);
		setControlData((uint8_t) (newData & 0xFF), indx2, size2, pos2, shift2);
	}
};

#endif
