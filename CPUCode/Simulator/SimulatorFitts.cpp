#include <stdio.h>
#include <MaxVideoCpuResources.h>
#include <iostream>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

#include "Simulators.h"

#include "Delay.h"
#include "Logging.h"
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


void SimulatorFitts::MainLoop()
{
	std::cout << "Beginning main loop Fitts Law Test Simulator" << std::endl;

	Mouse mouse;

	/* Configure the card and start the kernel running */

	max_file_t* maxfile = LatencyInteractionExperiment_init();
	max_engine_t* engine = max_load(maxfile, "local:*");
	max_actions_t* actions = max_actions_init(maxfile, "default");

	bool IsSimulation = max_get_constant_uint64t(maxfile,"IS_SIMULATION");

	VirtualMonitor monitor(maxfile);

	if(IsSimulation){
		monitor.Connect(engine);
	}

	mouse.Scale = 0.4f;


	Plane plane_0("plane_0", engine, maxfile);
	plane_0.SetPlaneContent("/home/sfriston/Experiments/Bezier_700.gif");
	plane_0.UpdatePlaneContent(); //this will cause a reset


	Sprite sprite_0("sprite_0",engine,maxfile,256,256);
	Sprite sprite_1("sprite_1",engine,maxfile,256,256);
	Sprite sprite_2("sprite_2",engine,maxfile,256,256);

	max_disable_validation(actions); //we wont have set the sprite content yet.
	max_run(engine, actions);

	/* This object will control the logic of the Fitts Law Tests */

	FittsLawTestRunner runner(sprite_0, sprite_1);

	/* This will control the cursor sprite */

	Cursor cursor(sprite_2);

	/* This will control the input device, reading it and storing a history of its state so that delayed input
	 * may be provided to the tests */

	DelayedInputController input_controller(0.060f,1000,mouse);

	/* This object will load the conditions that drive the state of the tests */

	FittsLawTestConditionLoader loader;
	std::vector<FittsLawTestCondition*> conditions = loader.LoadCSV("/home/sfriston/Experiments/fittsLawConditions.csv");
	std::vector<FittsLawTestCondition*>::iterator conditions_interator = conditions.begin();

	MouseState last_input;

	while(do_simulation()){

		monitor.Refresh(1066);

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

		/* Update returns true when the test is complete, so load the next one until all are exhausted */

		if(runner.Update(input.x,input.y, input.lmb)){

			runner.Begin(*conditions_interator);
			conditions_interator++;

			if(conditions_interator == conditions.end()){
				std::cout << "All Conditions Complete." << std::endl;
				do_simuation(false);

				break;
			}

			logger.AddNewLog(Log("unknown",0,*(runner.condition)));
		}

		logger.CurrentLog().Add(Datapoint(real,input));

	}

	logger.Save(); //saves to the default directory with an unused filename
	logger.Clear();

	max_actions_free(actions);

	max_reset_engine(engine);

//	max_unlock(engine);
//	max_unload(engine);

}
