/*
 * SimulatorFitts.h
 *
 *  Created on: 26 Jun 2014
 *      Author: sfriston
 */

#ifndef SIMULATORFITTS_H_
#define SIMULATORFITTS_H_

#include "BasicSimulator.h"
#include <vector>

class Cursor;
class FittsLawTestRunner;
class FittsLawTestCondition;

class SimulatorFitts : public BasicSimulator
{
public:
	SimulatorFitts(Resources& resources)
	 :BasicSimulator(resources)
	{}

	void SetConditions(std::vector<FittsLawTestCondition*>* conditions)
	{
		m_conditions = conditions;
	}

	virtual void Initialise();
	virtual bool Iterate();
	virtual void Finish();

private:
	std::vector<FittsLawTestCondition*>* m_conditions;
	MouseState m_last_input;
	Cursor* m_cursor;
	FittsLawTestRunner* m_runner;
};

#endif /* SIMULATORFITTS_H_ */
