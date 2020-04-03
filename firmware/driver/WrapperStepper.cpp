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
#include "../hdr/driver/WrapperStepper.h"
#include "../hdr/hardware.h"


#ifdef WRAPPER_AccelStepper
WrapperStepper::WrapperStepper(uint8_t _pin_enable,uint8_t interface, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, bool enable):
		stepper(interface,pin1,pin2,pin3,pin4,enable)
#endif
#ifdef WRAPPER_Stepper
WrapperStepper::WrapperStepper(uint8_t _pin_enable,uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4):
		stepper(STEPPER_PER_REVOLUTION,pin1,pin3,pin2,pin4)
#endif
{
	pin_enable = _pin_enable;
}

WrapperStepper::~WrapperStepper() {
}

void WrapperStepper::begin() {
	pinMode(pin_enable, OUTPUT);
#ifdef WRAPPER_AccelStepper
	stepper.setMaxSpeed(STEPPER_MAX_SPEED);
	stepper.setAcceleration(STEPPER_MAX_ACCELERATION);
#endif
#ifdef WRAPPER_Stepper
	stepper.setSpeed(STEPPER_MAX_SPEED);
#endif
	close();
}

void WrapperStepper::close(){
	setPressure(0);
}

void WrapperStepper::setMotorPosition(long position){
	setEnable(WrapperStepper::ENABLE);
#ifdef WRAPPER_AccelStepper
	stepper.moveTo(position);
	stepper.runToPosition();
#endif
#ifdef WRAPPER_Stepper
	Serial.println(position);
	stepper.step(position);
#endif
	setEnable(WrapperStepper::DISABLE);
}

void WrapperStepper::setEnable(stepper_enable_t se){
	digitalWrite(pin_enable,(uint8_t)se);
}
