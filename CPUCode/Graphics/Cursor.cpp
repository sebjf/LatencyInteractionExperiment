/*
 * Cursor.cpp
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#include "Cursor.h"
#include <SDL/SDL.h>

Cursor::Cursor(Sprite& sprite)
	:m_sprite(sprite)
{
	SDL_Surface* target_texture = SDL_CreateRGBSurface(0,50,50, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	SDL_FillRect(target_texture, NULL, SDL_MapRGBA(target_texture->format, 255,255,255,255));
	m_sprite.SetSpriteSurface(target_texture,5,5);
	m_sprite.UpdateSpriteContent();
}

void Cursor::Update(int x, int y)
{
	m_sprite.SetSpriteCenterLocation(x,y);
	m_sprite.UpdateSpriteProperties();
}
