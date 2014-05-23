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

void PrintMainMenu()
{
	std::cout <<
	"Latency Interaction Experiment.\n"\
	"	R: Run Simulation\n"\
	"	E: Exit.\n"\
	"	S: Stop Simulation\n"\
	"	C: Convert all available logs to Matlab\n";
}

int main(int argc, char *argv[])
{
	SimulatorWrapper* simManager = new SimulatorWrapper();

	Logger logger("/home/sfriston/Experiments/","fitts_law_log_collection_",".fitts");
	Simulator* sim = new SimulatorFitts(logger);

	bool run = true;
	while(run){

		PrintMainMenu();

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

			simManager->StopSimulation();
			run = false;
			break;

		case 'q':	//this will kill any stuck simulator threads by exiting the program.
		case 'Q':
			run = false;
			break;

		case 'c':	//convert all available logs to matlab
		case 'C':
			logger.SaveFormatMatlab();
			break;

		case '\n':
		case '\r':
			break;

		default:
			std::cout << "Unknown command. Remember press E to exit." << std::endl;
			break;
		}
	};

	std::cout << "Done." << std::endl;

	return 0;
}
