
#include "Simulators.h"
#include <MaxVideoCpuResources.h>
#include "Maxfiles.h"
#include "MaxSLiCInterface.h"
#include "../Experiment/experiment.h"
#include <stdio.h>
#include "Sprite.h"
#include "FittsLawTest.h"

struct InputUpdate
{
	uint x;
	uint y;
	uint padding;
	uint padding2;
};

void SimulatorOne::MainLoop()
{
	std::cout << "Beginning main loop Simulator One" << std::endl;

	Mouse* mouse = new Mouse();

	/* Configure the card and start the kernel running */

	max_file_t* maxfile = LatencyInteractionExperiment_init();
	max_engine_t* engine = max_load(maxfile, "local:*");
	max_actions_t* actions = max_actions_init(maxfile, "default");

	bool IsSimulation = max_get_constant_uint64t(maxfile,"IS_SIMULATION");

	std::cout << "Setting Memory..." << std::endl;

	SDL_Surface* img = SDL_LoadBMP("test1.bmp");
	if(img == NULL){
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	Sprite* sprite_0 = new Sprite("sprite_0",engine,maxfile,256,256);

	SDL_BlitSurface(img,NULL,sprite_0->surface,NULL);
	sprite_0->UpdateSpriteContent(actions);

	VirtualMonitor* monitor = new VirtualMonitor(maxfile);

	if(IsSimulation){
		monitor->Connect(engine);
	}

	Stream* inputStream = new Stream(engine,"positions",sizeof(InputUpdate));

	InputUpdate update;
	update.x = 0;
	update.y = 0;

	max_run(engine, actions);

	mouse->Scale = 0.4f;

	float x = 0;
	float y = 0 ;

	while(DoSimulation){
		MouseDelta m = mouse->readMouse(false);

		x += m.x;
		y += m.y;

		sprite_0->properties.a = 127;
		sprite_0->properties.x = x;
		sprite_0->properties.y = y;
		sprite_0->UpdateSpriteProperties();

		monitor->Refresh(1066);
	}

}
