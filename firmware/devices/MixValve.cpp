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
#include "../hdr/devices/MixValve.h"
#include "../hdr/hardware.h"
#include "../hdr/defines.h"

MixValve::MixValve() :
#ifdef WRAPPER_AccelStepper
WrapperStepper(STEPPER_MIX_PIN_ENABLE,STEPPER_MIX_MOTOR_IFACE, STEPPER_MIX_STEP_PIN, STEPPER_MIX_DIR_PIN)
#endif
#ifdef WRAPPER_Stepper
	WrapperStepper(STEPPER_MIX_PIN_ENABLE,STEPPER_MIX_INI1_PIN, STEPPER_MIX_INI2_PIN, STEPPER_MIX_INI3_PIN,STEPPER_MIX_INI4_PIN)
#endif
{
	last_value=0;
}

MixValve::~MixValve() {
}

void MixValve::setPressure(double value) {
#ifdef WRAPPER_AccelStepper
	setMotorPosition((value*STEPPER_MAX_VALUE)/MAX_MIX_PRESSURE);
#endif
#ifdef WRAPPER_Stepper
	long _value = ((value*STEPPER_MAX_VALUE)/MAX_MIX_PRESSURE);
	setMotorPosition(_value-last_value);
	last_value = _value;
#endif
}

void MixValve::setPercent(double value) {
#ifdef WRAPPER_AccelStepper
	setMotorPosition((value*STEPPER_MAX_VALUE)/100);
#endif
#ifdef WRAPPER_Stepper
	long _value = ((value*STEPPER_MAX_VALUE)/NETWORK_AIR_PRESSURE);
	setMotorPosition(_value-last_value);
	last_value = _value;
#endif
}

