/*
 * Cursor.h
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#ifndef CURSOR_H_
#define CURSOR_H_

#include "Sprite.h"

class Cursor
{
private:
	Sprite& m_sprite;

public:
	Cursor(Sprite& sprite);
	void Update(int x, int y);
};

#endif /* CURSOR_H_ */
