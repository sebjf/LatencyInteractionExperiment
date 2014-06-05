/*
 * SimulatorSteering.cpp
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#include <stdio.h>
#include <MaxVideoCpuResources.h>
#include <iostream>

#include "Simulators.h"
#include "Delay.h"
#include "Logging.h"
#include <Steering/SteeringLawTest.h>
#include <Steering/SteeringConditionBuilder.h>
#include <Graphics/Sprite.h>
#include <Graphics/Plane.h>
#include <Graphics/Cursor.h>

void SimulatorSteering::MainLoop()
{
	std::cout << "Beginning main loop Steering Law Test Simulator" << std::endl;

	/* This object will control the logic of the Fitts Law Tests */

	SteeringLawTestRunner runner(m_resources.plane_0, m_resources.sprite_0);

	/* This will control the cursor sprite */

	Cursor cursor(m_resources.sprite_2);
	Cursor bc(m_resources.sprite_0);

	/* This will control the input device, reading it and storing a history of its state so that delayed input
	 * may be provided to the tests */

	DelayedInputController input_controller(0.060f,1000,m_resources.mouse);

	/* This object will load the conditions that drive the state of the tests */

	std::vector<SteeringLawTestCondition*>::iterator conditions_interator = m_conditions.m_conditions.begin();

	MouseState last_input;

	//runner.m_ball_cursor = &bc;

	while(do_simulation()){

		m_resources.monitor.Refresh(1066);

		input_controller.Update();
		MouseState real  = input_controller.GetCurrentState();
		MouseState input = input_controller.GetState(runner.GetDelay());

		/* This loop runs at ~ 1/60us /s (very fast), and will quickly saturate the pci-ex link, computer memory and make
		 * handling the large amount of data in the logs difficult. So we only do all of the above when the user input
		 * state has changed, and rely on the timestamp for correct analysis of the data later on */

		if(input.Equals(last_input)){
			continue;
		}

		last_input = input;

		cursor.Update(input.x, input.y);
		//bc.Update(100, 100);

		/* Update returns true when the test is complete, so load the next one until all are exhausted */

		if(runner.Update(input.x,input.y)){

			runner.Begin(*conditions_interator);
			conditions_interator++;

			if(conditions_interator == m_conditions.m_conditions.end()+1){
				std::cout << "All Conditions Complete." << std::endl;
				do_simuation(false);

				break;
			}

		//	logger.AddNewLog(Log("unknown",0,*(runner.condition)));
		}

		//logger.CurrentLog().Add(Datapoint(real,input));

	}

}
