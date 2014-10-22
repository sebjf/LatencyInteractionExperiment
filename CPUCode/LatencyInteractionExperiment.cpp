#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "MaxSLiCInterface.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Simulator/Resources.h"

#include <Simulator/SimulatorFitts.h>
#include <Simulator/SimulatorSteering.h>
#include <Simulator/TestSimulator.h>

#include "Steering/SteeringConditionBuilder.h"

#include <signal.h>

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

void sigaction_handler(int signum, siginfo_t* info, void* context)
{
	int pid = info->si_pid;
	std::cout << "Received term from " << pid << std::endl;
}

int main(int argc, char *argv[])
{
	// no problem with card for a while, so turn this off
	struct sigaction action;
	action.sa_handler = NULL;
	action.sa_sigaction = &sigaction_handler;
	action.sa_flags = SA_SIGINFO;
//	sigemptyset(&action.sa_mask);
//	sigaction(SIGTERM, &action, NULL );

	int participant_id = 0;
	if(argc > 1)
	{
		participant_id = atoi(argv[1]);
	}
	std::cout << "Beginning for participant number: " << participant_id << std::endl;

	std::string experiments_root = "/home/sfriston/Experiments/";

	Logger logger(participant_id, experiments_root + "Logs/", "test_results_collection", ".logs");

	SteeringConditionBuilder steering_conditions(experiments_root);

	FittsLawTestConditionLoader loader;
	std::vector<FittsLawTestCondition*>* fitts_conditions = loader.LoadCSV("/home/sfriston/Experiments/fittsLawConditions_1.csv");

	Resources* resources = NULL;
	SimulatorFitts* 	fitts;
	SimulatorSteering* 	steering;

	Simulator* running = NULL;

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

			if(running != NULL)
			{
				running->Stop();
			}
			//running = new TestPhantomSimulator(*resources,logger);
			running = fitts;
			running->Start();

			break;

		case 't':
		case 'T':

			steering->SetConditions(steering_conditions);

			if(running != NULL)
			{
				running->Stop();
			}
			running = steering;
			running->Start();

			break;

		case 's':
		case 'S':
			if(running != NULL)
			{
				running->Stop();
				running = NULL;
			}

			break;

		case 'e':
		case 'E':
			if(running != NULL)
			{
				running->Stop();
				running = NULL;
			}
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

		case 'n':
		case 'N':
			resources->input_controller.Reset();

		case 'M':
		case 'm':
			if(running != NULL)
			{
				running->flag = 1;
			}

		case '\n':
		case '\r':
			break;

		default:
			std::cout << "Unknown command. Remember press E to exit." << std::endl;
			break;
		}
	};

	if(resources){
		delete resources;
	}

	std::cout << "Done." << std::endl;

	return 0;
}
