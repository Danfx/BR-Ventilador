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
		if( pControl ) pControl->doTaskBtStart();
	}
	last_interrupt_time_bts = interrupt_time;
}

void bt_mode_1_interrupt(){
	static unsigned long last_interrupt_time_btm1 = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time_btm1 > 200) {
		if( pControl ) pControl->doTaskSetMode(0);
	}
	last_interrupt_time_btm1 = interrupt_time;
}

void bt_mode_2_interrupt(){
	static unsigned long last_interrupt_time_btm2 = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time_btm2 > 200) {
		if( pControl ) pControl->doTaskSetMode(1);
	}
	last_interrupt_time_btm2 = interrupt_time;
}

void bt_mode_3_interrupt(){
	static unsigned long last_interrupt_time_btm3 = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time_btm3 > 200) {
		if( pControl ) pControl->doTaskSetMode(2);
	}
	last_interrupt_time_btm3 = interrupt_time;
}

void bt_mode_4_interrupt(){
	static unsigned long last_interrupt_time_btm4 = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time_btm4 > 200) {
		if( pControl ) pControl->doTaskSetMode(3);
	}
	last_interrupt_time_btm4 = interrupt_time;
}

Control::Control() {
	started = false;
	pControl = this;
	mode = 0;
}

Control::~Control() {
	pControl = NULL;
}

void Control::begin(){
	pinMode(PIN_BUTTON_START, INPUT_PULLUP);
	started = (digitalRead(PIN_BUTTON_START) == VAL_STARTED);
	attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_START), bt_start_interrupt, FALLING);
	attachInterrupt(digitalPinToInterrupt(PIN_MODE_1), bt_mode_1_interrupt, FALLING);
}

void Control::doTaskBtStart(){
	started = !started;
}

void Control::doTaskSetMode(uint8_t _mode){
	mode = (mode==3) ? 0 : (mode+1);
//	mode = _mode;
}

bool Control::isStarted() {
	return started;
}

uint8_t Control::getMode(){
	return mode;
}
