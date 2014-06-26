/*
 * Simulator.cpp
 *
 *  Created on: 26 Jun 2014
 *      Author: sfriston
 */

#include "BasicSimulator.h"
#include <sched.h>

void makeRealtime(){

	sched_param params;
	params.__sched_priority = 99;

	sched_setscheduler(	0,
						SCHED_FIFO,
						&params);

}

void BasicSimulator::Start()
{
	if(thread_running){
		Stop();
	}

	std::cout << "Starting simulator...\n";

	int res = pthread_create(&thread_info, NULL, &BasicSimulator::SimulationMainLoop, this);
	if(res != 0){
		std::cout << "Could not create thread: " << strerror(res) << "\n";
		return;
	}
	thread_running = true;
}

void BasicSimulator::Stop()
{
	if(!thread_running){
		return;
	}

	std::cout << "Stopping simulator...";

	void* returnStatus;
	do_simuation(false);
	pthread_join(thread_info, &returnStatus);

	thread_running = false;

	std::cout << "Shutdown Complete.\n";
}

void* BasicSimulator::SimulationMainLoop(void* c)
{
	makeRealtime();

	std::cout << "Started.\n";

	BasicSimulator* simulator = (BasicSimulator*)c;

	simulator->do_simuation(true);
	simulator->Initialise();
	while(simulator->do_simulation())
	{
		bool b = simulator->Iterate() && simulator->do_simulation();
		simulator->do_simuation( b );
	}
	simulator->Finish();

	pthread_exit(NULL);
	return NULL;
}
