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

#include "GuitarController.h"

GuitarController::GuitarController(NXC_I2C_TYPE& i2cBus) : ExtensionController(i2cBus, NXC_GuitarController, 6) {}
GuitarController::GuitarController(ExtensionData& busData) : ExtensionController(busData, NXC_GuitarController, 6) {}

uint8_t GuitarController::joyX() const {
	return decodeControlByte(NXC_CTRLBYTE_CLASSIC_LEFTJOYX);
}

uint8_t GuitarController::joyY() const {
	return decodeControlByte(NXC_CTRLBYTE_CLASSIC_LEFTJOYY);
}

boolean GuitarController::strum() const {
	return strumUp() | strumDown();
}

boolean GuitarController::strumUp() const {
	return getControlBit(NXC_CTRLBIT_GUITAR_STRUMUP);
}

boolean GuitarController::strumDown() const {
	return getControlBit(NXC_CTRLBIT_GUITAR_STRUMDOWN);
}

boolean GuitarController::fretGreen() const {
	return getControlBit(NXC_CTRLBIT_GUITAR_GREEN);
}

boolean GuitarController::fretRed() const {
	return getControlBit(NXC_CTRLBIT_GUITAR_RED);
}

boolean GuitarController::fretYellow() const {
	return getControlBit(NXC_CTRLBIT_GUITAR_YELLOW);
}

boolean GuitarController::fretBlue() const {
	return getControlBit(NXC_CTRLBIT_GUITAR_BLUE);
}

boolean GuitarController::fretOrange() const {
	return getControlBit(NXC_CTRLBIT_GUITAR_ORANGE);
}

uint8_t GuitarController::whammyBar() const {
	return decodeControlByte(NXC_CTRLBYTE_GUITAR_WHAMMY);
}

uint8_t GuitarController::touchbar() const {
	return decodeControlByte(NXC_CTRLBYTE_GUITAR_TOUCHBAR);
}

boolean GuitarController::touchGreen() const {
	return touchbar() != 0 && touchbar() <= 7;
}

boolean GuitarController::touchRed() const {
	return touchbar() >= 7 && touchbar() <= 13;
}

boolean GuitarController::touchYellow() const {
	return touchbar() >= 12 && touchbar() <= 21
		&& touchbar() != 15;	// The "not touched" value
}

boolean GuitarController::touchBlue() const {
	return touchbar() >= 20 && touchbar() <= 26;
}

boolean GuitarController::touchOrange() const {
	return touchbar() >= 26;
}

boolean GuitarController::buttonPlus() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_PLUS);
}

boolean GuitarController::buttonMinus() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_MINUS);
}

void GuitarController::joyX(uint8_t dataIn) {
	setControlData(dataIn, NXC_CTRLBYTE_CLASSIC_LEFTJOYX);
}

void GuitarController::joyY(uint8_t dataIn) {
	setControlData(dataIn, NXC_CTRLBYTE_CLASSIC_LEFTJOYY);
}

void GuitarController::strumUp(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_GUITAR_STRUMUP);
}

void GuitarController::strumDown(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_GUITAR_STRUMDOWN);
}

void GuitarController::fretGreen(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_GUITAR_GREEN);
}

void GuitarController::fretRed(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_GUITAR_RED);
}

void GuitarController::fretYellow(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_GUITAR_YELLOW);
}

void GuitarController::fretBlue(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_GUITAR_BLUE);
}

void GuitarController::fretOrange(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_GUITAR_ORANGE);
}

void GuitarController::whammyBar(uint8_t dataIn) {
	setControlData(dataIn, NXC_CTRLBYTE_GUITAR_WHAMMY);
}

void GuitarController::touchbar(uint8_t dataIn) {
	setControlData(dataIn, NXC_CTRLBYTE_GUITAR_TOUCHBAR);
}

void GuitarController::buttonPlus(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_CLASSIC_PLUS);
}

void GuitarController::buttonMinus(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_CLASSIC_MINUS);
}

boolean GuitarController::supportsTouchbar() {
	if (touchbarData) {
		return true;
	}
	else if (touchbar() != 31) {  // '1' for all data bits
		touchbarData = true;
	}
	return false;
}

void GuitarController::printDebug(Stream& stream) {
	const char fillCharacter = '_';

	char buffer[25];

	stream.print("Guitar: ");

	// Strum + Fret Buttons
	char strumPrint = fillCharacter;
	if (strumUp()) {
		strumPrint = '^';
	}
	else if (strumDown()) {  // Mutually exclusive
		strumPrint = 'v';
	}

	char greenPrint = fretGreen() ? 'G' : fillCharacter;
	char redPrint = fretRed() ? 'R' : fillCharacter;
	char yellowPrint = fretYellow() ? 'Y' : fillCharacter;
	char bluePrint = fretBlue() ? 'B' : fillCharacter;
	char orangePrint = fretOrange() ? 'O' : fillCharacter;

	sprintf(buffer,
		"%c | %c%c%c%c%c | W:%2u ",
		strumPrint,
		greenPrint, redPrint, yellowPrint, bluePrint, orangePrint,
		whammyBar());
	stream.print(buffer);
	buffer[0] = 0;

	// Touchbar, if World Controller
	if (supportsTouchbar()) {
		greenPrint = touchGreen() ? 'G' : fillCharacter;
		redPrint = touchRed() ? 'R' : fillCharacter;
		yellowPrint = touchYellow() ? 'Y' : fillCharacter;
		bluePrint = touchBlue() ? 'B' : fillCharacter;
		orangePrint = touchOrange() ? 'O' : fillCharacter;

		sprintf(buffer,
			"Touch:%2u - %c%c%c%c%c | ",
			touchbar(),
			greenPrint, redPrint, yellowPrint, bluePrint, orangePrint);
		stream.print(buffer);
		buffer[0] = 0;
	}

	// Joy + Plus/Minus
	char plusPrint = buttonPlus() ? '+' : fillCharacter;
	char minusPrint = buttonMinus() ? '-' : fillCharacter;

	sprintf(buffer,
		"%c%c | Joy:(%2u, %2u)",
		minusPrint, plusPrint,
		joyX(), joyY());
	stream.println(buffer);
}
