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
	Logger logger(experiments_root + "Logs/","test_results_collection",".logs");

	SteeringConditionBuilder steering_conditions(experiments_root);

	FittsLawTestConditionLoader loader;
	std::vector<FittsLawTestCondition*> fitts_conditions = loader.LoadCSV("/home/sfriston/Experiments/fittsLawConditions_1.csv");

	Resources* resources;
	SimulatorFitts* 	fitts;
	SimulatorSteering* 	steering;

	bool run = true;
	while(run){

		PrintMainMenu();

		switch(std::cin.get()){
		case 'i':
		case 'I':
			resources = InitialiseResources();

			steering_conditions.Load("steering_conditions_1.mbin");
			resources->plane_0.SetPlaneContent(steering_conditions.GetMaps(), steering_conditions.GetRefs());
			resources->plane_0.UpdatePlaneContent();
			resources->plane_0.ShowPlane(MAP_DEFAULT);

			fitts = new SimulatorFitts(*resources, logger);
			steering = new SimulatorSteering(*resources, logger);
			break;

		case 'r':
		case 'R':

			fitts->SetConditions(fitts_conditions);
			manager.RunSimulation(fitts);
			break;

		case 't':
		case 'T':

			steering->SetConditions(steering_conditions);
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

		case 'p':
		case 'P':
			resources->input_controller.Reset();
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
