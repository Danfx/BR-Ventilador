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
	double plim;
	double peep;
	int i_ms;
	int e_ms;
} config_pcv_t;

typedef struct {
	double air;
	double o2;
	double plim;
	double peep;
	double volume;
	double fluxo;
	int e_ms;
} config_vcv_t;

Control ctrl;
config_pcv_t config_pcv[4];
config_vcv_t config_vcv[4];

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
	// Mode PCV
	//
	config_pcv[0].o2 = 70;		// %
	config_pcv[0].air = 50;		// %
	config_pcv[0].plim = 15;	// cmH20
	config_pcv[0].peep = 5;  	// cmH20
	config_pcv[0].i_ms = 2000;	// milisegs
	config_pcv[0].e_ms = 3000;	// milisegs

	config_pcv[0].plim += config_pcv[0].peep;

	//
	// Mode VCV
	//
	config_vcv[0].o2 = 70;		// %
	config_vcv[0].air = 50;		// %
	config_vcv[0].plim = 15;	// cmH20
	config_vcv[0].peep = 5;  	// cmH20
	config_vcv[0].volume = 300;	// mL
	config_vcv[0].fluxo = 15;	// L/Min
	config_vcv[0].e_ms = 2000;	// milisegs

	config_vcv[0].plim += config_vcv[0].peep;
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
		Serial.println((press<0?0:press));
		// display
		disp.printPressure(press,ctrl.getMode());
		// delay
		delay(500);
	}
}

void loop() {

	o2Valve.close();
	mixValve.close();
	solValve.close();
	expMembrane.open();

	// wait for start machine
	while(!ctrl.isStarted());

	if( ctrl.getMode() == 0 ){ // PCV
		Serial.println(F("Modo PCV"));

		config_pcv_t *c = &config_pcv[0];
		bool mixLimit = false;

		o2Valve.setPercent(c->o2);
		airValve.setPercent(c->air);
		expMembrane.close();

		while(ctrl.isStarted()){
			solValve.open();

			double percent = 0;
			double press = pressSensor.readPressure();
			while( press < c->plim ){
				if( percent < 100 && !mixLimit ){
					percent += PCV_PERCENT_INCREMENT;
					mixValve.setPercent(percent);
				}
				press = pressSensor.readPressure();
			}
			solValve.close();
			mixLimit = true;
			delay(c->i_ms);

			expMembrane.open();
			press = pressSensor.readPressure();
			while( press > c->peep ){
				press = pressSensor.readPressure();
			}

			expMembrane.close();
			delay(c->e_ms);
		}
	} else { // VCV
		Serial.println(F("Modo VCV"));

		config_vcv_t *c = &config_vcv[0];
		unsigned long t,ti;
		bool mixLimit = false;

		ti = ((6*c->volume)/(100*c->fluxo))*1000; // ms

		o2Valve.setPercent(c->o2);
		airValve.setPercent(c->air);
		expMembrane.close();

		while(ctrl.isStarted()){
			solValve.open();

			t = millis();
			double percent = 0;
			double flow = flowMeter.readFlow();
			double press = pressSensor.readPressure();

			while( flow < c->fluxo && press < c->plim ){
				if( percent < 100 && !mixLimit ){
					percent += VCV_PERCENT_INCREMENT;
					mixValve.setPercent(percent);
				}
				press = pressSensor.readPressure();
				flow = flowMeter.readFlow();
			}
			t = abs(ti - ((millis()-t)/2)); // **
			t += millis();
			mixLimit = true;

			press = pressSensor.readPressure();
			while( press < c->plim && (t > millis()) ){
				press = pressSensor.readPressure();
			}
			solValve.close();

			expMembrane.open();
			press = pressSensor.readPressure();
			while( press > c->peep ){
				press = pressSensor.readPressure();
			}

			expMembrane.close();
			delay(c->e_ms);
		}
	}
}





