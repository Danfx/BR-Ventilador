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
#include "Main.cpp"
#include "../hdr/defines.h"

Display::Display():lcd(LCD_RESET,LCD_EN,LCD_D4,LCD_D5,LCD_D6,LCD_D7){
}

void Display::begin() {
	lcd.begin(LCD_COLS,LCD_ROWS);
}

void Display::printMenu(int cursor,config_t* mode,config_t* cfg,size_t cfg_len){
	int k=0;
	for(size_t i=0;i<cfg_len;i++){
		if( cfg[i].visibility == SHOW_ALWAYS || mode->value == cfg[i].visibility ){
			if( cursor == k++ ){
				Serial.print("> ");
			}
			Serial.print(cfg[i].label);
			Serial.print(" : ");
#if 1
			if( cfg[i].key == "mode" ){
				if( cfg[i].value == MODE_PCV ){
					Serial.println("PCV");
				} else if( cfg[i].value == MODE_VCV ){
					Serial.println("VCV");
				}
			} else {
				Serial.println(cfg[i].value);
			}
#else
			// exibe somente valores
			Serial.println(cfg[i].value);
#endif

		}
	}
}

void Display::printPressure(double press, double plim, double peep, double i_ms, int frequencia){
	char buffer[10];
	press = press < 0 ? 0 : press;
	dtostrf(press,2,2,buffer);
	// Turn on the display:
	lcd.display();
	lcd.clear();
	// row 0
	lcd.setCursor(5, 0);
	lcd.print("MODO PCV");
	// row 1
	lcd.setCursor(0, 1);
	lcd.print("Patual:");
	lcd.print(buffer);
	lcd.setCursor(12, 1);
	lcd.print(" [cmH2O]");
	//row 2
	lcd.setCursor(0, 2);
	lcd.print("Plim:");
	lcd.print(plim);
	lcd.setCursor(11, 2);
	lcd.print("PEEP:");
	lcd.print(peep);
	//row 3
	lcd.setCursor(0, 3);
	lcd.print("Freq:");
	lcd.print(frequencia);
	lcd.setCursor(11, 3);
	lcd.print("Ti:");
	lcd.print(i_ms);
	lcd.setCursor(17, 3);
	lcd.print("[s]");
}

void Display::printFlow(double flow,int mode){
	//char buffer[10];
	//press = press < 0 ? 0 : press;
	//dtostrf(press,2,2,buffer);
	// Turn on the display:
	lcd.display();
	lcd.clear();
	// row 0
	lcd.setCursor(5, 0);
	lcd.print("MODO VCV");
	// row 1
	lcd.setCursor(0, 1);
	lcd.print("Fluxo atual:");
	lcd.print(flow);
	lcd.setCursor(12, 1);
	lcd.print(" [L/s]");
	//row 2
	lcd.setCursor(1, 2);
	lcd.print("Plim:");
	lcd.print("15");
	lcd.setCursor(11, 2);
	lcd.print("PEEP:");
	lcd.print("5");
	//row 3
	lcd.setCursor(1, 3);
	lcd.print("Fluxo:");
	lcd.print("15");
	lcd.setCursor(11, 3);
	lcd.print("Vol:");
	lcd.print("300");
	lcd.setCursor(17, 3);
	lcd.print("mL]");
	//&dataMain = cb_Display();
	//lcd.print(cb_Display());
}
