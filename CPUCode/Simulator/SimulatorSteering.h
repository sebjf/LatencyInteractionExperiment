/*
 * SimulatorSteering.h
 *
 *  Created on: 26 Jun 2014
 *      Author: sfriston
 */

#ifndef SIMULATORSTEERING_H_
#define SIMULATORSTEERING_H_

#include "BasicSimulator.h"
#include "SensableSimulator.h"

class SteeringConditionBuilder;
class SteeringLawTestCondition;
class SteeringLawTestRunner;
class PhantomInputDevice;
class Cursor;

class SimulatorSteering : public SensableSimulator
{
public:
	SimulatorSteering(Resources& resources, Logger& logger)
	 :SensableSimulator(resources, logger)
	{}

	virtual void Initialise();
	virtual bool Iterate();
	virtual void Finish();

	void SetConditions(SteeringConditionBuilder& conditions)
	{
		m_conditions = &conditions;
	}

private:
	SteeringConditionBuilder* m_conditions;
	std::vector<SteeringLawTestCondition*>::iterator m_conditions_interator;
	SteeringLawTestRunner* m_runner;
	MouseState m_last_input;
	Cursor* m_cursor;
	PhantomInputDevice* m_phantom_input_device;
};

#endif /* SIMULATORSTEERING_H_ */
