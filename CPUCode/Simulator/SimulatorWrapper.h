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
	SimulatorWrapper(bool isSim)
	{
		/* Refers to whether this is running on hardware or cpu... */
		isSimulation = isSim;
	}

	/* This one creates the thread the simulator will run in and returns immediately */
	void RunSimulation(Simulator* simulator)
	{
		std::cout << "Starting simulator...\n";

		this->simulator = simulator;
		int res = pthread_create(&threadInfo, NULL, &SimulatorWrapper::SimulationMainLoop, this);
		if(res != 0){
			std::cout << "Could not create thread: " << strerror(res) << "\n";
		}
	}

	void StopSimulation()
	{
		std::cout << "Stopping simulator...";

		void* returnStatus;
		simulator->DoSimulation = false;
		pthread_join(threadInfo, &returnStatus);

		std::cout << "Shutdown Complete.\n";
	}

	pthread_t threadInfo;
	bool isSimulation;

private:
	Simulator* simulator;

	/* This will be called in a new thread */

	static void* SimulationMainLoop(void* c)
	{
		makeRealtime();

		std::cout << "Started.\n";

		SimulatorWrapper* wrapper = (SimulatorWrapper*)c;
		Simulator* simulator = wrapper->simulator;

		simulator->IsSimulation = wrapper->isSimulation;
		simulator->DoSimulation = true;
		simulator->MainLoop();

		pthread_exit(NULL);
		return NULL;
	}
};

#endif /* SIMULATORWRAPPER_H_ */
