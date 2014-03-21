/*
 * Simulators.h
 *
 *  Created on: 21 Mar 2014
 *      Author: sfriston
 */

#ifndef SIMULATORS_H_
#define SIMULATORS_H_

#include "../Experiment/experiment.h"

class Simulator
{
public:
	virtual void MainLoop() = 0;
	volatile bool IsSimulation;
	volatile bool DoSimulation;
	ExperimentLog* log;
};

class SimulatorOne : public Simulator
{
public:
	virtual void MainLoop();
};

class SimulatorTwo : public Simulator
{
public:
	virtual void MainLoop()
	{
		while(DoSimulation)
		{
			log->Add(Datapoint(10,10));
		}
	}
};

#endif /* SIMULATORS_H_ */
