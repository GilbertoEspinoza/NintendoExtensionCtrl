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

#include "DJTurntable.h"

typedef NintendoExtensionCtrl::ControlByteMap ControlByteMap;
typedef NintendoExtensionCtrl::ControlBitMap  ControlBitMap;

constexpr static ControlByteMap DJTurntableController::NXC_CTRLBYTE_DJ_EFFECT[2];
constexpr static ControlByteMap DJTurntableController::NXC_CTRLBYTE_DJ_CROSSFADE;

constexpr static ControlBitMap  DJTurntableController::NXC_CTRLBIT_DJ_EUPHORIA;

constexpr static ControlByteMap DJTurntableController::TurntableLeft::NXC_CTRLBYTE_DJ_LEFT_TURNTABLE;
constexpr static ControlByteMap DJTurntableController::TurntableLeft::NXC_CTRLBYTE_DJ_LEFT_TURNTABLE_SIGN;
constexpr static ControlBitMap  DJTurntableController::TurntableLeft::NXC_CTRLBIT_DJ_LEFT_GREEN;
constexpr static ControlBitMap  DJTurntableController::TurntableLeft::NXC_CTRLBIT_DJ_LEFT_RED;
constexpr static ControlBitMap  DJTurntableController::TurntableLeft::NXC_CTRLBIT_DJ_LEFT_BLUE;

constexpr static ControlByteMap DJTurntableController::TurntableRight::NXC_CTRLBYTE_DJ_RIGHT_TURNTABLE[3];
constexpr static ControlByteMap DJTurntableController::TurntableRight::NXC_CTRLBYTE_DJ_RIGHT_TURNTABLE_SIGN;
constexpr static ControlBitMap  DJTurntableController::TurntableRight::NXC_CTRLBIT_DJ_RIGHT_GREEN;
constexpr static ControlBitMap  DJTurntableController::TurntableRight::NXC_CTRLBIT_DJ_RIGHT_RED;
constexpr static ControlBitMap  DJTurntableController::TurntableRight::NXC_CTRLBIT_DJ_RIGHT_BLUE;

DJTurntableController::DJTurntableController(NXC_I2C_TYPE& i2cBus) : ExtensionController(i2cBus, NXC_DJTurntable, 6), left(*this), right(*this) {}
DJTurntableController::DJTurntableController(ExtensionData& busData) : ExtensionController(busData, NXC_DJTurntable, 6), left(*this), right(*this) {}

// Combined Turntable
int8_t DJTurntableController::turntable() const {
	return left.turntable() + right.turntable();
}

boolean DJTurntableController::buttonGreen() const {
	return left.buttonGreen() | right.buttonGreen();
}

boolean DJTurntableController::buttonRed() const {
	return left.buttonRed() | right.buttonRed();
}

boolean DJTurntableController::buttonBlue() const {
	return left.buttonBlue() | right.buttonBlue();
}

// Main Board
uint8_t DJTurntableController::effectDial() const {
	return decodeControlByte(NXC_CTRLBYTE_DJ_EFFECT);
}

int8_t DJTurntableController::crossfadeSlider() const {
	return (int8_t) decodeControlByte(NXC_CTRLBYTE_DJ_CROSSFADE) + CrossfadeOffset;  // Shifted to signed int
}

boolean DJTurntableController::buttonEuphoria() const {
	return getControlBit(NXC_CTRLBIT_DJ_EUPHORIA);
}

uint8_t DJTurntableController::joyX() const {
	return decodeControlByte(ClassicController::NXC_CTRLBYTE_CLASSIC_LEFTJOYX);
}

uint8_t DJTurntableController::joyY() const {
	return decodeControlByte(ClassicController::NXC_CTRLBYTE_CLASSIC_LEFTJOYY);
}

boolean DJTurntableController::buttonPlus() const {
	return getControlBit(ClassicController::NXC_CTRLBIT_CLASSIC_PLUS);
}

boolean DJTurntableController::buttonMinus() const {
	return getControlBit(ClassicController::NXC_CTRLBIT_CLASSIC_MINUS);
}

void DJTurntableController::effectDial(uint8_t dataIn) {
	setControlData(dataIn, NXC_CTRLBYTE_DJ_EFFECT);
}

