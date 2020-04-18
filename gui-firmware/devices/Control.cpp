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

#include "../hdr/system/Control.h"
#include "../hdr/hardware.h"
#include <Arduino.h>

#define VAL_STARTED			0

static Control* pControl = NULL;

void bt_start_interrupt(){
	static unsigned long last_interrupt_time_bts = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time_bts > 200) {
		if( pControl ) pControl->doTaskSetButton(Control::BTN_START);
	}
	last_interrupt_time_bts = interrupt_time;
}

void bt_up_interrupt(){
	static unsigned long last_interrupt_time_btm1 = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time_btm1 > 200) {
		if( pControl ) pControl->doTaskSetButton(Control::BTN_UP);
	}
	last_interrupt_time_btm1 = interrupt_time;
}

void bt_right_interrupt(){
	static unsigned long last_interrupt_time_btm2 = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time_btm2 > 200) {
		if( pControl ) pControl->doTaskSetButton(Control::BTN_RIGHT);
	}
	last_interrupt_time_btm2 = interrupt_time;
}

void bt_down_interrupt(){
	static unsigned long last_interrupt_time_btm3 = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time_btm3 > 200) {
		if( pControl ) pControl->doTaskSetButton(Control::BTN_DOWN);
	}
	last_interrupt_time_btm3 = interrupt_time;
}

void bt_left_interrupt(){
	static unsigned long last_interrupt_time_btm4 = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time_btm4 > 200) {
		if( pControl ) pControl->doTaskSetButton(Control::BTN_LEFT);
	}
	last_interrupt_time_btm4 = interrupt_time;
}

Control::Control() {
	pControl = this;
	btn = BTN_NONE;
}

Control::~Control() {
	pControl = NULL;
}

void Control::begin(){
	pinMode(PIN_BUTTON_START, INPUT_PULLUP);
	pinMode(PIN_BUTTON_UP, INPUT_PULLUP);
	pinMode(PIN_BUTTON_RIGHT, INPUT_PULLUP);
	pinMode(PIN_BUTTON_DOWN, INPUT_PULLUP);
	pinMode(PIN_BUTTON_LEFT, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_START), bt_start_interrupt, FALLING);
	attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_UP), bt_up_interrupt, FALLING);
	attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_RIGHT), bt_right_interrupt, FALLING);
	attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_DOWN), bt_down_interrupt, FALLING);
	attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_LEFT), bt_left_interrupt, FALLING);
}

void Control::doTaskSetButton(button_t _btn){
	btn = _btn;
}

Control::button_t Control::getButton(){
	while(btn == BTN_NONE);
	button_t _btn = btn;
	btn = BTN_NONE;
	return _btn;
}
