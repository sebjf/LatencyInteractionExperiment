/*
 * TestSimulator.h
 *
 *  Created on: 26 Jun 2014
 *      Author: sfriston
 */

#ifndef TESTSIMULATOR_H_
#define TESTSIMULATOR_H_

#include "SensableSimulator.h"

class TestSimulator : public SensableSimulator
{
public:
	TestSimulator(Resources& resources, Logger& logger)
	:SensableSimulator(resources,logger)
	{}

	virtual void Initialise()
	{

	}

	virtual void Finish()
	{

	}

	virtual bool Iterate()
	{
		MouseState s = m_dummy.read();
		std::cout << s.x << " " << s.y << " " << s.lmb << std::endl;
		return true;
	}


};

#endif /* TESTSIMULATOR_H_ */
