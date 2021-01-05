/*
 * Channel.cpp
 *
 *  Created on: 26 Nov 2020
 *      Author: julianporter
 */

#include "Channel.hpp"

namespace queg {

AudioChannel::AudioChannel(const char *name,const Direction dir) : direction(dir) {
	ptr = JBox_GetMotherboardObjectRef(name);
}

bool AudioChannel::isConnected() const {
		auto attr = (direction == Direction::Input) ? kJBox_AudioInputConnected : kJBox_AudioOutputConnected;
		auto ref = JBox_LoadMOMPropertyByTag(ptr,attr);
		if(JBox_GetType(ref)==kJBox_Boolean) return JBox_GetBoolean(ref);
		else return false;
	}

uint32 AudioChannel::read(float32 *buffer) {
		assert(direction==Direction::Input);
		if(!isConnected()) return 0;
		auto ref = JBox_LoadMOMPropertyByTag(ptr, kJBox_AudioInputBuffer);
		auto length = std::min<int64>(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
		if(length>0) {
			JBox_GetDSPBufferData(ref, 0, length, buffer);
		}
		return static_cast<int32>(length);
	}
	void AudioChannel::write(const uint32 length,float32 *buffer) {
		assert(direction==Direction::Output);
		auto ref = JBox_LoadMOMPropertyByTag(ptr, kJBox_AudioOutputBuffer);
		if(length>0) {
			JBox_SetDSPBufferData(ref, 0, length, buffer);
		}
	}

	// template is
	//
	// cv_outputs/SNOut
	//
	// where S = A,B,C,D,X,Y and n = 1,2,3,4
	//
	// so
	//             0123456788012
	// template = "cv_outputs/__Out"
	// template[11]=s
	// template[12]='1'+n

	ChannelCVs::ChannelCVs(const char name) {

		char *xxtmpl="/cv_outputs/X_Out";
		xxtmpl[13]=name;
		xOutCV=JBox_GetMotherboardObjectRef(xxtmpl);
		char *yytmpl="/cv_outputs/Y_Out";
		yytmpl[13]=name;
		yOutCV=JBox_GetMotherboardObjectRef(yytmpl);
	}



	void ChannelCVs::x(const float32 v) { JBox_StoreMOMPropertyAsNumber(xOutCV,kJBox_CVOutputValue,v); }
	void ChannelCVs::y(const float32 v) { JBox_StoreMOMPropertyAsNumber(yOutCV,kJBox_CVOutputValue,v); }
} /* namespace queg */
