/*
 * LICENSE MIT - https://tldrlegal.com/license/mit-license
 *
 * Copyright Daniel Fussia, https://github.com/Danfx
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "../hdr/devices/Display.h"
#include "../hdr/hardware.h"
#include "Arduino.h"

Display::Display():lcd(LCD_RESET,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7){
}

void Display::begin() {
	lcd.begin(LCD_COLS,LCD_ROWS);
}

void Display::printPressure(double press){
	char buffer[10];
	dtostrf(press,2,2,buffer);
	// Turn on the display:
	lcd.display();
	lcd.clear();
	// Col 3 row 0
	lcd.setCursor(3, 0);
	lcd.print("PRESSAO:");
	// Col 3 row 1
	lcd.setCursor(3, 1);
	lcd.print(buffer);
	lcd.print(" kPa");
}
