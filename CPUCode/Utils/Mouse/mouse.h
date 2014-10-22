/*
 * Mouse.h
 *
 *  Created on: 20 Jan 2014
 *      Author: sfriston
 */

#ifndef MOUSE_H_
#define MOUSE_H_

#include <stdio.h>
#include <Simulator/Delay.h>

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
	bool valid;
};

class Mouse : public InputDevice
{
public:
	Mouse(bool invert_y);
	virtual ~Mouse();
	struct MouseDelta readMouse(bool block);
	float Scale;
	bool InvertY;

	virtual MouseState readDevice();
	virtual void reset();

private:
	FILE* mouse;
	bool mouseInputAvailable();

	float xpos;
	float ypos;

	int m_mouse_cooldown;
	bool m_mouse_down;
};


#endif /* MOUSE_H_ */
