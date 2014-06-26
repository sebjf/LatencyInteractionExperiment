/*
 * Simulators.h
 *
 *  Created on: 21 Mar 2014
 *      Author: sfriston
 */

#ifndef SIMULATORS_H_
#define SIMULATORS_H_

#include "Simulator.h"

class BasicSimulator : public Simulator
{
public:
	BasicSimulator(Resources& resources, Logger& logger)
	:Simulator(resources, logger),
	 thread_running(false)
	{}

	virtual void Start();
	virtual void Stop();

	virtual void MainLoop()=0;

private:
	pthread_t thread_info;
	bool thread_running;

	/* This will be called in a new thread */
	static void* SimulationMainLoop(void* c);
};

#endif /* SIMULATORS_H_ */
