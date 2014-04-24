
#include "Simulators.h"
#include <MaxVideoCpuResources.h>
#include "Maxfiles.h"
#include "MaxSLiCInterface.h"
#include "../Experiment/experiment.h"
#include <stdio.h>

struct InputUpdate
{
	uint x;
	uint y;
	uint padding;
	uint padding2;
};

struct memword
{
	char r;
	char g;
	char b;
	char a;
	uint32_t padding;
};

void SimulatorOne::MainLoop()
{
	std::cout << "Beginning main loop Simulator One\n";

	Mouse* mouse = new Mouse();

	/* Configure the card and start the kernel running */
	max_file_t* maxfile = LatencyInteractionExperiment_init();
	max_engine_t* engine = max_load(maxfile, "local:*");
	max_actions_t* actions = max_actions_init(maxfile, "default");

	bool IsSimulation = max_get_constant_uint64t(maxfile,"IS_SIMULATION");

	if(IsSimulation){
		std::cout << "Running in simulation mode. " << max_get_constant_uint64t(maxfile,"IS_SIMULATION");
	}

	std::cout << "Setting Memory...\n";

	int numMemElements = 256 * 256;

	memword* memData = (new memword[numMemElements]);

	for(int i = 0; i < numMemElements; i++){
		memData[i].r = 0;
		memData[i].g = 255;
		memData[i].b = 0;
		memData[i].a = 127;
	}

	max_set_mem_range_uint64t(actions, "LatencyInteractionExperimentKernel", "sprite_0", 0, numMemElements, (uint64_t*)memData);
/*
	for(int i = 0; i < memSizeInWords; i++){
		max_set_mem_uint64t(actions, "LatencyInteractionExperimentKernel", "sprite_0", i, memData[i]);
	}
*/

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

		update.x = (int)x;
		update.y = (int)y;

		inputStream->Write(&update);

		monitor->Refresh(1066);
	}

}
