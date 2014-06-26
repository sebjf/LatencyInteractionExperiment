/*
 * SimulatorSteering.h
 *
 *  Created on: 26 Jun 2014
 *      Author: sfriston
 */

#ifndef SIMULATORSTEERING_H_
#define SIMULATORSTEERING_H_

#include "BasicSimulator.h"

class SteeringConditionBuilder;

class SimulatorSteering : public BasicSimulator
{
public:
	SimulatorSteering(Resources& resources, Logger& logger)
	 :BasicSimulator(resources, logger)
	{}

	virtual void MainLoop();

	void SetConditions(SteeringConditionBuilder& conditions)
	{
		m_conditions = &conditions;
	}

private:
	SteeringConditionBuilder* m_conditions;
};

#endif /* SIMULATORSTEERING_H_ */
