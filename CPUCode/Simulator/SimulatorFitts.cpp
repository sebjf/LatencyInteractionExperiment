#include <stdio.h>
#include <MaxVideoCpuResources.h>
#include <iostream>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

#include "Simulators.h"
#include "Sprite.h"
#include "FittsLawTest.h"
#include "Delay.h"
#include "Logging.h"

struct InputUpdate
{
	uint x;
	uint y;
	uint padding;
	uint padding2;
};

class Cursor
{
private:
	Sprite* const m_sprite;

public:
	Cursor(Sprite* sprite)
		:m_sprite(sprite)
	{
		SDL_Surface* target_texture = SDL_CreateRGBSurface(0,50,50, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
		SDL_FillRect(target_texture, NULL, SDL_MapRGBA(target_texture->format, 255,255,255,255));
		m_sprite->SetSpriteSurface(target_texture,5,5);
		m_sprite->UpdateSpriteContent();
	}

	void Update(int x, int y)
	{
		m_sprite->SetSpriteCenterLocation(x,y);
		m_sprite->UpdateSpriteProperties();
	}
};

void SimulatorFitts::MainLoop()
{
	std::cout << "Beginning main loop Fitts Law Test Simulator" << std::endl;

	Mouse* mouse = new Mouse();

	/* Configure the card and start the kernel running */

	max_file_t* maxfile = LatencyInteractionExperiment_init();
	max_engine_t* engine = max_load(maxfile, "local:*");
	max_actions_t* actions = max_actions_init(maxfile, "default");

	bool IsSimulation = max_get_constant_uint64t(maxfile,"IS_SIMULATION");

	VirtualMonitor* monitor = new VirtualMonitor(maxfile);

	if(IsSimulation){
		monitor->Connect(engine);
	}

	mouse->Scale = 0.4f;

	Sprite* sprite_0 = new Sprite("sprite_0",engine,maxfile,256,256);
	Sprite* sprite_1 = new Sprite("sprite_1",engine,maxfile,256,256);
	Sprite* sprite_2 = new Sprite("sprite_2",engine,maxfile,256,256);


	max_disable_validation(actions); //we wont have set the sprite content yet.

	max_run(engine, actions);

	/* This object will control the logic of the Fitts Law Tests */

	FittsLawTestRunner* runner = new FittsLawTestRunner(sprite_0, sprite_1);

	/* This will control the cursor sprite */

	Cursor* cursor = new Cursor(sprite_2);

	/* This will control the input device, reading it and storing a history of its state so that delayed input
	 * may be provided to the tests */

	DelayedInputController* input_controller = new DelayedInputController(0.060f,500,mouse);

	/* This object will load the conditions that drive the state of the tests */

	FittsLawTestConditionLoader loader;
	std::vector<FittsLawTestCondition*> conditions = loader.LoadCSV(std::string("fittsLawConditions.csv"));
	std::vector<FittsLawTestCondition*>::iterator conditions_interator = conditions.begin();

	Logger* logger = new Logger("\\home\\sfriston\\Experiments\\","fitts_law_log_collection_");

	while(do_simulation()){

		input_controller->Update();
		MouseState real = input_controller->GetCurrentState();
		MouseState input = input_controller->GetState(runner->GetDelay());

		cursor->Update(input.x, input.y);

		/* Update returns true when the test is complete, so load the next one until all are exhausted */

		if(runner->Update(input.x,input.y, input.lmb)){

			runner->Begin(*conditions_interator);
			conditions_interator++;

			if(conditions_interator == conditions.end()){
				std::cout << "All Conditions Complete." << std::endl;
				do_simuation(false);

				return;
			}

		//	logger->AddNewLog(*(new Log("unknown",0,runner->condition)));
		}

		Datapoint dp = Datapoint(real,input);
		//logger->CurrentLog().Add(dp);

		monitor->Refresh(1066);
	}

}
