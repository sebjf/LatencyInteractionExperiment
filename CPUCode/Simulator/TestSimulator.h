/*
 * TestSimulator.h
 *
 *  Created on: 26 Jun 2014
 *      Author: sfriston
 */

#ifndef TESTSIMULATOR_H_
#define TESTSIMULATOR_H_

#include "SensableSimulator.h"
#include <Input/PhantomInputDevice.h>

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

class TestPhantomSimulator : public BasicSimulator
{
public:
	TestPhantomSimulator(Resources& resources, Logger& logger)
	:BasicSimulator(resources,logger)
	{}
	virtual void Initialise()
	{
		m_device = new PhantomInputDevice(&m_resources.phantom);
	}

	virtual void Finish()
	{
		delete m_device;
	}

	virtual bool Iterate()
	{
		MouseState s = m_device->read();
		std::cout << s.x << " " << s.y << " " << s.lmb << std::endl;
		return true;
	}

	PhantomInputDevice* m_device;

};


#endif /* TESTSIMULATOR_H_ */
