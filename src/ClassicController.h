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

#ifndef NXC_ClassicController_h
#define NXC_ClassicController_h

#include "ExtensionController.h"

class ClassicController : public ExtensionController {
public:
	ClassicController(NXC_I2C_TYPE& i2cBus = NXC_I2C_DEFAULT);
	ClassicController(ExtensionData& busData);

	uint8_t leftJoyX() const;  // 6 bits, 0-63
	uint8_t leftJoyY() const;

	uint8_t rightJoyX() const;  // 5 bits, 0-31
	uint8_t rightJoyY() const;

	boolean dpadUp() const;
	boolean dpadDown() const;
	boolean dpadLeft() const;
	boolean dpadRight() const;

	boolean buttonA() const;
	boolean buttonB() const;
	boolean buttonX() const;
	boolean buttonY() const;

	uint8_t triggerL() const;  // 5 bits, 0-31
	uint8_t triggerR() const;

	boolean buttonL() const;
	boolean buttonR() const;

	boolean buttonZL() const;
	boolean buttonZR() const;

	boolean buttonStart() const;
	boolean buttonSelect() const;

	boolean buttonPlus() const;
	boolean buttonMinus() const;

	boolean buttonHome() const;

	void leftJoyX(uint8_t dataIn);
	void leftJoyY(uint8_t dataIn);

	void rightJoyX(uint8_t dataIn);
	void rightJoyY(uint8_t dataIn);

	void dpadUp(boolean bitIn);
	void dpadDown(boolean bitIn);
	void dpadLeft(boolean bitIn);
	void dpadRight(boolean bitIn);

	void buttonA(boolean bitIn);
	void buttonB(boolean bitIn);
	void buttonX(boolean bitIn);
	void buttonY(boolean bitIn);

	void triggerL(uint8_t dataIn);
	void triggerR(uint8_t dataIn);

	void buttonL(boolean bitIn);
	void buttonR(boolean bitIn);

	void buttonZL(boolean bitIn);
	void buttonZR(boolean bitIn);

	void buttonStart(boolean bitIn);
	void buttonSelect(boolean bitIn);

	void buttonPlus(boolean bitIn);
	void buttonMinus(boolean bitIn);

	void buttonHome(boolean bitIn);

	void printDebug(Stream& stream=NXC_SERIAL_DEFAULT) const;

	// Control Data Mappings
	typedef NintendoExtensionCtrl::ControlByteMap ControlByteMap;
	typedef NintendoExtensionCtrl::ControlBitMap  ControlBitMap;

	constexpr static ControlByteMap NXC_CTRLBYTE_CLASSIC_LEFTJOYX = ControlByteMap(0, 6, 0, 0);
	constexpr static ControlByteMap NXC_CTRLBYTE_CLASSIC_LEFTJOYY = ControlByteMap(1, 6, 0, 0);

	constexpr static ControlByteMap NXC_CTRLBYTE_CLASSIC_RIGHTJOYX[3] = { ControlByteMap(0, 2, 6, 3),  ControlByteMap(1, 2, 6, 5),  ControlByteMap(2, 1, 7, 7) };
	constexpr static ControlByteMap NXC_CTRLBYTE_CLASSIC_RIGHTJOYY = ControlByteMap(2, 5, 0, 0);

	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_DPADUP = { 5, 0 };
	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_DPADDOWN = { 4, 6 };
	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_DPADLEFT = { 5, 1 };
	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_DPADRIGHT = { 4, 7 };

	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_A = { 5, 4 };
	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_B = { 5, 6 };
	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_X = { 5, 3 };
	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_Y = { 5, 5 };

	constexpr static ControlByteMap NXC_CTRLBYTE_CLASSIC_TRIGGERL[2] = { ControlByteMap(2, 2, 5, 2),  ControlByteMap(3, 3, 5, 5) };
	constexpr static ControlByteMap NXC_CTRLBYTE_CLASSIC_TRIGGERR = ControlByteMap(3, 5, 0, 0);

	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_L = { 4, 5 };
	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_R = { 4, 1 };
	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_ZL = { 5, 7 };
	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_ZR = { 5, 2 };

	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_PLUS = { 4, 2 };
	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_MINUS = { 4, 4 };
	constexpr static ControlBitMap  NXC_CTRLBIT_CLASSIC_HOME = { 4, 3 };
};

#endif
