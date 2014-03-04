#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

#include <MaxVideoCpuResources.h>

#include <stdio.h>

struct InputUpdate
{
	uint x;
	uint y;
	uint padding;
	uint padding2;
};

int main(int argc, char *argv[])
{

	if(isSim(argc,argv)){
		printf("Running Simulation.");
	}

	makeRealtime();

	Mouse* mouse = new Mouse();

	VirtualMonitor* monitor = new VirtualMonitor(1688,1066);

	/* Configure the card and start the kernel running */
	max_file_t* maxfile = LatencyInteractionExperiment_init();
	max_engine_t* engine = max_load(maxfile, "local:*");
	max_actions_t* actions = max_actions_init(maxfile, "default");

	if(isSim(argc,argv)){
		monitor->Connect(engine);
	}

	Stream* inputStream = new Stream(engine,"positions",sizeof(InputUpdate));

	InputUpdate update;
	update.x = 0;
	update.y = 0;

	max_run(engine, actions);

	while(1){
		MouseDelta m = mouse->readMouse(false);

		update.x += m.x;
		update.y += m.y;

		inputStream->Write(&update);

		monitor->Refresh(1066);

		if(keyboardInputAvailable()){
			break;
		}
	}

	printf("Done.\n");
	return 0;
}
