/*
 * Mouse.h
 *
 *  Created on: 20 Jan 2014
 *      Author: sfriston
 */

#ifndef MOUSE_H_
#define MOUSE_H_

#include <stdio.h>

struct MouseEvent
{
	char flags;
	char x;
	char y;
};

/* Low Latency Input from Mouse Device - Set the Polling Rate to 1kHz before using this */

struct MouseDelta{
	float x;
	float y;
	bool lmb;
};

class Mouse
{
public:
	Mouse(bool invert_y);
	~Mouse();
	struct MouseDelta readMouse(bool block);
	float Scale;
	bool InvertY;

private:
	FILE* mouse;
	bool mouseInputAvailable();
};


#endif /* MOUSE_H_ */
