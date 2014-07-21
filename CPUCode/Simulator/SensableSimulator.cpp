/*
 * SensableSimulator.cpp
 *
 *  Created on: 26 Jun 2014
 *      Author: sfriston
 */

#include "SensableSimulator.h"

bool SensableSimulator::m_initialised = false;
HHD SensableSimulator::m_device = 0;

SensableSimulator::SensableSimulator(Resources& resources, Logger& logger)
:Simulator(resources, logger)
{
	if(m_initialised == false){
		m_device = hdInitDevice(HD_DEFAULT_DEVICE);
		m_initialised = true;
	}
}

void SensableSimulator::Start()
{
	hdMakeCurrentDevice(m_device);
	m_callbackhandle = hdScheduleAsynchronous(&SensableSimulator::DeviceStateCallback,this,HD_MIN_SCHEDULER_PRIORITY);

	Initialise();

	hdStartScheduler();
}

void SensableSimulator::Stop()
{
	hdStopScheduler();
	hdUnschedule(m_callbackhandle);

	Finish();
}

HDCallbackCode SensableSimulator::DeviceStateCallback(void* pUserData)
{
	SensableSimulator* simulator = (SensableSimulator*)pUserData;

	hdBeginFrame(simulator->m_device);

	HDdouble position[3];
	hdGetDoublev(HD_CURRENT_POSITION, position);
	HDint buttonState;
	hdGetIntegerv(HD_CURRENT_BUTTONS, &buttonState);

	simulator->m_dummy.m_phantom_x = position[0];
	simulator->m_dummy.m_phantom_y = position[2];

	bool b1 = buttonState & HD_DEVICE_BUTTON_1;
	bool b2 = buttonState & HD_DEVICE_BUTTON_2;
	bool b3 = buttonState & HD_DEVICE_BUTTON_3;
	bool b4 = buttonState & HD_DEVICE_BUTTON_4;

	simulator->m_dummy.m_phantom_lmb = (bool)( b1 || b2 || b3 || b4 );

	hdEndFrame(simulator->m_device);

	bool response = simulator->Iterate();

	if(response)
	{
		return HD_CALLBACK_CONTINUE;
	}

	return HD_CALLBACK_DONE;
}


SensableSimulator::~SensableSimulator() {
	// TODO Auto-generated destructor stub
}
