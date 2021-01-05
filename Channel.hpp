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


	TJBox_ObjectRef xOutCV;
	TJBox_ObjectRef yOutCV;



public:
	ChannelCVs(const char name);
	virtual ~ChannelCVs() = default;



	void x(const float32);
	void y(const float32);
};



} /* namespace queg */

#endif /* QUEG_CHANNEL_HPP_ */
