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
#include "hdr/devices/Display.h"
#include "hdr/container/JsonData.h"
#include <string.h>
#include "hdr/defines.h"
#include "hdr/container/Config.h"
#include "hdr/system/Control.h"

Control ctrl;
Display disp;
int cursor;

config_t cfg[] = {
	{
		.label = "MODO",
		.key = "mode",
		.value = MODE_PCV,
		.max = 1,
		.min = 0,
		.visibility = SHOW_ALWAYS,
		.increment = 1
	},
	{
		.label = "NIVEL DE O2",
		.key = "o2",
		.value = 50,
		.max = 100,
		.min = 0,
		.visibility = SHOW_ALWAYS,
		.increment = 5
	},
	{
		.label = "NIVEL DE AR",
		.key = "air",
		.value = 50,
		.max = 100,
		.min = 0,
		.visibility = SHOW_ALWAYS,
		.increment = 5
	},
	{
		.label = "PRESSAO LIMITE",
		.key = "plim",
		.value = 20,
		.max = 100,
		.min = 0,
		.visibility = SHOW_ALWAYS,
		.increment = 1
	},
	{
		.label = "PEEP",
		.key = "peep",
		.value = 5,
		.max = 100,
		.min = 0,
		.visibility = SHOW_ALWAYS,
		.increment = 1
	},
	{
		.label = "TEMPO DE INSPIRACAO (MS)",
		.key = "i_ms",
		.value = 2000,
		.max = 10000,
		.min = 1000,
		.visibility = SHOW_VCV,
		.increment = 10
	},
	{
		.label = "VOLUME (CMH2O)",
		.key = "volume",
		.value = 200,
		.max = 1000,
		.min = 0,
		.visibility = SHOW_VCV,
		.increment = 1
	},
	{
		.label = "FLUXO (L/MIN)",
		.key = "fluxo",
		.value = 10,
		.max = 100,
		.min = 0,
		.visibility = SHOW_ALWAYS,
		.increment = 1
	},
	{
		.label = "FREQUENCIA (BPM)",
		.key = "frequency",
		.value = 15,
		.max = 100,
		.min = 0,
		.visibility = SHOW_ALWAYS,
		.increment = 1
	},
};

size_t cfg_len = (sizeof(cfg)/sizeof(config_t));
int pcv_len=0;
int vcv_len=0;
config_t* mode = NULL;
config_t* attr = NULL;

void setup() {
	Serial.begin(115200);
	disp.begin();
	for(size_t i=0;i<cfg_len;i++){
		if( cfg[i].key == "mode" ){
			mode = &cfg[i];
		}
		if( cfg[i].visibility == SHOW_ALWAYS ){
			pcv_len++;
			vcv_len++;
		} else if( cfg[i].visibility == SHOW_VCV ){
			vcv_len++;
		} else if( cfg[i].visibility == SHOW_PCV ){
			pcv_len++;
		}
	}
	cursor = 0;
	attr = &cfg[0];
	ctrl.begin();
}

void refreshAttributePointer(){
	int k=0;
	for(size_t i=0;i<cfg_len;i++){
		if( k == cursor ){
			attr = &cfg[i];
			break;
		}
		if( cfg[i].visibility == mode->value ){
			k++;
		}
	}
}

void loop() {

	disp.printMenu(cursor,mode,cfg,cfg_len);
	switch(ctrl.getButton()){
		case Control::BTN_UP:
			Serial.println("-- UP --");
			if( mode->value == MODE_PCV ){
				cursor = (cursor-1) < 0 ? pcv_len-1 : (cursor-1);
			} else {
				cursor = (cursor-1) < 0 ? vcv_len-1 : (cursor-1);
			}
			refreshAttributePointer();
		break;
		case Control::BTN_DOWN:
			Serial.println("-- DOWN --");
			if( mode->value == MODE_PCV ){
				cursor = (cursor+1) < pcv_len ? (cursor+1) : 0;
			} else {
				cursor = (cursor+1) < vcv_len ? (cursor+1) : 0;
			}
			refreshAttributePointer();
		break;
		case Control::BTN_RIGHT:
			Serial.println("-- RIGHT --");
			attr->value = (attr->value+attr->increment) <= attr->max ? (attr->value+attr->increment) : attr->min;
		break;
		case Control::BTN_LEFT:
			Serial.println("-- LEFT --");
			attr->value = (attr->value-attr->increment) >= attr->min ? (attr->value-attr->increment) : attr->max;
		break;
		case Control::BTN_START:
			Serial.println("-- START --");
			JsonData jd;
			for(size_t i=0;i<cfg_len;i++){
				if( cfg[i].visibility == SHOW_ALWAYS || mode->value == cfg[i].visibility ){
					jd.addData(cfg[i].key,cfg[i].value);
				}
			}
			Serial.println(jd.toString().c_str());
		break;
	}

#if 0
	// TODO
	// Em outro 'Arduino'
	//
	cJSON* root = cJSON_Parse("{\"param\":\"123\"}");
	if( root ){
		cJSON* jparam = cJSON_GetObjectItem(root,"param");
		if( cJSON_IsString(jparam) ){
			Serial.println(jparam->valuestring);
		}
		cJSON_Delete(root);
	}
#endif

}
