/*
 * Cursor.cpp
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#include "Cursor.h"
#include <SDL/SDL.h>



Cursor::Cursor(Sprite& sprite, bool doLatency, int size)
	:m_sprite(sprite)
{

	if(doLatency)
	{
		SDL_Surface* target_texture = SDL_CreateRGBSurface(0,20,20, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
		SDL_FillRect(target_texture, NULL, SDL_MapRGBA(target_texture->format, 255,255,255,255));
		m_sprite.SetSpriteSurface(target_texture,20,20);
	}
	else
	{
		SDL_Surface* target_texture = SDL_CreateRGBSurface(0,size,size, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
		SDL_FillRect(target_texture, NULL, SDL_MapRGBA(target_texture->format, 255,0,0,255));
		m_sprite.SetSpriteSurface(target_texture,size,size);
	}

	m_sprite.UpdateSpriteContent();
}

void Cursor::Update(int x, int y)
{
	m_sprite.SetSpriteCenterLocation(x,y);
	m_sprite.UpdateSpriteProperties();
}
