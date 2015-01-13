
#include <stdio.h>
#include "SimulatorFitts.h"
#include <iostream>
#include "MaxSLiCInterface.h"
#include "Delay.h"
#include <Fitts/FittsLawTest.h>
#include <Graphics/Sprite.h>
#include <Graphics/Plane.h>
#include <Graphics/Cursor.h>

struct InputUpdate
{
	uint x;
	uint y;
	uint padding;
	uint padding2;
};

void SimulatorFitts::Initialise()
{
	makeRealtime();

	std::cout << "Beginning main loop Fitts Law Test Simulator" << std::endl;

	/* BASIC MOUSE INPUT */
	m_resources.input_controller.input_device = &(m_resources.mouse);

	/*Set the background for Fitts Test*/

	m_resources.plane_0.ShowPlane(MAP_BLACK);

	/* This object will control the logic of the Fitts Law Tests */

	m_runner = new FittsLawTestRunner(m_resources.sprite_0, m_resources.sprite_1);

	/* This will control the cursor sprite */

	m_cursor = new Cursor(m_resources.sprite_2, dolatency, 2);
	m_resources.input_controller.ResetHistory();
	m_resources.input_controller.input_device->reset();

}

bool SimulatorFitts::Iterate()
{
	m_resources.monitor.Refresh(1066);

	m_resources.input_controller.Update();
	MouseState real  = m_resources.input_controller.GetCurrentState();
	MouseState input = m_resources.input_controller.GetState(m_runner->GetDelay());

	/* The input controller samples so fast (0.006ms) that quantisation noise in the the timing during the search for the
	 * delayed value can result in the lmb being missed. */
	//input.lmb = real.lmb;

	/* This loop runs at ~ 1/60us /s (very fast), and will quickly saturate the pci-ex link, computer memory and make
	 * handling the large amount of data in the logs difficult. So we only do all of the above when the user input
	 * state has changed, and rely on the timestamp for correct analysis of the data later on */

	if(input.Equals(m_last_input)){
		return true;
	}

	m_last_input = input;

	m_cursor->Update(input.x, input.y);

	//std::cout << input.x << " " << input.y << std::endl;

	/* Update returns true when the test is complete, so load the next one until all are exhausted */

	if(m_runner->Update(input.x,input.y, input.lmb)){

		if(current_test >= m_conditions->size()){
			std::cout << "All Conditions Complete." << std::endl;
			return false;
		}

		FittsLawTestCondition* condition = (*m_conditions)[current_test];

		m_runner->Begin(condition);

		current_test++;
	}

	return true;
}

void SimulatorFitts::Finish()
{
	std::cout << "Finished on test: " << current_test << std::endl;

	m_resources.sprite_0.Hide();
	m_resources.sprite_1.Hide();

	delete m_cursor;
	delete m_runner;
}