void DJTurntableController::crossfadeSlider(int8_t dataIn) {
	if (dataIn < CrossfadeOffset) { dataIn = CrossfadeOffset; }  // Keep in range
	dataIn -= CrossfadeOffset;  // Remove the offset
	setControlData((uint8_t) dataIn, NXC_CTRLBYTE_DJ_CROSSFADE);
}

void DJTurntableController::buttonEuphoria(boolean bitIn) {
	setControlBit(bitIn, NXC_CTRLBIT_DJ_EUPHORIA);
}

void DJTurntableController::joyX(uint8_t dataIn) {
	setControlData(dataIn, ClassicController::NXC_CTRLBYTE_CLASSIC_LEFTJOYX);
}

void DJTurntableController::joyY(uint8_t dataIn) {
	setControlData(dataIn, ClassicController::NXC_CTRLBYTE_CLASSIC_LEFTJOYY);
}

void DJTurntableController::buttonPlus(boolean bitIn) {
	setControlBit(bitIn, ClassicController::NXC_CTRLBIT_CLASSIC_PLUS);
}

void DJTurntableController::buttonMinus(boolean bitIn) {
	setControlBit(bitIn, ClassicController::NXC_CTRLBIT_CLASSIC_MINUS);
}

NXC_DJTurntable_Configuration DJTurntableController::getTurntableConfig() {
	if (tableConfig == NXC_DJTurntable_Both) {
		return tableConfig;  // Both are attached, no reason to check data
	}

	boolean leftState = left.connected();
	boolean rightState = right.connected();

	if (leftState && rightState) {
		return tableConfig = NXC_DJTurntable_Both;
	}
	else if (leftState) {
		return tableConfig = NXC_DJTurntable_Left;
	}
	else if (rightState) {
		return tableConfig = NXC_DJTurntable_Right;
	}
	else {
		return tableConfig = NXC_DJTurntable_BaseOnly;
	}
}

uint8_t DJTurntableController::getNumTurntables() {
	getTurntableConfig();  // Update config from data

	switch (tableConfig) {
		case NXC_DJTurntable_BaseOnly:
			return 0;
			break;
		case NXC_DJTurntable_Left:
		case NXC_DJTurntable_Right:
			return 1;
			break;
		case NXC_DJTurntable_Both:
			return 2;
			break;
	}
	return 0;  // Just in-case
}

void DJTurntableController::printDebug(Stream& stream) {
	const char fillCharacter = '_';

	char buffer[45];

	stream.print("DJ:");

	if (getNumTurntables() == 0) {
		stream.print(" No turntable found! |");
	}
	else if (left.connected()) {
		printTurntable(stream, left);
		stream.print(" |");
	}

	char plusPrint = buttonPlus() ? '+' : fillCharacter;
	char minusPrint = buttonMinus() ? '-' : fillCharacter;

	char euphoriaPrint = buttonEuphoria() ? 'E' : fillCharacter;

	sprintf(buffer,
		" Joy:(%2u, %2u) | %c | %c%c | FX: %2u | Fade: %2d",
		joyX(), joyY(),
		euphoriaPrint,
		minusPrint, plusPrint,
		effectDial(), crossfadeSlider());
	stream.print(buffer);

	if (right.connected()) {
		stream.print(" |");
		printTurntable(stream, right);
	}
	stream.println();
}

void DJTurntableController::printTurntable(Stream& stream, TurntableExpansion &table) const {
	const char fillCharacter = '_';

	char idPrint = 'X';
	if (table.side == NXC_DJTurntable_Left) {
		idPrint = 'L';
	}
	else if (table.side == NXC_DJTurntable_Right) {
		idPrint = 'R';
	}

	char greenPrint = table.buttonGreen() ? 'G' : fillCharacter;
	char redPrint = table.buttonRed() ? 'R' : fillCharacter;
	char bluePrint = table.buttonBlue() ? 'B' : fillCharacter;

	char buffer[15];
	sprintf(buffer,
		" T%c:%3d %c%c%c",
		idPrint,
		table.turntable(),
		greenPrint, redPrint, bluePrint);
	stream.print(buffer);
}

