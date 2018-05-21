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

#ifndef NXC_DJTurntable_h
#define NXC_DJTurntable_h

#include "ExtensionController.h"
#include "ClassicController.h"  // For joy and +/- byte defines

constexpr static NintendoExtensionCtrl::ControlByteMap NXC_CTRLBYTE_DJ_LEFT_TURNTABLE = { 3, 5, 0, 0 };
constexpr static NintendoExtensionCtrl::ControlByteMap NXC_CTRLBYTE_DJ_LEFT_TURNTABLE_SIGN = { 4, 1, 0, 0 };
constexpr static NintendoExtensionCtrl::ControlBitMap  NXC_CTRLBIT_DJ_LEFT_GREEN = { 5, 3 };
constexpr static NintendoExtensionCtrl::ControlBitMap  NXC_CTRLBIT_DJ_LEFT_RED = { 4, 5 };
constexpr static NintendoExtensionCtrl::ControlBitMap  NXC_CTRLBIT_DJ_LEFT_BLUE = { 5, 7 };

constexpr static NintendoExtensionCtrl::ControlByteMap NXC_CTRLBYTE_DJ_RIGHT_TURNTABLE[3] = { 0, 2, 6, 3,  1, 2, 6, 5,  2, 1, 7, 7 };
constexpr static NintendoExtensionCtrl::ControlByteMap NXC_CTRLBYTE_DJ_RIGHT_TURNTABLE_SIGN = { 2, 1, 0, 0 };
constexpr static NintendoExtensionCtrl::ControlBitMap  NXC_CTRLBIT_DJ_RIGHT_GREEN = { 5, 5 };
constexpr static NintendoExtensionCtrl::ControlBitMap  NXC_CTRLBIT_DJ_RIGHT_RED = { 4, 1 };
constexpr static NintendoExtensionCtrl::ControlBitMap  NXC_CTRLBIT_DJ_RIGHT_BLUE = { 5, 2 };

constexpr static NintendoExtensionCtrl::ControlByteMap NXC_CTRLBYTE_DJ_EFFECT[2] = { 2, 2, 5, 2,  3, 3, 5, 5 };
constexpr static NintendoExtensionCtrl::ControlByteMap NXC_CTRLBYTE_DJ_CROSSFADE = { 2, 4, 1, 1 };

constexpr static NintendoExtensionCtrl::ControlBitMap  NXC_CTRLBIT_DJ_EUPHORIA = { 5, 4 };

enum NXC_DJTurntable_Configuration {
	NXC_DJTurntable_BaseOnly,
	NXC_DJTurntable_Left,
	NXC_DJTurntable_Right,
	NXC_DJTurntable_Both,
};

class DJTurntableController : public ExtensionController {
public:
	DJTurntableController(NXC_I2C_TYPE& i2cBus = NXC_I2C_DEFAULT);
	DJTurntableController(ExtensionData& busData);

	int8_t turntable() const;  // 6 bits, -30-29. Clockwise = positive, faster = larger.

	boolean buttonGreen() const;
	boolean buttonRed() const;
	boolean buttonBlue() const;

	uint8_t effectDial() const;  // 5 bits, 0-31. One rotation per rollover.
	int8_t crossfadeSlider() const;  // 4 bits, -8-7. Negative to the left.
	
	boolean buttonEuphoria() const;

	uint8_t joyX() const;  // 6 bits, 0-63
	uint8_t joyY() const;

	boolean buttonPlus() const;
	boolean buttonMinus() const;

	void effectDial(uint8_t dataIn);
	void crossfadeSlider(int8_t dataIn);

	void buttonEuphoria(boolean bitIn);

	void joyX(uint8_t dataIn);
	void joyY(uint8_t dataIn);

	void buttonPlus(boolean bitIn);
	void buttonMinus(boolean bitIn);

	void printDebug(Stream& stream=NXC_SERIAL_DEFAULT);

	NXC_DJTurntable_Configuration getTurntableConfig();
	uint8_t getNumTurntables();

	class TurntableExpansion {
	public:
		TurntableExpansion(NXC_DJTurntable_Configuration conf, DJTurntableController &baseObj)
			: side(conf), base(baseObj) {}
		boolean connected() const;

		virtual int8_t turntable() const = 0;

		virtual boolean buttonGreen() const = 0;
		virtual boolean buttonRed() const = 0;
		virtual boolean buttonBlue() const = 0;

		virtual void turntable(int8_t dataIn) = 0;

		virtual void buttonGreen(boolean bitIn) = 0;
		virtual void buttonRed(boolean bitIn) = 0;
		virtual void buttonBlue(boolean bitIn) = 0;

		const NXC_DJTurntable_Configuration side = NXC_DJTurntable_BaseOnly;
	protected:
		int8_t tableSignConversion(int8_t turnData) const;
		DJTurntableController & base;
	};

	class TurntableLeft : public TurntableExpansion {
	public:
		TurntableLeft(DJTurntableController &baseObj)
			: TurntableExpansion(NXC_DJTurntable_Left, baseObj) {}
		int8_t turntable() const;

		boolean buttonGreen() const;
		boolean buttonRed() const;
		boolean buttonBlue() const;

		void turntable(int8_t dataIn);

		void buttonGreen(boolean bitIn);
		void buttonRed(boolean bitIn);
		void buttonBlue(boolean bitIn);
	} left;

	class TurntableRight: public TurntableExpansion {
	public:
		TurntableRight(DJTurntableController &baseObj)
			: TurntableExpansion(NXC_DJTurntable_Right, baseObj) {}
		int8_t turntable() const;

		boolean buttonGreen() const;
		boolean buttonRed() const;
		boolean buttonBlue() const;

		void turntable(int8_t dataIn);

		void buttonGreen(boolean bitIn);
		void buttonRed(boolean bitIn);
		void buttonBlue(boolean bitIn);
	} right;

	class EffectRollover : private NXCtrl::RolloverChange {
	public:
		EffectRollover(DJTurntableController & controller) : RolloverChange(0, 31), dj(controller) {}
		int8_t getChange();
	private:
		const DJTurntableController & dj;
	};

private:
	void printTurntable(Stream& stream, TurntableExpansion &table) const;

	static const int8_t CrossfadeOffset = -8;  // Convert the crossfade to +/- about 0
	NXC_DJTurntable_Configuration tableConfig = NXC_DJTurntable_BaseOnly;
};

#endif
