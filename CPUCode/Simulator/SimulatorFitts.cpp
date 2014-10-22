
#include <stdio.h>
#include "SimulatorFitts.h"
#include <iostream>
#include "MaxSLiCInterface.h"
#include "Delay.h"
#include "Logging.h"
#include <Fitts/FittsLawTest.h>
#include <Graphics/Sprite.h>
#include <Graphics/Plane.h>
#include <Graphics/Cursor.h>
#include <Input/SensableDummy.h>

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

	/* BASIC INPUT */
	m_phantom_input_device = new PhantomInputDevice(&m_resources.phantom);
	m_resources.input_controller.input_device = m_phantom_input_device;

	/* SENSABLE INPUT */
//	m_resources.input_controller.input_device = &m_dummy;

	/*Set the background for Fitts Test*/

	m_resources.plane_0.ShowPlane(MAP_BLACK);

	/* This object will control the logic of the Fitts Law Tests */

	m_runner = new FittsLawTestRunner(m_resources.sprite_0, m_resources.sprite_1);

	/* This will control the cursor sprite */

	m_cursor = new Cursor(m_resources.sprite_2);
	m_resources.input_controller.ResetHistory();

	current_test = 0;

}

bool SimulatorFitts::Iterate()
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

	if(flag == 1)
	{
		flag = 0;

		char* d = new char[16];
		for(int i = 0; i < 16; i++)
		{
			if(i < 0)
			d[i] = 255;
			else
			d[i] = 255;
		}
		if(m_resources.metadata.Write(d)){
		std::cout << "Trigger";
		}
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

		m_logger.AddNewLog(Log(m_logger.GetParticipantId(), condition->m_filename,Fitts,condition->m_condition_id));
		m_runner->Begin(condition);

		current_test++;
	}

	m_logger.CurrentLog().Add(Datapoint(real,input));

	return true;
}

void SimulatorFitts::Finish()
{
	m_logger.Save(); //saves to the default directory with an unused filename
	m_logger.Clear();

	m_resources.sprite_0.Hide();
	m_resources.sprite_1.Hide();

	delete m_cursor;
	delete m_runner;
	delete m_phantom_input_device;
}
