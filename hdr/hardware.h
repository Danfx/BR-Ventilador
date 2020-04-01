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

#ifndef HDR_HARDWARE_H_
#define HDR_HARDWARE_H_

#include <AccelStepper.h>

//
// Control Buttons
//
#define PIN_BUTTON_START				2
#define PIN_MODE_1						21
#define PIN_MODE_2						20
#define PIN_MODE_3						19
#define PIN_MODE_4						18

//
// Display (Digital I/O)
//
#define LCD_COLS    		20
#define LCD_ROWS    		4
#define LCD_RESET   		9
#define LCD_EN      		8
#define LCD_D4      		7
#define LCD_D5      		6
#define LCD_D6      		5
#define LCD_D7      		4

//
// DRV8825 Stepper Motor Driver
//
#define STEPPER_ONE_STEP				400
#define STEPPER_MAX_VALUE				(STEPPER_ONE_STEP*7) // o registro da no máximo 7 voltas
#define STEPPER_MAX_SPEED				200
#define STEPPER_MAX_ACCELERATION		50
#define STEPPER_ENABLE					1
#define STEPPER_DISABLE					0

//
// O2 Valve Stepper Motor
//
#define STEPPER_O2_DIR_PIN				23
#define STEPPER_O2_STEP_PIN				25
#define STEPPER_O2_MOTOR_IFACE			AccelStepper::DRIVER
#define STEPPER_O2_PIN_ENABLE			27

//
// Air Valve Stepper Motor
//
#define STEPPER_AIR_DIR_PIN				29
#define STEPPER_AIR_STEP_PIN			31
#define STEPPER_AIR_MOTOR_IFACE			AccelStepper::DRIVER
#define STEPPER_AIR_PIN_ENABLE			33

//
// Mix Valve Stepper Motor
//
#define STEPPER_MIX_DIR_PIN				39
#define STEPPER_MIX_STEP_PIN			41
#define STEPPER_MIX_MOTOR_IFACE			AccelStepper::DRIVER
#define STEPPER_MIX_PIN_ENABLE			43

//
// Air Heater
//
#define PIN_AIR_HEATER					53
#define AH_VAL_TURN_ON					1
#define AH_VAL_TURN_OFF					0

//
// Solenoid Valve
//
#define PIN_SOL_VALVE					51
#define SA_VALVE_OPEN					1
#define SA_VALVE_CLOSE					0

//
// Flow Meter
//
#define PIN_FLOW_METER					D3

//
// Pressure Sensor
//
#define PIN_PRESS_SENSOR				A1
#define VS_PRESS_SENSOR					5	// Vs = 5.0 Vdc

//
// Expiratory Membrane
//
#define PIN_EXP_MEMBRANE				45
#define EX_MEMB_OPEN					23
#define EX_MEMB_CLOSE					0

#define BUZZER							12
#define LED								13
#define SOURCE_POWER_MONITOR			46
#define SOURCE_POWER_BATTERY			A0


#endif /* HDR_HARDWARE_H_ */
