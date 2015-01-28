#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <vector>

#include "MaxSLiCInterface.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Simulator/Resources.h"

#include <Simulator/SimulatorFitts.h>
#include <Simulator/SimulatorSteering.h>
#include "Steering/SteeringConditionBuilder.h"
#include "Fitts/FittsLawTestConditions.h"

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

int main(int argc, char *argv[])
{
	int starting_test = 0;
	int participant_id = 0;
	if(argc > 1)
	{
		participant_id = atoi(argv[1]);
	}
	if(argc > 2)
	{
		starting_test = atoi(argv[2]);
	}

	std::cout << "Beginning for participant number: " << participant_id << std::endl;

	std::string experiments_root = "/home/sfriston/Experiments/";

	SteeringConditionBuilder steering_conditions(experiments_root);
	FittsLawTestConditionLoader loader;
	std::vector<FittsLawTestCondition*>* fitts_conditions = loader.LoadCSV(experiments_root + "/fittsLawConditions_1.csv");

	Resources* resources = NULL;
	SimulatorFitts* 	fitts;
	SimulatorSteering* 	steering;

	Simulator* running = NULL;

	bool shoulddolatencymeasurement = true;

	bool run = true;
	while(run){

		PrintMainMenu();

		switch(std::cin.get()){

		case 'i':
		case 'I':

			steering_conditions.Load("steering_conditions_1.mbin");

			resources = InitialiseResources(steering_conditions);

			fitts = new SimulatorFitts(*resources);
			steering = new SimulatorSteering(*resources);
			break;

		case 'r':
		case 'R':

			fitts->SetConditions(fitts_conditions);

			if(running != NULL)
			{
				running->Stop();
			}

			running = fitts;
			running->current_test = starting_test;
			running->dolatency = shoulddolatencymeasurement;
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
			running->current_test = starting_test;
			running->dolatency = shoulddolatencymeasurement;
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

		case 'n':
		case 'N':
			resources->input_controller.Reset();
			break;

		case 'M':
		case 'm':
			shoulddolatencymeasurement = !shoulddolatencymeasurement;
			break;

		case 'P':
		case 'p':
			if(running != NULL){
				std::cout << "Current test: " << running->current_test << std::endl;
			}
			break;

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
