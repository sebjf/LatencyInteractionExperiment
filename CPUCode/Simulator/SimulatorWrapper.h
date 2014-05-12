/*
 * SimulatorWrapper.h
 *
 *  Created on: 21 Mar 2014
 *      Author: sfriston
 */

#ifndef SIMULATORWRAPPER_H_
#define SIMULATORWRAPPER_H_

#include <pthread.h>
#include "Simulators.h"

#include <iostream>

class SimulatorWrapper
{
public:
	SimulatorWrapper()
	 :thread_running(false)
	{}

	/* This one creates the thread the simulator will run in and returns immediately */

	void RunSimulation(Simulator* simulator);
	void StopSimulation();

private:
	Simulator* simulator;
	pthread_t thread_info;
	bool thread_running;

	/* This will be called in a new thread */
	static void* SimulationMainLoop(void* c);
};

#endif /* SIMULATORWRAPPER_H_ */
