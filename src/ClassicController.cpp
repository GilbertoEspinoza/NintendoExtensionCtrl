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

#include "ClassicController.h"

ClassicController::ClassicController(NXC_I2C_TYPE& i2cBus) : ExtensionController(i2cBus, NXC_ClassicController, 6) {}
ClassicController::ClassicController(ExtensionData& busData) : ExtensionController(busData, NXC_ClassicController, 6) {}

uint8_t ClassicController::leftJoyX() const {
	return decodeControlByte(NXC_CTRLBYTE_CLASSIC_LEFTJOYX);
}

uint8_t ClassicController::leftJoyY() const {
	return decodeControlByte(NXC_CTRLBYTE_CLASSIC_LEFTJOYY);
}

uint8_t ClassicController::rightJoyX() const {
	return decodeControlByte(NXC_CTRLBYTE_CLASSIC_RIGHTJOYX);
}

uint8_t ClassicController::rightJoyY() const {
	return decodeControlByte(NXC_CTRLBYTE_CLASSIC_RIGHTJOYY);
}

boolean ClassicController::dpadUp() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_DPADUP);
}

boolean ClassicController::dpadDown() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_DPADDOWN);
}

boolean ClassicController::dpadLeft() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_DPADLEFT);
}

boolean ClassicController::dpadRight() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_DPADRIGHT);
}

boolean ClassicController::buttonA() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_A);
}

boolean ClassicController::buttonB() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_B);
}

boolean ClassicController::buttonX() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_X);
}

boolean ClassicController::buttonY() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_Y);
}

uint8_t ClassicController::triggerL() const {
	return decodeControlByte(NXC_CTRLBYTE_CLASSIC_TRIGGERL);
}

uint8_t ClassicController::triggerR() const {
	return decodeControlByte(NXC_CTRLBYTE_CLASSIC_TRIGGERR);
}

boolean ClassicController::buttonL() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_L);
}

boolean ClassicController::buttonR() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_R);
}

boolean ClassicController::buttonZL() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_ZL);
}

boolean ClassicController::buttonZR() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_ZR);
}

boolean ClassicController::buttonStart() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_PLUS);
}

boolean ClassicController::buttonSelect() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_MINUS);
}

boolean ClassicController::buttonPlus() const {
	return buttonStart();
}

boolean ClassicController::buttonMinus() const {
	return buttonSelect();
}

boolean ClassicController::buttonHome() const {
	return getControlBit(NXC_CTRLBIT_CLASSIC_HOME);
}

void ClassicController::printDebug(Stream& stream) const {
	const char fillCharacter = '_';

	char buffer[62];

	char dpadLPrint = dpadLeft() ? '<' : fillCharacter;
	char dpadUPrint = dpadUp() ? '^' : fillCharacter;
	char dpadDPrint = dpadDown() ? 'v' : fillCharacter;
	char dpadRPrint = dpadRight() ? '>' : fillCharacter;

	char aButtonPrint = buttonA() ? 'A' : fillCharacter;
	char bButtonPrint = buttonB() ? 'B' : fillCharacter;
	char xButtonPrint = buttonX() ? 'X' : fillCharacter;
	char yButtonPrint = buttonY() ? 'Y' : fillCharacter;

	char plusPrint = buttonPlus() ? '+' : fillCharacter;
	char minusPrint = buttonMinus() ? '-' : fillCharacter;
	char homePrint = buttonHome() ? 'H' : fillCharacter;

	char ltButtonPrint = buttonL() ? 'X' : fillCharacter;
	char rtButtonPrint = buttonR() ? 'X' : fillCharacter;

	char zlButtonPrint = buttonZL() ? 'L' : fillCharacter;
	char zrButtonPrint = buttonZR() ? 'R' : fillCharacter;

	stream.print("Classic ");
	sprintf(buffer,
		"%c%c%c%c | %c%c%c | %c%c%c%c L:(%2u, %2u) R:(%2u, %2u) | LT:%2u%c RT:%2u%c Z:%c%c",
		dpadLPrint, dpadUPrint, dpadDPrint, dpadRPrint,
		minusPrint, homePrint, plusPrint,
		aButtonPrint, bButtonPrint, xButtonPrint, yButtonPrint,
		leftJoyX(), leftJoyY(), rightJoyX(), rightJoyY(),
		triggerL(), ltButtonPrint, triggerR(), rtButtonPrint,
		zlButtonPrint, zrButtonPrint);
	stream.println(buffer);
}
