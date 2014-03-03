#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

#include <MaxVideoCpuResources.h>

#include <stdio.h>

int main(int argc, char *argv[])
{

	if(isSim(argc,argv)){
		printf("Running Simulation.");
	}

	makeRealtime();

	Mouse* mouse = new Mouse();

	VirtualMonitor monitor = CreateVirtualMonitor(1688,1066);

	/* Configure the card and start the kernel running */
	max_file_t* maxfile = LatencyInteractionExperiment_init();
	max_engine_t* engine = max_load(maxfile, "local:*");
	max_actions_t* actions = max_actions_init(maxfile, "default");

	ConnectVirtualMonitor(monitor,engine);

	while(1){
		RefreshVirtualMonitor(monitor,1066);
	}

	printf("Done.\n");
	return 0;
}
