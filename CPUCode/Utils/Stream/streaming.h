/*
 * streaming.h
 *
 *  Created on: 4 Mar 2014
 *      Author: sfriston
 */

#ifndef STREAMING_H_
#define STREAMING_H_

#include "MaxSLiCInterface.h"

/* Simple interface for sending updates using low latency streams */

class Stream
{
public:
	Stream(max_engine_t* engine, const char* stream_name, int update_size);
	~Stream();
	bool Write(void* update);

private:
	void* write_buffer;
	max_llstream_t* write_llstream;
	size_t SLOT_SIZE;
	size_t NUM_SLOTS;
};

#endif /* STREAMING_H_ */
