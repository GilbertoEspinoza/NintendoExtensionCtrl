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

#include "Nunchuk.h"

Nunchuk::Nunchuk(NXC_I2C_TYPE& i2cBus) : ExtensionController(i2cBus, NXC_Nunchuk, 6) {}
Nunchuk::Nunchuk(ExtensionData& busData) : ExtensionController(busData, NXC_Nunchuk, 6) {}

uint8_t Nunchuk::joyX() const {
	return getControlData(NXC_CTRLBYTE_NUNCHUK_JOYX);
}

uint8_t Nunchuk::joyY() const {
	return getControlData(NXC_CTRLBYTE_NUNCHUK_JOYY);
}

uint16_t Nunchuk::accelX() const {
	return decodeAccelData(NXC_CTRLBYTE_NUNCHUK_ACCELX);
}

uint16_t Nunchuk::accelY() const {
	return decodeAccelData(NXC_CTRLBYTE_NUNCHUK_ACCELY);
}

uint16_t Nunchuk::accelZ() const {
	return decodeAccelData(NXC_CTRLBYTE_NUNCHUK_ACCELZ);
}

boolean Nunchuk::buttonC() const {
	return getControlBit(NXC_CTRLBIT_NUNCHUK_C);
}

boolean Nunchuk::buttonZ() const {
	return getControlBit(NXC_CTRLBIT_NUNCHUK_Z);
}

void Nunchuk::joyX(uint8_t dataIn) {
	setControlData(dataIn, NXC_CTRLBYTE_NUNCHUK_JOYX);
}

void Nunchuk::joyY(uint8_t dataIn) {
	setControlData(dataIn, NXC_CTRLBYTE_NUNCHUK_JOYY);
}

void Nunchuk::accelX(uint16_t dataIn) {
	setAccelControlData(dataIn, NXC_CTRLBYTE_NUNCHUK_ACCELX);
}

void Nunchuk::accelY(uint16_t dataIn) {
	setAccelControlData(dataIn, NXC_CTRLBYTE_NUNCHUK_ACCELY);
}

void Nunchuk::accelZ(uint16_t dataIn) {
	setAccelControlData(dataIn, NXC_CTRLBYTE_NUNCHUK_ACCELZ);
}

void Nunchuk::buttonC(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_NUNCHUK_C);
}

void Nunchuk::buttonZ(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_NUNCHUK_Z);
}

float Nunchuk::rollAngle() const {
	return atan2((float)accelX() - 511.0, (float)accelZ() - 511.0) * 180.0 / PI;
}

float Nunchuk::pitchAngle() const {
	// Inverted so pulling back is a positive pitch
	return -atan2((float)accelY() - 511.0, (float)accelZ() - 511.0) * 180.0 / PI;
}

void Nunchuk::printDebug(Stream& stream) const {
	char buffer[60];

	char cPrint = buttonC() ? 'C' : '-';
	char zPrint = buttonZ() ? 'Z' : '-';

	stream.print("Nunchuk - ");
	sprintf(buffer,
		"Joy:(%3u, %3u) | Accel XYZ:(%4u, %4u, %4u) | Buttons: %c%c",
		joyX(), joyY(), accelX(), accelY(), accelZ(), cPrint, zPrint);
	
	stream.println(buffer);
}
