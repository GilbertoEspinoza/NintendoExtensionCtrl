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

#include "DrumController.h"

DrumController::DrumController(NXC_I2C_TYPE& i2cBus) : ExtensionController(i2cBus, NXC_DrumController, 6) {}
DrumController::DrumController(ExtensionData& busData) : ExtensionController(busData, NXC_DrumController, 6) {}

uint8_t DrumController::joyX() const {
	return decodeControlByte(NXC_CTRLBYTE_CLASSIC_LEFTJOYX);
}

uint8_t DrumController::joyY() const {
	return decodeControlByte(NXC_CTRLBYTE_CLASSIC_LEFTJOYY);
}

boolean DrumController::drumRed() const {
	return getControlBit(NXC_CTRLBIT_DRUMS_RED);
}

boolean DrumController::drumBlue() const {
	return getControlBit(NXC_CTRLBIT_DRUMS_BLUE);
}

boolean DrumController::drumGreen() const {
	return getControlBit(NXC_CTRLBIT_DRUMS_GREEN);
}

boolean DrumController::cymbalYellow() const {
	return getControlBit(NXC_CTRLBIT_DRUMS_YELLOW);
}

boolean DrumController::cymbalOrange() const {
	return getControlBit(NXC_CTRLBIT_DRUMS_ORANGE);
}

boolean DrumController::bassPedal() const {
	return getControlBit(NXC_CTRLBIT_DRUMS_PEDAL);
}

boolean DrumController::buttonPlus() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_PLUS);
}

boolean DrumController::buttonMinus() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_MINUS);
}

boolean DrumController::velocityAvailable() const {
	return getControlBit(NXC_CTRLBIT_DRUMS_VELOCITY_AVAILABLE);
}

NXC_DrumVelocityID DrumController::velocityID() const {
	uint8_t velocityID = decodeControlByte(NXC_CTRLBYTE_DRUMS_VELOCITY_ID);  // 5 bit identifier

	if (validVelocityID(velocityID)) {
		return (NXC_DrumVelocityID) velocityID;
	}

	return NXC_Drum_None;
}

boolean DrumController::validVelocityID(uint8_t idIn) const {
	switch (idIn) {
		case(NXC_Drum_None):  // Intentionally fall through cases
		case(NXC_Drum_Red):
		case(NXC_Drum_Blue):
		case(NXC_Drum_Green):
		case(NXC_Drum_Yellow):
		case(NXC_Drum_Orange):
		case(NXC_Drum_Pedal):
			return true;  // One of the above, is a valid ID
			break;
		default:
			return false;  // Not one of the above, invalid
	}
}

uint8_t DrumController::velocity() const {
	if (velocityAvailable()) {
		uint8_t velocityRaw = decodeControlByte(NXC_CTRLBYTE_DRUMS_VELOCITY);
		velocityRaw = 7 - velocityRaw;  // Invert so high = fast attack
		return velocityRaw;
	}
	return 0;  // Invalid data
}

uint8_t DrumController::velocity(NXC_DrumVelocityID idIn) const {
	if (idIn == velocityID()) {
		return velocity();
	}
	return 0;  // ID mismatch
}

uint8_t DrumController::velocityRed() const {
	return velocity(NXC_Drum_Red);
}

uint8_t DrumController::velocityBlue() const {
	return velocity(NXC_Drum_Blue);
}

uint8_t DrumController::velocityGreen() const {
	return velocity(NXC_Drum_Green);
}

uint8_t DrumController::velocityYellow() const {
	return velocity(NXC_Drum_Yellow);
}

uint8_t DrumController::velocityOrange() const {
	return velocity(NXC_Drum_Orange);
}

uint8_t DrumController::velocityPedal() const {
	return velocity(NXC_Drum_Pedal);  // Fix this
}

void DrumController::joyX(uint8_t dataIn) {
	setControlData(dataIn, NXC_CTRLBYTE_CLASSIC_LEFTJOYX);
}

void DrumController::joyY(uint8_t dataIn) {
	setControlData(dataIn, NXC_CTRLBYTE_CLASSIC_LEFTJOYY);
}

void DrumController::drumRed(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_DRUMS_RED);
}

void DrumController::drumBlue(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_DRUMS_BLUE);
}

void DrumController::drumGreen(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_DRUMS_GREEN);
}

void DrumController::cymbalYellow(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_DRUMS_YELLOW);
}

void DrumController::cymbalOrange(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_DRUMS_ORANGE);
}

void DrumController::bassPedal(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_DRUMS_PEDAL);
}

void DrumController::buttonPlus(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_CLASSIC_PLUS);
}

void DrumController::buttonMinus(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_CLASSIC_MINUS);
}

void DrumController::velocity(uint8_t dataIn, NXC_DrumVelocityID idIn) {
	if (dataIn > 7) { dataIn = 7; }  // Keep in range
	dataIn = 7 - dataIn;  // Re-invert, so hard is low again (matching expected data)
	setControlBit(idIn != NXC_Drum_None, NXC_CTRLBIT_DRUMS_VELOCITY_AVAILABLE);
	setControlData(idIn, NXC_CTRLBYTE_DRUMS_VELOCITY_ID);
	setControlData(dataIn, NXC_CTRLBYTE_DRUMS_VELOCITY);
}

void DrumController::printDebug(Stream& stream) const {
	const char fillCharacter = '_';
	
	char buffer[45];
	
	stream.print("Drums: ");

	char redPrint = drumRed() ? 'R' : fillCharacter;
	char bluePrint = drumBlue() ? 'B' : fillCharacter;
	char greenPrint = drumGreen() ? 'G' : fillCharacter;

	char yellowPrint = cymbalYellow() ? 'Y' : fillCharacter;
	char orangePrint = cymbalOrange() ? 'O' : fillCharacter;

	char pedalPrint = bassPedal() ? 'P' : fillCharacter;

	uint8_t velocityPrint = 0;
	char velocityIDPrint = fillCharacter;

	if (velocityAvailable()) {
		velocityPrint = velocity();

		switch (velocityID()) {
			case (NXC_Drum_None):
				break;  // Keep as fillCharacter
			case(NXC_Drum_Red):
				velocityIDPrint = 'R';
				break;
			case(NXC_Drum_Blue):
				velocityIDPrint = 'B';
				break;
			case(NXC_Drum_Green):
				velocityIDPrint = 'G';
				break;
			case(NXC_Drum_Yellow):
				velocityIDPrint = 'Y';
				break;
			case(NXC_Drum_Orange):
				velocityIDPrint = 'O';
				break;
			case(NXC_Drum_Pedal):
				velocityIDPrint = 'P';
				break;
		}
	}

	char plusPrint = buttonPlus() ? '+' : fillCharacter;
	char minusPrint = buttonMinus() ? '-' : fillCharacter;

	sprintf(buffer,
		"%c\\%c%c%c/%c %c | V:%1u for %c | %c%c | Joy:(%2u, %2u)",
		yellowPrint, redPrint, bluePrint, greenPrint, orangePrint, pedalPrint,
		velocityPrint, velocityIDPrint,
		minusPrint, plusPrint,
		joyX(), joyY());
	stream.println(buffer);
}
