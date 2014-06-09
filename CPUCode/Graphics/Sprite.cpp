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
}

void Sprite::SetSpriteSurface(SDL_Surface* source)
{
	SetSpriteSurface(source, source->w, source->h);
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
	centre.x = x;
	centre.y = y;
	int offset_x = surface->w/2;
	int offset_y = surface->h/2;
	properties.x = x - offset_x;
	properties.y = y - offset_y;
}

Point Sprite::GetSpriteCenterLocation()
{
	return centre;
}

void Sprite::UpdateSpriteContent()
{
	UpdateSpriteContentStream();
}

void Sprite::UpdateSpriteContentStream()
{
	max_actions_t* mem_actions = max_actions_init(maxfile, NULL);
	max_disable_reset(mem_actions);
	max_enable_partial_memory(mem_actions);
	max_disable_validation(mem_actions);

	/* This runs more than quickly enough - remember to make sure llstreams are not set up or else neither will work! */

	max_queue_input(mem_actions,(m_name + "_content").c_str(), surface->pixels, surface->w * surface->h * 4);

	max_run_nonblock(engine, mem_actions);
	//max_run(engine, mem_actions);
	max_actions_free(mem_actions);
}

void Sprite::UpdateSpriteProperties()
{
	spriteproperties s = properties; //this corrects for a mistake in the y direction in the kernel which needs a recompile
	s.y = -s.y;
	properties_stream->Write(&s);
}

void Sprite::Hide()
{
	SetSpriteColour(0,0,0,0);
	UpdateSpriteProperties();
}

Sprite::~Sprite()
{
	delete properties_stream;
//	max_wait(max_run); //we cant unload the engine until all non-blocking operations have completed.
	SDL_FreeSurface(surface);
}
