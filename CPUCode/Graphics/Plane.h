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
#include <vector>
#include <map>

/* A plane is a special type of sprite that does not move, and instead takes up the whole screen, stored in LMEM */

class Plane
{
public:
	Plane(std::string name, max_engine_t* engine, max_file_t* maxfile);
	~Plane();

	void SetPlaneContent(std::vector<SDL_Surface*> surfaces, std::vector<int> refs);
	void SetPlaneContent(SDL_Surface* image, int ref);
	void SetPlaneContent(std::string& image);
	void SetPlaneContent(SDL_Surface* image);
	void UpdatePlaneContent();

	void ShowPlane(int ref);

private:
	std::string m_name;

	max_engine_t* m_engine;
	max_file_t* m_maxfile;
	SDL_Surface* m_surface;

	int m_width;
	int m_height;

	int m_pixelsperburst;
	int m_burst_size;

	int m_map_width; //the number of pixels that will actually be read per line (will likely be larger than m_width)
	int m_map_size;

	SDL_Surface* AddSurface(int ref);
	std::vector<SDL_Surface*> m_surfaces;
	std::map<int,int> m_surfacemap;

	bool m_is_simulation;

};

#endif /* PLANE_H_ */
