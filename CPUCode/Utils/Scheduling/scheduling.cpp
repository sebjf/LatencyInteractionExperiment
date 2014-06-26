/*
 * scheduling.cpp
 *
 *  Created on: 31 Jan 2014
 *      Author: sfriston
 */

#include "scheduling.h"

void makeRealtime(){

	sched_param params;
	params.__sched_priority = 99;

	sched_setscheduler(	0,
						SCHED_FIFO,
						&params);

}
