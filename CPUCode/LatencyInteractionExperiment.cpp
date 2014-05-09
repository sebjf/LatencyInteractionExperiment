#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

#include <MaxVideoCpuResources.h>

#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

#include "Keyboard/Keyboard.h"

#include "Simulator/SimulatorWrapper.h"
#include "Simulator/Simulators.h"


int main(int argc, char *argv[])
{
	SimulatorWrapper* simManager = new SimulatorWrapper();

	std::cout <<
	"Latency Interaction Experiment.\n"\
	"	R: Run Simulation\n"\
	"	E: Exit.\n";

	Simulator* sim = new SimulatorFitts();

	bool run = true;
	while(run){

		switch(std::cin.get()){
		case 'r':
		case 'R':

			simManager->RunSimulation(sim);
			break;

		case 's':
		case 'S':

			simManager->StopSimulation();
			break;

		case 'e':
		case 'E':

			run = false;
			break;

		case 't':
		case 'T':
			std::cout << "Test" << std::endl;
			break;

		default:
			std::cout << "Unknown command. Remember press E to exit." << std::endl;
			break;
		}
	};

	std::cout << "Done." << std::endl;

	return 0;
}
