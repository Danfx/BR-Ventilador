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

#include "../hdr/container/JsonData.h"

JsonData::JsonData() {
	root = cJSON_CreateObject();
}

JsonData::~JsonData() {
	if( root ){
		cJSON_Delete(root);
	}
}

void JsonData::addData(String key,String value){
	if( root ){
		cJSON_AddStringToObject(root,key.c_str(),value.c_str());
	}
}

void JsonData::addData(String key,int value){
	addData(key,String(value,DEC));
}

String JsonData::toString(){
	String result = "";
	if( root ){
		char* jdata = cJSON_PrintUnformatted(root);
		result = String(jdata);
		cJSON_free(jdata);
	}
	return result;
}
