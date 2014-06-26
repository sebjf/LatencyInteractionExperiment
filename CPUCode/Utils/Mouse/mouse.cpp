/*
 * mouse.cpp
 *
 *  Created on: 28 Jan 2014
 *      Author: sfriston
 */

#include "mouse.h"

#include <poll.h>

Mouse::Mouse(bool invert_y)
:Scale(1.0f),
 InvertY(invert_y)
{
	mouse = fopen("/dev/input/mice","rb");
	if(mouse == NULL){
		printf("Could not open mouse. Are you running with elevated permissions?");
	}
};

Mouse::~Mouse()
{
	fclose(mouse);
}

struct MouseDelta Mouse::readMouse(bool block)
{
	struct MouseDelta value;
	value.x = 0;
	value.y = 0;
	value.lmb = false;

	if(mouseInputAvailable() || block){

		struct MouseEvent event;
		int result = fread(&event,sizeof(struct MouseEvent),1,mouse);

		int x = 0;
		int y = 0;

		if(result == 1)
		{
			/*This works because even if the msb in word 1 is removed, the remainder of the counter
			 *is still 2's complement, so when the *signed* char is cast to an int, the integer is created in
			 *2's complement notation*/
			x = ((event.flags & 0x10) << 4) | (int)event.x;
			y = ((event.flags & 0x20) << 3) | (int)event.y;
			value.lmb = (event.flags & 0x1);
		}

		float xscale = Scale;
		float yscale = InvertY ? -Scale : Scale;

		value.x = ((float)x) * xscale;
		value.y = ((float)y) * yscale;
	}

	return value;
}

bool Mouse::mouseInputAvailable()
{
	struct pollfd fds;
	fds.fd = fileno(mouse);
	fds.events = POLLIN;
	int timeout = 0;
	int ret = poll(&fds,1,timeout);
	if(ret > 0){
		if(fds.revents & POLLIN){
			return true;
		}
	}

	return false;
}
