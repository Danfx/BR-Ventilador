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
#include <Arduino.h>
#include "hdr/defines.h"
#include "hdr/devices/AirHeater.h"
#include "hdr/devices/AirValve.h"
#include "hdr/devices/ExpiratoryMembrane.h"
#include "hdr/devices/FlowMeter.h"
#include "hdr/devices/MixValve.h"
#include "hdr/devices/O2Valve.h"
#include "hdr/devices/PressureSensor.h"
#include "hdr/devices/SensorLambda.h"
#include "hdr/devices/SolenoidValve.h"
#include "hdr/system/Control.h"
#include "hdr/devices/Display.h"

#ifdef AIR_VALVE_ENABLE
AirValve airValve;
#endif

#ifdef O2_VALVE_ENABLE
O2Valve o2Valve;
#endif

#ifdef SENSOR_LAMBDA_ENABLE
SensorLambda sensorLambda;
#endif

#ifdef MIX_VALVE_ENABLE
MixValve mixValve;
#endif

#ifdef AIR_HEATER_ENABLE
AirHeater airHeater;
#endif

#ifdef SOLENOID_VALVE_ENABLE
SolenoidValve solValve;
#endif

#ifdef FLOW_METER_ENABLE
FlowMeter flowMeter;
#endif

#ifdef PRESSURE_SENSOR_ENABLE
PressureSensor pressSensor;
#endif

#ifdef EXPIRATORY_MEMBRANE_ENABLE
ExpiratoryMembrane expMembrane;
#endif

#ifdef DISPLAY_ENABLE
Display disp;
#endif

typedef struct {
	double air;
	double o2;
	double mix;
	int ms;
} config_t;

Control ctrl;
config_t config[4];

void setup() {
#ifdef SERIAL_DEBUG_ENABLE
	Serial.begin(115200);
#endif

#ifdef AIR_VALVE_ENABLE
	airValve.begin();
#endif

#ifdef O2_VALVE_ENABLE
	o2Valve.begin();
#endif

#ifdef SENSOR_LAMBDA_ENABLE
	sensorLambda.begin();
#endif

#ifdef MIX_VALVE_ENABLE
	mixValve.begin();
#endif

#ifdef AIR_HEATER_ENABLE
	airHeater.begin();
#endif

#ifdef SOLENOID_VALVE_ENABLE
	solValve.begin();
#endif

#ifdef FLOW_METER_ENABLE
	flowMeter.begin();
#endif

#ifdef PRESSURE_SENSOR_ENABLE
	pressSensor.begin();
#endif

#ifdef EXPIRATORY_MEMBRANE_ENABLE
	expMembrane.begin();
#endif

#ifdef DISPLAY_ENABLE
	disp.begin();
#endif

	//
	// init control interface
	//
	ctrl.begin();

	//
	// Mode 1 - BT 21
	//
	config[0].o2 = 1.5;		// 50%
	config[0].air = 1.5;	// 50%
	config[0].mix = 3.0;	// 3.0
	config[0].ms = 5;		// 5 segs
	//
	// Mode 2 - BT 20
	//
	config[1].o2 = 1;		// 25%
	config[1].air = 3.0;	// 75%
	config[1].mix = 4.0;	// 4.0
	config[1].ms = 3;		// 3 segs
	//
	// Mode 3 - BT 19
	//
	config[2].o2 = 1.0;		// 100%
	config[2].air = 0;		// 0%
	config[2].mix = 1.0;	// 1.0
	config[2].ms = 8;		// 8 segs
	//
	// Mode 4 - BT 18
	//
	config[3].o2 = 1.7;		// 85%
	config[3].air = 0.3;	// 15%
	config[3].mix = 2.0;	// 2.0
	config[3].ms = 4;		// 4 segs
}

typedef enum {
	BREATHING_OUT_TO_IN=0,
	BREATHING_IN,
	BREATHING_IN_TO_OUT,
	BREATHING_OUT,
} state_t;

void delayShowPressure(int segs){
	double press;
	segs *= 2;
	for(int i=0;i<segs;i++){
		press = pressSensor.readPressure();
		// debug
		Serial.print(F("Pressure: "));
		Serial.println(press);
		// display
		disp.printPressure(press);
		// delay
		delay(500);
	}
}

void loop() {

	// Initial State
	airValve.close();
	o2Valve.close();
	mixValve.close();
	airHeater.setTurn(AirHeater::TURN_OFF);
	solValve.close();
	expMembrane.open();

	// wait for start machine
	while(!ctrl.isStarted());

	config_t *c = &config[ctrl.getMode()];

	// set initial PCV state
	o2Valve.setPressure(c->o2);
	airValve.setPressure(c->air);
	mixValve.setPressure(c->mix);
	airHeater.setTurn(AirHeater::TURN_ON);

	state_t state = BREATHING_OUT_TO_IN;

	// exec until machine stop
	while(ctrl.isStarted()){
		// state machine
		switch(state){
			case BREATHING_OUT_TO_IN:
				delayShowPressure(c->ms);
				state = BREATHING_IN;
			break;
			case BREATHING_IN:
				expMembrane.close();
				solValve.open();
				state = BREATHING_IN_TO_OUT;
			break;
			case BREATHING_IN_TO_OUT:
				delayShowPressure(c->ms);
				solValve.close();
				expMembrane.open();
				state = BREATHING_OUT;
			break;
			case BREATHING_OUT:
				state = BREATHING_OUT_TO_IN;
			break;
		}
	}

}





