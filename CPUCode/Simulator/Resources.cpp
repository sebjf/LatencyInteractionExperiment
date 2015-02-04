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

/* Embedded resources */
extern unsigned int __background_map_size;
extern unsigned char __background_map_data[];

Resources* InitialiseResources(SteeringConditionBuilder& steeringConditions)
{
	std::cout << "Initialising resources." << std::endl;

	Mouse* mouse = new Mouse(true);

	/* This will control the input device, reading it and storing a history of its state so that delayed input
	 * may be provided to the tests */

	DelayedInputController* input_controller = new DelayedInputController(0.0060f,2000);

	input_controller->suppressPeriodWarnings = true;

	max_file_t* maxfile = LatencyInteractionExperiment_init();
	max_engine_t* engine = max_load(maxfile, "local:*");
	max_actions_t* actions = max_actions_init(maxfile, "default");

	bool isSimulation = max_get_constant_uint64t(maxfile,"IS_SIMULATION");

	VirtualMonitor* monitor = new VirtualMonitor(maxfile);

	if(isSimulation){
		monitor->Connect(engine);
	}

	Sprite* sprite_0 = new Sprite("sprite_0",engine,maxfile,256,256);
	Sprite* sprite_1 = new Sprite("sprite_1",engine,maxfile,256,256);
	Sprite* sprite_2 = new Sprite("sprite_2",engine,maxfile,256,256);

	Plane* plane_0 = new Plane("plane_0", engine, maxfile);
	plane_0->SetPlaneContent(__background_map_data, __background_map_size);
	plane_0->SetPlaneContent(steeringConditions.GetMaps(), steeringConditions.GetRefs());

	printf("Loading resources...\n");

	plane_0->UpdatePlaneContent(); //this will cause a reset

	printf("Initialising...\n");

	max_set_uint64t(actions, "MaxVideoSignalKernel", "HSyncPolarity", 1);
	max_set_uint64t(actions, "MaxVideoSignalKernel", "VSyncPolarity", 1);

	max_ignore_lmem(actions,"plane_0_write");

	printf("Starting display engine...\n");

	max_run(engine, actions);

	plane_0->ShowPlane(MAP_DEFAULT);

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
			isSimulation);

	return resources;

}

Resources::~Resources()
{
	delete &input_controller;
	delete &mouse;
	delete &monitor;
}
