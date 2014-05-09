/*
 * Sprite.cpp
 *
 *  Created on: 25 Apr 2014
 *      Author: sfriston
 */
 
 //http://www.sdltutorials.com/sdl-scale-surface

#include "Sprite.h"

#include "SDL/SDL_rotozoom.h"
#include <errno.h>

Sprite::Sprite(std::string name, max_engine_t* engine, max_file_t* maxfile, int width, int height)
	:m_name(name),
	 engine(engine),
	 maxfile(maxfile)
{
	surface = SDL_CreateRGBSurface(0, width, height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	properties_stream = new Stream(engine, (name + "_positions").c_str(), sizeof(spriteproperties));

	properties.x = 0;
	properties.y = 0;
	properties.r = 255;
	properties.g = 255;
	properties.b = 255;
	properties.a = 255;

	//CreateContentStream();
}

void Sprite::CreateContentStream()
{
	SLOT_SIZE = 16; //32 bit rgba colour
	NUM_SLOTS = std::min(512, surface->w * surface->h);

	write_buffer = NULL;
	if(posix_memalign(&write_buffer, 4096, SLOT_SIZE * NUM_SLOTS) == ENOMEM){
		printf("Could not allocate memory.");
	}
	memset(write_buffer,0,SLOT_SIZE*NUM_SLOTS);
	write_llstream = 0;
	write_llstream = max_llstream_setup(engine, (m_name + "_content").c_str(), NUM_SLOTS, SLOT_SIZE, write_buffer);
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
	UpdateSpriteContentStream2();
}

void Sprite::UpdateSpriteContentStream2()
{
	max_actions_t* mem_actions = max_actions_init(maxfile, NULL);
	max_disable_reset(mem_actions);
	max_enable_partial_memory(mem_actions);
	max_disable_validation(mem_actions);

	/* This runs more than quickly enough - remember to make sure llstreams are not set up or else neither will work! */

	max_queue_input(mem_actions,(m_name + "_content").c_str(), surface->pixels, surface->w * surface->h * 4);

	max_run_nonblock(engine, mem_actions);
	max_actions_free(mem_actions);
}

void Sprite::UpdateSpriteContentStream()
{
	int numMemElements = surface->w * surface->h;

	void* write_ptr;

	int offset = 0;
	int slots = 0;

	/* In simulation this can lock up, as the output stream stalls (because VirtualMonitor does not read it as it
	 * runs in the same thread as this method), meaning the input streams are never 'read' and the acquired slots
	 * always remain zero. */

	do{
		slots = max_llstream_write_acquire(write_llstream, NUM_SLOTS, &write_ptr);
		if(slots > 0){
			memcpy(write_ptr, &(((uint32_t*)surface->pixels)[offset]), SLOT_SIZE * slots); //this is wrong anyway, there are 4 bytes in a pixel not 16
			max_llstream_write(write_llstream, slots);
		}
		offset+=slots;
	}while(offset < numMemElements);

}

void Sprite::UpdateSpriteProperties()
{
	properties_stream->Write(&properties);
}

