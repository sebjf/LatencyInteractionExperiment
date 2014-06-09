/*
 * Delay.h
 *
 *  Created on: 30 Apr 2014
 *      Author: sfriston
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "MaxVideoCpuResources.h"
#include <time.h>
#include <msgpack.hpp>

struct MouseState
{
	int x;
	int y;
	bool lmb;
	float timestamp_ms;

	MouseState()
	{
		x = 0;
		y = 0;
		lmb = false;
	}

	bool Equals(const MouseState& a)
	{
		return (x == a.x) && (y == a.y) && (lmb == a.lmb);
	}

	friend std::ostream& operator<< (std::ostream& stream, const MouseState& mousestate);

	MSGPACK_DEFINE(x,y,lmb,timestamp_ms);
};


class DelayedInputController
{
public:
	DelayedInputController(float average_period_ms, float max_delay, Mouse& input_device);
	MouseState GetState(float delay_ms);
	MouseState GetCurrentState();
	void Update();
	void Reset();
	void ResetHistory();

private:
	Mouse& input_device;

	float acc_x;
	float acc_y;

	int buffer_length;
	int buffer_position;
	MouseState*	values;

	timespec starttime;

	double getCurrentTimeInMs();
};


#endif /* DELAY_H_ */
