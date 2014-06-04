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
	steering_conditions.LoadSingle("steering_conditions.bin");

	Resources* resources;
	Simulator* fitts;
	Simulator* steering;

//the issue is the reference in plane made from sdl_surface pointer. the cast from void* to uint64_t makes it go to zero.
	SDL_Surface* img1 = IMG_Load("/home/sfriston/Experiments/path1.bmp");
	SDL_Surface* img2 = IMG_Load("/home/sfriston/Experiments/background.bmp");

	bool run = true;
	while(run){

		PrintMainMenu();

		switch(std::cin.get()){
		case 'i':
		case 'I':

			resources = InitialiseResources();

			resources->plane_0.SetPlaneContent(steering_conditions.GetMaps());

			resources->plane_0.SetPlaneContent(img1,1);
			resources->plane_0.SetPlaneContent(img2,2);

			resources->plane_0.UpdatePlaneContent();

			fitts = new SimulatorFitts(*resources, logger);
			steering = new SimulatorSteering(*resources, logger, steering_conditions);
			break;

		case 'b':
		case 'B':
			int v;
			std::cout << "Plane No." << std::endl;
			std::cin >> v;
			resources->plane_0.ShowPlane(v);
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
