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

Plane::Plane(std::string name, max_engine_t* engine, max_file_t* maxfile)
:m_name(name),
 m_engine(engine),
 m_maxfile(maxfile)
{
	m_width = (int)max_get_constant_uint64t(maxfile, "DisplayTotalWidth");
	m_height = (int)max_get_constant_uint64t(maxfile, "DisplayTotalHeight");
	m_offsetx = (int)max_get_constant_uint64t(maxfile, "DisplayStartX");
	m_offsety = (int)max_get_constant_uint64t(maxfile, "DisplayStartY");

	m_surface = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

	m_burst_size = max_get_burst_size(maxfile, NULL);

	m_front_porch = 0;
	m_burst_offset = 2;
}

Plane::~Plane()
{

}

void Plane::SetPlaneContent(SDL_Surface* img)
{
	SDL_Rect dest;
	dest.x = m_offsetx;
	dest.y = m_offsety;
	dest.w = img->w;
	dest.h = img->h;

	SDL_FillRect(m_surface, &dest, SDL_MapRGBA(m_surface->format,255,255,255,255));

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

	const int length = (m_width * m_height) + m_front_porch;
	const int length_in_bytes = length * 4;
	const int length_in_bursts = length_in_bytes / m_burst_size;
	const int length_in_bytes_clipped = length_in_bursts * m_burst_size;

	max_set_uint64t(mem_actions, "mcp_kernel", "BurstOffset", m_burst_offset);
	max_set_uint64t(mem_actions, "mcp_kernel", "FrameSizeBursts", length_in_bursts/2);

	uint8_t pData[length_in_bytes];
	memcpy(&pData[m_front_porch * 4], m_surface->pixels, (m_width * m_height) * 4);

	max_lmem_linear(mem_actions, "plane_0_write", 0, length_in_bytes_clipped);
	max_queue_input(mem_actions,("cpu_to_" + m_name).c_str(), pData, length_in_bytes_clipped);

	max_run(m_engine, mem_actions);
	max_actions_free(mem_actions);

	std::cout << "Initialised LMem." << std::endl;
}
