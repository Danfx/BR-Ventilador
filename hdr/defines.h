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

#ifndef HDR_DEFINES_H_
#define HDR_DEFINES_H_

//
// Hardware Features
//
#define AIR_VALVE_ENABLE
#define O2_VALVE_ENABLE

//#define SENSOR_LAMBDA_ENABLE
#define MIX_VALVE_ENABLE

#define AIR_HEATER_ENABLE
#define SOLENOID_VALVE_ENABLE

#define FLOW_METER_ENABLE

#define PRESSURE_SENSOR_ENABLE

#define EXPIRATORY_MEMBRANE_ENABLE

#define DISPLAY_ENABLE

//
// Software Definitions
//
#define NETWORK_O2_PRESSURE			3.00
#define NETWORK_AIR_PRESSURE		3.00
#define MAX_MIX_PRESSURE			(NETWORK_O2_PRESSURE+NETWORK_AIR_PRESSURE)

//
// Debug
//
#define SERIAL_DEBUG_ENABLE

#endif /* HDR_DEFINES_H_ */
