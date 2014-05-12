/*
 * SimulatorWrapper.cpp
 *
 *  Created on: 7 May 2014
 *      Author: sfriston
 */

#include "SimulatorWrapper.h"
#include "MaxVideoCpuResources.h"

/* This one creates the thread the simulator will run in and returns immediately */
void SimulatorWrapper::RunSimulation(Simulator* simulator)
{
	if(thread_running){
		StopSimulation();
	}

	std::cout << "Starting simulator...\n";

	this->simulator = simulator;
	int res = pthread_create(&thread_info, NULL, &SimulatorWrapper::SimulationMainLoop, this);
	if(res != 0){
		std::cout << "Could not create thread: " << strerror(res) << "\n";
		return;
	}
	thread_running = true;
}

void SimulatorWrapper::StopSimulation()
{
	if(!thread_running){
		return;
	}

	std::cout << "Stopping simulator...";

	void* returnStatus;
	simulator->do_simuation(false);
	pthread_join(thread_info, &returnStatus);

	thread_running = false;

	std::cout << "Shutdown Complete.\n";
}

void* SimulatorWrapper::SimulationMainLoop(void* c)
{
	makeRealtime();

	std::cout << "Started.\n";

	SimulatorWrapper* wrapper = (SimulatorWrapper*)c;
	Simulator* simulator = wrapper->simulator;

	simulator->do_simuation(true);
	simulator->MainLoop();

	pthread_exit(NULL);
	return NULL;
}