// Turntable Expansion Base
boolean DJTurntableController::TurntableExpansion::connected() const {
	if (base.tableConfig == NXC_DJTurntable_Both || base.tableConfig == side) {
		return true;  // Already checked
	}
	return turntable() != 0 || buttonGreen() || buttonRed() || buttonBlue();
}

int8_t DJTurntableController::TurntableExpansion::tableSignConversion(int8_t turnData) const {
	if (turnData & 0x80) {  // If sign bit is 1...
		turnData |= 0x60;  // Flip missing bits to '1's
	}
	return turnData;
}

// Left Turntable
int8_t DJTurntableController::TurntableLeft::turntable() const {
	int8_t turnData = (int8_t) base.decodeControlByte(NXC_CTRLBYTE_DJ_LEFT_TURNTABLE);
	turnData |= base.decodeControlByte(NXC_CTRLBYTE_DJ_LEFT_TURNTABLE_SIGN) << 7;  // Sign bit

	return tableSignConversion(turnData);
}

boolean DJTurntableController::TurntableLeft::buttonGreen() const {
	return base.getControlBit(NXC_CTRLBIT_DJ_LEFT_GREEN);
}

boolean DJTurntableController::TurntableLeft::buttonRed() const {
	return base.getControlBit(NXC_CTRLBIT_DJ_LEFT_RED);
}

boolean DJTurntableController::TurntableLeft::buttonBlue() const {
	return base.getControlBit(NXC_CTRLBIT_DJ_LEFT_BLUE);
}

void DJTurntableController::TurntableLeft::turntable(int8_t dataIn) {
	base.setControlData(dataIn, NXC_CTRLBYTE_DJ_LEFT_TURNTABLE);
	base.setControlData(dataIn >> 7, NXC_CTRLBYTE_DJ_LEFT_TURNTABLE_SIGN);
}

void DJTurntableController::TurntableLeft::buttonGreen(boolean bitIn) {
	base.setControlBit(bitIn, NXC_CTRLBIT_DJ_LEFT_GREEN);
}

void DJTurntableController::TurntableLeft::buttonRed(boolean bitIn) {
	base.setControlBit(bitIn, NXC_CTRLBIT_DJ_LEFT_RED);
}

void DJTurntableController::TurntableLeft::buttonBlue(boolean bitIn) {
	base.setControlBit(bitIn, NXC_CTRLBIT_DJ_LEFT_BLUE);
}

// Right Turntable
int8_t DJTurntableController::TurntableRight::turntable() const {
	int8_t turnData = (int8_t) base.decodeControlByte(NXC_CTRLBYTE_DJ_RIGHT_TURNTABLE);
	turnData |= base.decodeControlByte(NXC_CTRLBYTE_DJ_RIGHT_TURNTABLE_SIGN) << 7;  // Sign bit

	return tableSignConversion(turnData);
}

boolean DJTurntableController::TurntableRight::buttonGreen() const {
	return base.getControlBit(NXC_CTRLBIT_DJ_RIGHT_GREEN);
}

boolean DJTurntableController::TurntableRight::buttonRed() const {
	return base.getControlBit(NXC_CTRLBIT_DJ_RIGHT_RED);
}

boolean DJTurntableController::TurntableRight::buttonBlue() const {
	return base.getControlBit(NXC_CTRLBIT_DJ_RIGHT_BLUE);
}

void DJTurntableController::TurntableRight::turntable(int8_t dataIn) {
	base.setControlData(dataIn, NXC_CTRLBYTE_DJ_RIGHT_TURNTABLE);
	base.setControlData(dataIn >> 7, NXC_CTRLBYTE_DJ_RIGHT_TURNTABLE_SIGN);
}

void DJTurntableController::TurntableRight::buttonGreen(boolean bitIn) {
	base.setControlBit(bitIn, NXC_CTRLBIT_DJ_RIGHT_GREEN);
}

void DJTurntableController::TurntableRight::buttonRed(boolean bitIn) {
	base.setControlBit(bitIn, NXC_CTRLBIT_DJ_RIGHT_RED);
}

void DJTurntableController::TurntableRight::buttonBlue(boolean bitIn) {
	base.setControlBit(bitIn, NXC_CTRLBIT_DJ_RIGHT_BLUE);
}

// Effect Rollover
int8_t DJTurntableController::EffectRollover::getChange() {
	return RolloverChange::getChange(dj.effectDial());
}
