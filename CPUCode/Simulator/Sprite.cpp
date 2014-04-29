/*
 * Sprite.cpp
 *
 *  Created on: 25 Apr 2014
 *      Author: sfriston
 */
 
 //http://www.sdltutorials.com/sdl-scale-surface

#include "Sprite.h"

#include "SDL/SDL_rotozoom.h"


Sprite::Sprite(std::string name, max_engine_t* engine, max_file_t* maxfile, int width, int height)
{
	this->name = name;
	this->engine = engine;
	this->maxfile = maxfile;
	surface = SDL_CreateRGBSurface(0, width, height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	properties_stream = new Stream(engine, (name + "_positions").c_str(), sizeof(spriteproperties));
	properties.x = 0;
	properties.y = 0;
	properties.r = 255;
	properties.g = 255;
	properties.b = 255;
	properties.a = 255;
}

void Sprite::SetSpriteSurface(SDL_Surface* source, int width, int height)
{
	int x = (surface->w / 2) - (width / 2);
	int y = (surface->h / 2) - (height / 2);
	SetSpriteSurface(source,x,y,width,height);
}

void Sprite::SetSpriteSurface(SDL_Surface* source, int x, int y, int width, int height)
{
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format,0,0,0,0));

	SDL_Rect dstrect = {
		x, y,
		width, height
	};

	SDL_FillRect(surface, &dstrect, SDL_MapRGBA(surface->format,255,255,255,255));

	double zoomx = width / source->w;
	double zoomy = height / source->h;

	source = rotozoomSurfaceXY(source, 0, zoomx, zoomy, 1 );

	SDL_BlitSurface(source,NULL,surface, &dstrect);
}

void Sprite::SetSpriteColour(char a, char r, char g, char b)
{
	properties.a = a;
	properties.r = r;
	properties.g = g;
	properties.b = b;
}

void Sprite::SetSpriteCenterLocation(int x, int y)
{
	int offset_x = surface->w/2;
	int offset_y = surface->h/2;
	properties.x = x - offset_x;
	properties.y = y - offset_y;
}

void Sprite::UpdateSpriteContent()
{
	UpdateSpriteContent(NULL);
}

void Sprite::UpdateSpriteContent(max_actions_t* actions)
{
	int numMemElements = surface->w * surface->h;
	memData = (new FMemWord[numMemElements]);
	for(int i = 0; i < numMemElements; i++){
		memData[i].pixel = ((uint32_t*)surface->pixels)[i];
	}

	if(actions != NULL)
	{
		max_set_mem_range_uint64t(actions, "LatencyInteractionExperimentKernel", name.c_str(), 0, numMemElements, (uint64_t*)memData);
	}
	else
	{
		max_actions_t* mem_actions = max_actions_init(maxfile, NULL);
		max_disable_reset(mem_actions);
		max_enable_partial_memory(mem_actions);
		max_disable_validation(mem_actions);

		max_set_mem_range_uint64t(mem_actions, "LatencyInteractionExperimentKernel", name.c_str(), 0, numMemElements, (uint64_t*)memData);

		max_run(engine,mem_actions);
		max_actions_free(mem_actions);
	}
}

void Sprite::UpdateSpriteProperties()
{
	properties_stream->Write(&properties);
}

