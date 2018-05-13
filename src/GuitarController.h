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

#ifndef NXC_GuitarController_h
#define NXC_GuitarController_h

#include "ExtensionController.h"
#include "ClassicController.h"  // For joy and +/- byte defines

#define NXC_CTRLBIT_GUITAR_STRUMUP 5, 0
#define NXC_CTRLBIT_GUITAR_STRUMDOWN 4, 6

#define NXC_CTRLBIT_GUITAR_GREEN 5, 4
#define NXC_CTRLBIT_GUITAR_RED 5, 6
#define NXC_CTRLBIT_GUITAR_YELLOW 5, 3
#define NXC_CTRLBIT_GUITAR_BLUE 5, 5
#define NXC_CTRLBIT_GUITAR_ORANGE 5, 7

#define NXC_CTRLBYTE_GUITAR_WHAMMY 3, 5, 0, 0
#define NXC_CTRLBYTE_GUITAR_TOUCHBAR 2, 5, 0, 0

class GuitarController : public ExtensionController {
public:
	GuitarController(NXC_I2C_TYPE& i2cBus = NXC_I2C_DEFAULT);
	GuitarController(ExtensionData& busData);

	uint8_t joyX() const;  // 6 bits, 0-63
	uint8_t joyY() const;

	boolean strum() const;
	boolean strumUp() const;
	boolean strumDown() const;

	boolean fretGreen() const;
	boolean fretRed() const;
	boolean fretYellow() const;
	boolean fretBlue() const;
	boolean fretOrange() const;

	uint8_t whammyBar() const;  // 5 bits, 0-31 (starting at ~15-16)

	uint8_t touchbar() const;  // 5 bits, 0-31
	boolean touchGreen() const;
	boolean touchRed() const;
	boolean touchYellow() const;
	boolean touchBlue() const;
	boolean touchOrange() const;

	boolean buttonPlus() const;
	boolean buttonMinus() const;

	void joyX(uint8_t dataIn);
	void joyY(uint8_t dataIn);

	void strumUp(boolean bitIn);
	void strumDown(boolean bitIn);

	void fretGreen(boolean bitIn);
	void fretRed(boolean bitIn);
	void fretYellow(boolean bitIn);
	void fretBlue(boolean bitIn);
	void fretOrange(boolean bitIn);

	void whammyBar(uint8_t dataIn);

	void touchbar(uint8_t dataIn);

	void buttonPlus(boolean bitIn);
	void buttonMinus(boolean bitIn);

	void printDebug(Stream& stream=NXC_SERIAL_DEFAULT);

	boolean supportsTouchbar();

private:
	boolean touchbarData = false;  // Flag for touchbar data found
};

#endif
