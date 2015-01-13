/*
 * Resources.cpp
 *
 *  Created on: 29 May 2014
 *      Author: sfriston
 */

#include "Resources.h"
#include <Maxfiles.h>
#include <LatencyInteractionExperiment.h>
#include <iostream>


Resources* InitialiseResources()
{
	std::cout << "Initialising resources." << std::endl;

	Mouse* mouse = new Mouse(true);

	/* This will control the input device, reading it and storing a history of its state so that delayed input
	 * may be provided to the tests */

	DelayedInputController* input_controller = new DelayedInputController(0.0060f,2000);

	max_file_t* maxfile = LatencyInteractionExperiment_init();

	max_set_max_runnable_timing_score(maxfile,2000);

	max_engine_t* engine = max_load(maxfile, "local:*");
	max_actions_t* actions = max_actions_init(maxfile, "default");

	bool isSimulation = max_get_constant_uint64t(maxfile,"IS_SIMULATION");

	VirtualMonitor* monitor = new VirtualMonitor(maxfile);

	if(isSimulation){
		monitor->MirrorToFile("/home/sfriston/Experiments/moncapture.raw");
		monitor->Connect(engine);
	}

	Sprite* sprite_0 = new Sprite("sprite_0",engine,maxfile,256,256);
	Sprite* sprite_1 = new Sprite("sprite_1",engine,maxfile,256,256);
	Sprite* sprite_2 = new Sprite("sprite_2",engine,maxfile,256,256);

	Stream* metadata = new Stream(engine,"metadata",16);

	Plane* plane_0 = new Plane("plane_0", engine, maxfile);
	std::string s("/home/sfriston/Experiments/1280x1024.jpg");
	plane_0->SetPlaneContent(s);

	plane_0->UpdatePlaneContent(); //this will cause a reset

	max_set_uint64t(actions, "LatencyInteractionExperimentKernel", "Enable", 1);

	max_set_uint64t(actions, "LatencyInteractionExperimentKernel", "HSyncPolarity", 0);
	max_set_uint64t(actions, "LatencyInteractionExperimentKernel", "VSyncPolarity", 0);

	max_disable_validation(actions); //we wont have set the sprite content yet.
	max_run(engine, actions);

	char* nulldata = new char[16];
	memset(nulldata,0x0,16);
	metadata->Write(nulldata);

	Resources* resources = new Resources(
			mouse,
			input_controller,
			maxfile,
			engine,
			actions,
			sprite_0,
			sprite_1,
			sprite_2,
			plane_0,
			monitor,
			metadata,
			isSimulation);

	return resources;

}

Resources::~Resources()
{
	delete &input_controller;
	delete &mouse;
	delete &monitor;
}
