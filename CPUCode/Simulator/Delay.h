/*
 * Delay.h
 *
 *  Created on: 30 Apr 2014
 *      Author: sfriston
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <time.h>
#include <ostream>

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

};

class InputDevice
{
public:
	virtual ~InputDevice() {};
	virtual MouseState readDevice() = 0;
	virtual void reset() = 0;
};

class DelayedInputController
{
public:
	DelayedInputController(float average_period_ms, float max_delay);
	MouseState GetState(float delay_ms);
	MouseState GetCurrentState();
	void Update();
	void Reset();
	void ResetHistory();

	InputDevice* input_device;

private:

	int buffer_length;
	int buffer_position;
	MouseState*	values;

	timespec starttime;

	double getCurrentTimeInMs();
};


#endif /* DELAY_H_ */
