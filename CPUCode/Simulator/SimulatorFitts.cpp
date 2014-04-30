
#include "Simulators.h"
#include <MaxVideoCpuResources.h>
#include "Maxfiles.h"
#include "MaxSLiCInterface.h"
#include "../Experiment/experiment.h"
#include <stdio.h>
#include "Sprite.h"
#include "FittsLawTest.h"
#include "Delay.h"

struct InputUpdate
{
	uint x;
	uint y;
	uint padding;
	uint padding2;
};

class Cursor
{
public:
	Cursor(Sprite* sprite)
	{
		this->sprite = sprite;
		SDL_Surface* target_texture = SDL_CreateRGBSurface(0,50,50, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
		SDL_FillRect(target_texture, NULL, SDL_MapRGBA(target_texture->format, 255,255,255,255));
		sprite->SetSpriteSurface(target_texture,5,5);
		sprite->UpdateSpriteContent();
	}

	void Update(int x, int y)
	{
		sprite->SetSpriteCenterLocation(x,y);
		sprite->UpdateSpriteProperties();
	}

private:
	Sprite* sprite;
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


	/* Update the sprite content immediately, even if the sprite is not to be used, or will be overridden
	 * immediately, just so the memory is set so max_run() can start */

	sprite_0->UpdateSpriteContent(actions);
	sprite_1->UpdateSpriteContent(actions);
	sprite_2->UpdateSpriteContent(actions);

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

	while(DoSimulation){

		input_controller->Update();
		MouseState input = input_controller->GetState(runner->GetDelay());

		cursor->Update(input.x, input.y);

		/* Update returns true when the test is complete, so load the next one until all are exhausted */

		if(runner->Update(input.x,input.y, input.lmb)){

			runner->Begin(*conditions_interator);
			conditions_interator++;

			if(conditions_interator == conditions.end()){
				std::cout << "All Conditions Complete." << std::endl;
				DoSimulation = false;

				return;
			}
		}

		monitor->Refresh(1066);
	}

}
