/*
 * SimulatorSteering.cpp
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#include <stdio.h>
#include <iostream>
#include "SimulatorSteering.h"
#include "Delay.h"
#include <Steering/SteeringLawTest.h>
#include <Steering/SteeringConditionBuilder.h>
#include <Graphics/Sprite.h>
#include <Graphics/Plane.h>
#include <Graphics/Cursor.h>

 void SimulatorSteering::Initialise()
 {
	std::cout << "Beginning main loop Steering Law Test Simulator" << std::endl;

	/* BASIC MOUSE INPUT */
	m_resources.input_controller.input_device = &(m_resources.mouse);

	/* This object will control the logic of the Fitts Law Tests */

	m_runner = new SteeringLawTestRunner(m_resources.plane_0, m_resources.sprite_0);

	/* This will control the cursor sprite */

	m_cursor = new Cursor(m_resources.sprite_2, dolatency, 5);
	m_resources.input_controller.ResetHistory();
	m_resources.input_controller.input_device->reset();
 }


 bool SimulatorSteering::Iterate()
 {
	m_resources.monitor.Refresh(1066);

	m_resources.input_controller.Update();
	MouseState real  = m_resources.input_controller.GetCurrentState();
	MouseState input = m_resources.input_controller.GetState(m_runner->GetDelay());

	/* This loop runs at ~ 1/60us /s (very fast), and will quickly saturate the pci-ex link, computer memory and make
	 * handling the large amount of data in the logs difficult. So we only do all of the above when the user input
	 * state has changed, and rely on the timestamp for correct analysis of the data later on */

	if(input.Equals(m_last_input)){
		return true;
	}

	m_last_input = input;

	m_cursor->Update(input.x, input.y);

	/* Update returns true when the test is complete, so load the next one until all are exhausted */

	if(m_runner->Update(input.x,input.y)){

		if(current_test >= (int)m_conditions->m_conditions.size()){
			std::cout << "All Conditions Complete." << std::endl;
			return false;
		}

		SteeringLawTestCondition* condition = (m_conditions->m_conditions)[current_test];
		m_runner->Begin(condition);

		std::cout << "The latency is now " << condition->m_latency_in_ms << " ms." << std::endl;

		current_test++;
	}

	return true;
 }


 void SimulatorSteering::Finish()
 {
	std::cout << "Finished on test: " << current_test << std::endl;

	m_resources.sprite_0.Hide();
	m_resources.sprite_1.Hide();
	m_resources.plane_0.ShowPlane(MAP_DEFAULT);

	delete m_cursor;
	delete m_runner;

 }



