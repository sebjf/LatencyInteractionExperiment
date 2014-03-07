/*
 * metrics.h
 *
 *  Created on: 4 Mar 2014
 *      Author: sfriston
 */

#ifndef METRICS_H_
#define METRICS_H_

#include <sys/time.h>

class PerformanceCounter
{
public:
	PerformanceCounter();

	/*Returns the elapsed time since the last call in ms*/
	double GetTimestamp_ms();

private:
	struct timespec starttime;
	struct timespec endtime;
};

#endif /* METRICS_H_ */
