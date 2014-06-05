#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

#include "Simulator/SimulatorWrapper.h"
#include "Simulator/Simulators.h"
#include "Simulator/Resources.h"

#include "Steering/SteeringConditionBuilder.h"

#include <SDL/SDL_image.h>

void PrintMainMenu()
{
	std::cout <<
	"Latency Interaction Experiment.\n"\
	"	I: Initialise resources for experiments.\n"\
	"	R: Run Simulation\n"\
	"	E: Exit.\n"\
	"	S: Stop Simulation\n"\
	"	C: Convert all available logs to Matlab\n";
}

int main(int argc, char *argv[])
{
	std::string experiments_root = "/home/sfriston/Experiments/";

	SimulatorManager manager;
	Logger logger(experiments_root,"fitts_law_log_collection_",".fitts");

	SteeringConditionBuilder steering_conditions(experiments_root);

	Resources* resources;
	Simulator* fitts;
	Simulator* steering;

	bool run = true;
	while(run){

		PrintMainMenu();

		switch(std::cin.get()){
		case 'i':
		case 'I':
			steering_conditions.LoadSingle("steering_conditions.bin");

			resources = InitialiseResources();

			resources->plane_0.SetPlaneContent(steering_conditions.GetMaps(), steering_conditions.GetRefs());
			resources->plane_0.UpdatePlaneContent();

			fitts = new SimulatorFitts(*resources, logger);
			steering = new SimulatorSteering(*resources, logger, steering_conditions);
			break;

		case 'r':
		case 'R':

			manager.RunSimulation(fitts);
			break;

		case 't':
		case 'T':

			manager.RunSimulation(steering);
			break;

		case 's':
		case 'S':

			manager.StopSimulation();
			break;

		case 'e':
		case 'E':

			manager.StopSimulation();
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
