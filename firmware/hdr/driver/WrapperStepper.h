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
#ifndef STEPPER_H_
#define STEPPER_H_

#include "../hardware.h"
#ifdef WRAPPER_AccelStepper
#include <AccelStepper.h>
#endif
#ifdef WRAPPER_Stepper
#include <Stepper.h>
#endif

class WrapperStepper {
protected:
	typedef enum {
		DISABLE=STEPPER_DISABLE,
		ENABLE=STEPPER_ENABLE
	} stepper_enable_t;
protected:
#ifdef WRAPPER_AccelStepper
	AccelStepper stepper;
#endif
#ifdef WRAPPER_Stepper
	Stepper stepper;
#endif
	uint8_t pin_enable;
protected:
	void setMotorPosition(long position);
	void setEnable(stepper_enable_t se);
public:
#ifdef WRAPPER_AccelStepper
	WrapperStepper(uint8_t _pin_enable,uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3, uint8_t pin3 = 4, uint8_t pin4 = 5, bool enable = true);
#endif
#ifdef WRAPPER_Stepper
	WrapperStepper(uint8_t _pin_enable,uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
#endif
	virtual ~WrapperStepper();
	void begin();
	void close();
	virtual void setPressure(double value)=0;
};

#endif /* STEPPER_H_ */
