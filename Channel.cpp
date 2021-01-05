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


	const char * const cvTemplate="/cv_outputs/__Out";

	TJBox_ObjectRef getRef(const uint8 channel,const char name) {
		char tmpl[20];
		strcpy(tmpl,cvTemplate);
		tmpl[12]=name;
		tmpl[13]='1'+channel;
		return JBox_GetMotherboardObjectRef(tmpl);
	}

	ChannelCVs::ChannelCVs(const uint8 channel) {
		xPtr=getRef(channel,'X');
		yPtr=getRef(channel,'Y');
	}

	void ChannelCVs::x(const float32 value) const {
		JBox_StoreMOMPropertyAsNumber(xPtr,kJBox_CVOutputValue,value);
	}
	void ChannelCVs::y(const float32 value) const {
			JBox_StoreMOMPropertyAsNumber(yPtr,kJBox_CVOutputValue,value);
		}

} /* namespace queg */
