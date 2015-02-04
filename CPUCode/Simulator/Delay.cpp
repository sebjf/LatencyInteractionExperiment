/*
 * Delay.cpp
 *
 *  Created on: 30 Apr 2014
 *      Author: sfriston
 */

#include "Delay.h"
#include <Utils/ts_util.h>
#include <iostream>
#include <limits>
#include <stdlib.h>



DelayedInputController::DelayedInputController(float average_period_ms, float max_delay_ms)
:input_device(NULL)
{
	buffer_length = (int)((max_delay_ms / average_period_ms) * 1.2f);
	values = new MouseState[buffer_length]();

	suppressPeriodWarnings = false;

	ResetHistory();
}

/*resets everything*/
void DelayedInputController::Reset()
{
	input_device->reset();
}

/*resets the history but not the position */
void DelayedInputController::ResetHistory()
{
	/* Get the current time, this will be the epoch all times are from
	 * in this class (so we can work with ms stored in smaller types
	 * like float throughout) */

	clock_gettime(CLOCK_REALTIME, &starttime);
	buffer_position = 0;

	for(int i = 0; i < buffer_length; i++)
	{
		values[i].timestamp_ms = std::numeric_limits<float>::max();
	}
}

/* Gets the number of ms that have elapsed since the class was created. */
double DelayedInputController::getCurrentTimeInMs()
{
	timespec currenttime;
	clock_gettime(CLOCK_REALTIME, &currenttime);
	return tsFloat(tsSubtract(currenttime, starttime)) * 1000.0f;
}

MouseState DelayedInputController::GetState(float delay_ms)
{
	if(delay_ms == 0){
	//	return GetCurrentState();
	}

	double target_time = getCurrentTimeInMs() - delay_ms;

	int search_position = buffer_position;
	do
	{
		if(values[search_position].timestamp_ms <= target_time){
			//timestamps increase from epoch, so we have found the first timestamp older than the target age

			float dt = target_time - values[search_position].timestamp_ms;

			if(abs(dt) > 0.060){
				if(!suppressPeriodWarnings){
					std::cout << "dt of " << dt << " is greater than average period." << std::endl;
				}
			}

			return values[search_position];
		}
		search_position--;

		if(search_position < 0){
			search_position = buffer_length - 1;
		}

		if(search_position == buffer_position)
		{
			if(!suppressPeriodWarnings){
				std::cout << "Error: Could not find an Input State old enough. Returning the current one." << std::endl;
			}
			return values[search_position];
		}

		/* so long as delay_ms is relative to the current time, the only way this should be able to get stuck is if
		 * the execution time of the loop drops preciptiously */
	}while(1);

}

MouseState DelayedInputController::GetCurrentState()
{
	return values[buffer_position];
}

void DelayedInputController::Update()
{
	/* Using the latest data from the mouse, timestamp and write the state of the input device at this point in time */

	if(!input_device)
	{
		std::cout << "Input Device must be provided before calling update." << std::endl;
	}

	MouseState m = input_device->readDevice();

	buffer_position++;

	if(buffer_position >= buffer_length)
	{
		buffer_position = 0;
	}

	values[buffer_position].x = m.x;
	values[buffer_position].y = m.y;
	values[buffer_position].lmb = m.lmb;
	values[buffer_position].timestamp_ms = getCurrentTimeInMs();

/*	if(buffer_position > 0){
		std::cout << values[buffer_position].timestamp_ms - values[buffer_position-1].timestamp_ms << std::endl;
	}*/
}

std::ostream& operator<< (std::ostream& stream, const MouseState& mousestate)
{
	stream << mousestate.x << "," << mousestate.y << "," << (mousestate.lmb ? 1 : 0) << "," << mousestate.timestamp_ms;
	return stream;
}
