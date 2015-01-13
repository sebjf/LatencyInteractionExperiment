/*
 * Simulators.h
 *
 *  Created on: 21 Mar 2014
 *      Author: sfriston
 */

#ifndef SIMULATORS_H_
#define SIMULATORS_H_

#include "Simulator.h"

void makeRealtime();

class BasicSimulator : public Simulator
{
public:
	BasicSimulator(Resources& resources)
	:Simulator(resources),
	 thread_running(false)
	{}

	virtual void Start();
	virtual void Stop();

	virtual void Initialise()=0;
	virtual bool Iterate()=0;
	virtual void Finish()=0;

private:
	pthread_t thread_info;
	bool thread_running;

	/* This will be called in a new thread */
	static void* SimulationMainLoop(void* c);
};

#endif /* SIMULATORS_H_ */
