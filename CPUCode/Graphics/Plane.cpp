/*
 * Plane.cpp
 *
 *  Created on: 20 May 2014
 *      Author: sfriston
 */

#include "Plane.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include "MaxVideoCpuResources.h"
#include <math.h>

Plane::Plane(std::string name, max_engine_t* engine, max_file_t* maxfile)
:m_name(name),
 m_engine(engine),
 m_maxfile(maxfile)
{
	m_width = (int)max_get_constant_uint64t(maxfile, "DisplayWidth");
	m_height = (int)max_get_constant_uint64t(maxfile, "DisplayHeight");
	m_offsetx = (int)max_get_constant_uint64t(maxfile, "DisplayStartX");
	m_offsety = (int)max_get_constant_uint64t(maxfile, "DisplayStartY");

	m_burst_size = max_get_burst_size(maxfile, NULL);

	m_pixelsperburst = m_burst_size/4;

	m_map_width = ceil((float)m_width / (float)m_pixelsperburst) * m_pixelsperburst;

	m_burst_offset = 0;

	m_surface = SDL_CreateRGBSurface(0, m_map_width, m_height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
}

Plane::~Plane()
{

}

void Plane::SetPlaneContent(SDL_Surface* img)
{
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = 0;
	dest.h = 0;

	SDL_BlitSurface(img, NULL, m_surface, &dest);
}

void Plane::SetPlaneContent(std::string filename)
{
	SDL_Surface* img = IMG_Load(filename.c_str());
	SetPlaneContent(img);
	SDL_FreeSurface(img);
}

void Plane::UpdatePlaneContent()
{
	max_actions_t* mem_actions = max_actions_init(m_maxfile, "default");
//	max_disable_reset(mem_actions);
	max_enable_partial_memory(mem_actions);
	max_disable_validation(mem_actions);

	max_set_uint64t(mem_actions, "mcp_kernel", "frame_offset", 0);

	//The surface has been sized so its width is a multiple of the burst size, so we do not have to worry about that here
	const int map_size_bytes = m_surface->w * m_surface->h * 4;

	max_lmem_linear(mem_actions, "plane_0_write", 0, map_size_bytes);
	max_queue_input(mem_actions,"cpu_to_plane_0", m_surface->pixels, map_size_bytes);

	if(max_get_constant_uint64t(m_maxfile,"IS_SIMULATION"))
	{
		max_run_nonblock(m_engine, mem_actions);
	}
	else
	{
		max_run(m_engine, mem_actions);
	}
	max_actions_free(mem_actions);

	std::cout << "Wrote LMem." << std::endl;
}
