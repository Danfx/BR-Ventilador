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
#include "../hdr/devices/FlowMeter.h"
#include "../hdr/hardware.h"

FlowMeter::FlowMeter() {
}

FlowMeter::~FlowMeter() {
}

void FlowMeter::begin() {
	pinMode(PIN_FLOW_METER, INPUT_PULLUP);
}

double FlowMeter::readFlow(){
	double val = 0;
	double vOut = (analogRead(PIN_FLOW_METER)*5.0)/1024.0;
	if( vOut <= 2.99 ){
		val = 12.563*vOut-12.563;
	} else if( vOut <= 3.82 ){
		val = 30.12*vOut-65.06;
	} else if( vOut <= 4.30 ){
		val = 52.083*vOut-148.96;
	} else if( vOut <= 4.58 ){
		val = 89.286*vOut-308.93;
	} else if( vOut <= 4.86 ){
		val = 178.57*vOut-717.86;
	} else if( vOut <= 5 ){
		val = 357.14*vOut-1585.7;
	}
	return val;
}
