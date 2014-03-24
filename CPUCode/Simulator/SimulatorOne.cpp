
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



void SimulatorOne::MainLoop()
{
	Mouse* mouse = new Mouse();

	/* Configure the card and start the kernel running */
	max_file_t* maxfile = LatencyInteractionExperiment_init();
	max_engine_t* engine = max_load(maxfile, "local:*");
	max_actions_t* actions = max_actions_init(maxfile, "default");


	std::cout << "Setting Memory...\n";

	int numMemElements = 256 * 256;
	int memElementSize = 4;

	int memSizeInBytes = numMemElements * memElementSize;
	int memSizeInWords = memSizeInBytes / sizeof(uint64_t);

	uint64_t* memData = (uint64_t*)malloc(numMemElements * memElementSize);
	memset(memData, 0, memSizeInBytes);

	max_set_mem_range_uint64t(actions, "LatencyInteractionExperimentKernel", "sprite_0", memSizeInWords, 0, memData);



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
