/*
 * Delay.cpp
 *
 *  Created on: 30 Apr 2014
 *      Author: sfriston
 */

#include "Delay.h"
#include "ts_util.h"
#include <iostream>



DelayedInputController::DelayedInputController(float average_period_ms, float max_delay_ms, Mouse& input_device)
:input_device(input_device)
{
	buffer_length = (int)((max_delay_ms / average_period_ms) * 2.0f);
	buffer_position = 0;

	values = new MouseState[buffer_length]();

	/* Get the current time, this will be the epoch all times are from
	 * in this class (so we can work with ms stored in smaller types
	 * like float throughout) */
	clock_gettime(CLOCK_REALTIME, &starttime);

	acc_x = 0;
	acc_y = 0;
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
	double target_time = getCurrentTimeInMs() - delay_ms;

	int search_position = buffer_position;
	do
	{
		if(values[search_position].timestamp_ms <= target_time){
			//timestamps increase from epoch, so we have found the first timestamp older than the target age
			return values[search_position];
		}
		search_position--;

		if(search_position < 0){
			search_position = buffer_length - 1;
		}

		if(search_position == buffer_position)
		{
			std::cout << "Error: Could not find an Input State old enough. Returning the current one." << std::endl;
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

	MouseDelta m = input_device.readMouse(false);

	acc_x += m.x;
	acc_y += m.y;

	buffer_position++;

	if(buffer_position >= buffer_length)
	{
		buffer_position = 0;
	}

	values[buffer_position].x = (int)acc_x;
	values[buffer_position].y = (int)acc_y;
	values[buffer_position].lmb = m.lmb;
	values[buffer_position].timestamp_ms = getCurrentTimeInMs();
}

std::ostream& operator<< (std::ostream& stream, const MouseState& mousestate)
{
	stream << mousestate.x << "," << mousestate.y << "," << (mousestate.lmb ? 1 : 0) << "," << mousestate.timestamp_ms;
	return stream;
}
