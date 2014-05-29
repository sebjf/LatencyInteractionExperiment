/*
 * Plane.h
 *
 *  Created on: 20 May 2014
 *      Author: sfriston
 */

#ifndef PLANE_H_
#define PLANE_H_

#include <string>
#include <MaxSLiCInterface.h>
#include <SDL/SDL.h>

/* A plane is a special type of sprite that does not move, and instead takes up the whole screen, stored in LMEM */

class Plane
{
public:
	Plane(std::string name, max_engine_t* engine, max_file_t* maxfile);
	~Plane();

	void SetPlaneContent(std::string image);
	void SetPlaneContent(SDL_Surface* image);
	void UpdatePlaneContent();

private:
	std::string m_name;
	max_engine_t* m_engine;
	max_file_t* m_maxfile;

	SDL_Surface* m_surface;

	int m_width;
	int m_height;
	int m_offsetx;
	int m_offsety;

	int m_burst_size;
	int m_burst_offset;
	int m_front_porch;
};

#endif /* PLANE_H_ */
