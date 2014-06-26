/*
 * SimulatorFitts.h
 *
 *  Created on: 26 Jun 2014
 *      Author: sfriston
 */

#ifndef SIMULATORFITTS_H_
#define SIMULATORFITTS_H_

#include "BasicSimulator.h"

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

	virtual void MainLoop();

private:
	std::vector<FittsLawTestCondition*>* m_conditions;
};

#endif /* SIMULATORFITTS_H_ */
