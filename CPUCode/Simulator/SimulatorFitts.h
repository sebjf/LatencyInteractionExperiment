/*
 * SimulatorFitts.h
 *
 *  Created on: 26 Jun 2014
 *      Author: sfriston
 */

#ifndef SIMULATORFITTS_H_
#define SIMULATORFITTS_H_

#include "BasicSimulator.h"

class Cursor;
class FittsLawTestRunner;
class PhantomInputDevice;

class SimulatorFitts : public BasicSimulator
{
public:
	SimulatorFitts(Resources& resources, Logger& logger)
	 :BasicSimulator(resources, logger)
	{}

	void SetConditions(std::vector<FittsLawTestCondition*>& conditions)
	{
		m_conditions = &conditions;
	}

	virtual void Initialise();
	virtual bool Iterate();
	virtual void Finish();

private:
	std::vector<FittsLawTestCondition*>* m_conditions;
	std::vector<FittsLawTestCondition*>::iterator m_conditions_interator;
	MouseState m_last_input;
	Cursor* m_cursor;
	FittsLawTestRunner* m_runner;
	PhantomInputDevice* m_phantom_input_device;
};

#endif /* SIMULATORFITTS_H_ */
