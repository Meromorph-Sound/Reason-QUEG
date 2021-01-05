/*
 * Channel.hpp
 *
 *  Created on: 26 Nov 2020
 *      Author: julianporter
 */

#ifndef QUEG_CHANNEL_HPP_
#define QUEG_CHANNEL_HPP_

#include "base.hpp"


namespace queg {

class AudioChannel {

	const static uint32 BUFFER_SIZE = 64;

	enum class Direction {
		Input,
		Output
	};

	Direction direction;
	TJBox_ObjectRef ptr;

public:
	AudioChannel(const char *name,const Direction dir);

	bool isConnected() const;
	uint32 read(float32 *buffer);
	void write(const uint32 length,float32 *buffer);
};

class ChannelCVs {

	TJBox_ObjectRef xPtr;
	TJBox_ObjectRef yPtr;

public:
	ChannelCVs(const uint8 channel);
	ChannelCVs() : xPtr(0), yPtr(0) {};
	virtual ~ChannelCVs() = default;

	void x(const float32 value) const;
	void y(const float32 value) const;
};



} /* namespace queg */

#endif /* QUEG_CHANNEL_HPP_ */
