/*
 * base.hpp
 *
 *  Created on: 14 Sep 2020
 *      Author: julianporter
 */

#ifndef BASE_HPP_
#define BASE_HPP_

#include "Jukebox.h"
#include <type_traits>
#include <cmath>
#include <algorithm>


namespace queg {

using int8 = TJBox_Int8;
using uint8 = TJBox_UInt8;
using int32 = TJBox_Int32;
using uint32 = TJBox_UInt32;
using int64 = TJBox_Int64;
using uint64 = TJBox_UInt64;
using float64 = TJBox_Float64;
using float32 = TJBox_AudioSample;

using Tag = uint32;
using Channel = uint32;

using value_t = TJBox_Value;

enum class State : int32 {
	Off = 0, On = 1, Bypassed = 2
};

enum class Source : int32 {
	VCO = 0, Manual = 1, Bypass = 2
};

template<typename E, class = typename std::enable_if<std::is_enum<E>::value>::type>
E fromRaw(const int32 r) { return static_cast<E>(r); }

template<typename E, class = typename std::enable_if<std::is_enum<E>::value>::type>
int32 toRaw(const E e) { return static_cast<int32>(e); }

template<typename T, class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
void LOG(const char *filename,const int32 line,const char *temp,const T value) {
	TJBox_Value vals[1];
	vals[0]=JBox_MakeNumber(value);
	JBox_TraceValues(filename,line,temp,vals,1);
}

void trace(const char *tmpl);
void trace(const char *tmpl,const float32 value);
void trace(const char *tmpl,const float32 value1,const float32 value2);
}




#endif /* BASE_HPP_ */
