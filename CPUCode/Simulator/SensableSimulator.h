/*
 * SensableSimulator.h
 *
 *  Created on: 26 Jun 2014
 *      Author: sfriston
 */

#ifndef SENSABLESIMULATOR_H_
#define SENSABLESIMULATOR_H_

#include "Simulator.h"
#include <HD/hd.h>
#include <Input/SensableDummy.h>

class SensableSimulator : public Simulator {
public:
	SensableSimulator(Resources& resources, Logger& logger);

	virtual void Start();
	virtual void Stop();

	virtual void Initialise()=0;
	virtual bool Iterate()=0;
	virtual void Finish()=0;

	virtual ~SensableSimulator();

	SensableDummy m_dummy;

private:
	static bool m_initialised;
	static HHD m_device;
	HDSchedulerHandle m_callbackhandle;
	static HDCallbackCode DeviceStateCallback(void* pUserData);

	//SensableDummy dummy;

};

#endif /* SENSABLESIMULATOR_H_ */
