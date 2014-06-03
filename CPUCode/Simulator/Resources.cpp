/*
 * Resources.cpp
 *
 *  Created on: 29 May 2014
 *      Author: sfriston
 */

#include "Resources.h"
#include "Maxfiles.h"

Resources* InitialiseResources()
{
	std::cout << "Initialising resources." << std::endl;

	Mouse* mouse = new Mouse();
	mouse->Scale = 0.4f;

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
	plane_0->SetPlaneContent("/home/sfriston/Experiments/1280x1024.jpg");

	plane_0->UpdatePlaneContent(); //this will cause a reset

	max_set_uint64t(actions, "LatencyInteractionExperimentKernel", "Enable", 1);

	max_disable_validation(actions); //we wont have set the sprite content yet.
	max_run(engine, actions);

	Resources* resources = new Resources(
			mouse,
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
