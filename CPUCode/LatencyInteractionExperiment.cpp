#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

#include <MaxVideoCpuResources.h>

#include "Experiment/experiment.h"

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

	ExperimentLog* log = new ExperimentLog("Experiment 1", "/home/sfriston/");
	Simulator* sim = new SimulatorOne();
	sim->log = log;

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
			log->Write();
			break;

		case 'e':
		case 'E':

			run = false;
			break;

		case 't':
		case 'T':
			std::cout << "Test\n";
			break;

		default:
			std::cout << "Unknown command. Remember press E to exit.";
			break;
		}
	};

	std::cout << "Done.";

	return 0;
}
