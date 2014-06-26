/*
 * streaming.cpp
 *
 *  Created on: 4 Mar 2014
 *      Author: sfriston
 */

#include "streaming.h"
#include <memory.h>
#include <errno.h>
#include <algorithm>

Stream::Stream(max_engine_t* engine, const char* stream_name, int update_size)
{
	SLOT_SIZE = std::max(16, update_size);
	NUM_SLOTS = 100;

	write_buffer = NULL;
	if(posix_memalign(&write_buffer, 4096, SLOT_SIZE * NUM_SLOTS) == ENOMEM){
		printf("Could not allocate memory.");
	}
	memset(write_buffer,0,SLOT_SIZE*NUM_SLOTS);
	write_llstream = 0;
	write_llstream = max_llstream_setup(engine, stream_name, NUM_SLOTS, SLOT_SIZE, write_buffer);

}

Stream::~Stream()
{
	max_llstream_release(write_llstream);
}

bool Stream::Write(void* update)
{
	void* write_ptr;

	if(max_llstream_write_acquire(write_llstream, 1, &write_ptr))
	{
		memcpy(write_ptr, update, SLOT_SIZE);
		max_llstream_write(write_llstream, 1);

		return true;
	}

	return false;
}


