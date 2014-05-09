/*
 * Sprite.h
 *
 *  Created on: 25 Apr 2014
 *      Author: sfriston
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "SDL/SDL.h"
#include "MaxSLiCInterface.h"
#include "MaxVideoCpuResources.h"
#include <string>


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
	Sprite(std::string name, max_engine_t* engine, max_file_t* maxfile, int width, int height);

	SDL_Surface* surface;
	spriteproperties properties;

	/*scales the source surface and writes it into the sprite at the location specified*/
	void SetSpriteSurface(SDL_Surface* source, int width, int height);
	void SetSpriteSurface(SDL_Surface* source, int x, int y, int width, int height);

	void SetSpriteColour(char a, char r, char g, char b);

	void SetSpriteCenterLocation(int x, int y);

	void UpdateSpriteContent();

	void UpdateSpriteProperties();

private:
	std::string m_name;

	Stream* properties_stream;

	max_engine_t* engine;
	max_file_t* maxfile;

	size_t SLOT_SIZE;
	size_t NUM_SLOTS;
	void* write_buffer;
	max_llstream_t* write_llstream;

	void CreateContentStream();
	void UpdateSpriteContentStream();
	void UpdateSpriteContentStream2();
};

#endif /* SPRITE_H_ */
