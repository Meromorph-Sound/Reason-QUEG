/*
 * vco.cpp
 *
 *  Created on: 25 Nov 2020
 *      Author: julianporter
 */

#include "vco.hpp"

namespace queg {
namespace vco {




const int32 SimpleVCO::CV_OUT = kJBox_CVOutputValue;
const float32 SimpleVCO::PERIOD_BASE = 7.5e-3;
const float32 SimpleVCO::PERIOD_DECADES = 3.0;





SimpleVCO::SimpleVCO() : active(false), holding(false), ticks(0), sampleRate(1.0/48000.0), period(1),
		position(0), width(1), height(1),
		offsets(4), patterns() {
	xOutCV = JBox_GetMotherboardObjectRef("/cv_outputs/vcoXOut");
	yOutCV = JBox_GetMotherboardObjectRef("/cv_outputs/vcoYOut");
	env=JBox_GetMotherboardObjectRef("/environment");

	pattern=nullptr;
}

float32 SimpleVCO::getEnvVariable(const Tag tag) {
	const TJBox_Value& v = JBox_LoadMOMPropertyByTag(env, tag);
	const TJBox_Float64& n = JBox_GetNumber(v);
	return static_cast<float32>(n);
}

void SimpleVCO::loadSampleRate() {
	sampleRate=getEnvVariable(kJBox_EnvironmentSystemSampleRate);
	trace("Loaded sample rate as ^0",sampleRate);
}

void SimpleVCO::writeCV(const Point &p) {
	JBox_StoreMOMPropertyAsNumber(xOutCV,CV_OUT,p.x);
	JBox_StoreMOMPropertyAsNumber(yOutCV,CV_OUT,p.y);
}




void SimpleVCO::processBuffer(const uint32 length) {
	if(!active) return;
	if(active && !holding) {
		ticks+=length/sampleRate;
		position=ticks/period;
		if(pattern) writeCV(pattern->position(position));
	}
}

Point SimpleVCO::operator()(const uint32 channel) const {
	auto pos = offsets[channel]+position;
	if(pattern) return pattern->position(pos);
	else return Point();
}



inline float32 toFloat(const value_t diff) {
	return static_cast<float32>(JBox_GetNumber(diff));
}




void SimpleVCO::processChanges(const Tag &tag,const Channel channel,const value_t value) {

	switch(tag) {
	case VCO_ACTIVE: {
		auto old = active;
		active = toFloat(value)>0;
		if (!old && active) {
			ticks=0;
			position=0;
			loadSampleRate();
		}
		if(active) trace("VCO on");
		else trace("VCO off");
		break; }
	case VCO_FROZEN: {
		holding = toFloat(value)>0;
		break; }
	case VCO_RESET:
		ticks=0;
		position=0;
		break;
	case VCO_FREQUENCY: {
		float v=std::min(1.0f,std::max(0.0f,toFloat(value)));
		period=PERIOD_BASE * pow(10.0f,v*PERIOD_DECADES);
		trace("Period is ^0",period);
		break; }
	case VCO_WIDTH: {
		float v=std::min(1.0f,std::max(0.0f,toFloat(value)));
		width=v;
		if(pattern) pattern->setScaling(width,height);
		trace("Width is ^0",width);
		break;
	}
	case VCO_HEIGHT:{
		float v=std::min(1.0f,std::max(0.0f,toFloat(value)));
		height=v;
		if(pattern) pattern->setScaling(width,height);
		trace("Height is ^0",height);
		break;
	}
	case VCO_PATTERN: {
		auto v = (uint32)toFloat(value);
		trace("Pattern is ^0",v);
		pattern=patterns[v];
		pattern->setScaling(width,height);
		break; }
	case VCO_START_BASE:
		offsets[channel]=toFloat(value);
		break;
	default:
		break;
	}
}


}}


