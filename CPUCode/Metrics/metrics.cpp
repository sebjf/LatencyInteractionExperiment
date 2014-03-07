/*
 * metrics.cpp
 *
 *  Created on: 4 Mar 2014
 *      Author: sfriston
 */

#include "metrics.h"

#include <time.h>


PerformanceCounter::PerformanceCounter()
{

}

double PerformanceCounter::GetTimestamp_ms()
{
	timespec time;
	clock_gettime(CLOCK_REALTIME, &time);
	return ((double)time.tv_nsec)/1000000.0f;
}
