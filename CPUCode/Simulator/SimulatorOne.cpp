
#include "Simulators.h"
#include <MaxVideoCpuResources.h>
#include "Maxfiles.h"
#include "MaxSLiCInterface.h"
#include "../Experiment/experiment.h"
#include <stdio.h>

struct InputUpdate
{
	uint x;
	uint y;
	uint padding;
	uint padding2;
};

struct memword
{
	char r;
	char g;
	char b;
	char a;
	uint32_t padding;
};

struct mempixel
{
	uint32_t pixel;
	uint32_t padding;
};

struct spriteproperties
{
	int x;
	int y;
	char r;
	char g;
	char b;
	char a;
};

class Sprite
{
public:
	Sprite(std::string name, max_engine* engine, int width, int height)
	{
		this->name = name;
		surface = SDL_CreateRGBSurface(0, width, height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
		properties_stream = new Stream(engine, (name + "_positions").c_str(), sizeof(spriteproperties));
	}

	SDL_Surface* surface;

	void WriteToDFE(max_actions_t* actions)
	{
		int numMemElements = surface->w * surface->h;
		memData = (new mempixel[numMemElements]);
		for(int i = 0; i < numMemElements; i++){
			memData[i].pixel = ((uint32_t*)surface->pixels)[i];
		}
		max_set_mem_range_uint64t(actions, "LatencyInteractionExperimentKernel", name.c_str(), 0, numMemElements, (uint64_t*)memData);
	}

	void UpdateLocation(int x, int y)
	{
		spriteproperties t;
		t.x = x;
		t.y = y;
		properties_stream->Write(&t);
	}

private:
	std::string name;
	mempixel* memData;
	Stream* properties_stream;
};

void SimulatorOne::MainLoop()
{
	std::cout << "Beginning main loop Simulator One" << std::endl;

	Mouse* mouse = new Mouse();

	/* Configure the card and start the kernel running */
	max_file_t* maxfile = LatencyInteractionExperiment_init();
	max_engine_t* engine = max_load(maxfile, "local:*");
	max_actions_t* actions = max_actions_init(maxfile, "default");

	bool IsSimulation = max_get_constant_uint64t(maxfile,"IS_SIMULATION");

	if(IsSimulation){
		std::cout << "Running in simulation mode. " << max_get_constant_uint64t(maxfile,"IS_SIMULATION") << std::endl;
	}

	std::cout << "Setting Memory..." << std::endl;

	SDL_Surface* img = SDL_LoadBMP("test1.bmp");
	//SDL_Surface* scaled = SDL_ScaleSurface(img)

	if(img == NULL){
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	Sprite* sprite_0 = new Sprite("sprite_0",engine,256,256);

	SDL_BlitSurface(img,NULL,sprite_0->surface,NULL);
	sprite_0->WriteToDFE(actions);

	VirtualMonitor* monitor = new VirtualMonitor(maxfile);

	if(IsSimulation){
		monitor->Connect(engine);
	}

	Stream* inputStream = new Stream(engine,"positions",sizeof(InputUpdate));

	InputUpdate update;
	update.x = 0;
	update.y = 0;

	max_run(engine, actions);

	mouse->Scale = 0.4f;

	float x = 0;
	float y = 0 ;

	while(DoSimulation){
		MouseDelta m = mouse->readMouse(false);

		x += m.x;
		y += m.y;

		update.x = (int)x;
		update.y = (int)y;

		inputStream->Write(&update);

		sprite_0->UpdateLocation(x,y);

		monitor->Refresh(1066);
	}

}
