/*
 * Plane.cpp
 *
 *  Created on: 20 May 2014
 *      Author: sfriston
 */

#include "Plane.h"

#include <SDL/SDL.h>
#include <iostream>

Plane::Plane(std::string name, max_engine_t* engine, max_file_t* maxfile, max_actions_t* initial_actions)
:m_name(name),
 m_engine(engine),
 m_maxfile(maxfile)
{
	m_width = (int)max_get_constant_uint64t(maxfile, "DisplayTotalWidth");
	m_height = (int)max_get_constant_uint64t(maxfile, "DisplayTotalHeight");

	m_surface = SDL_CreateRGBSurface(0, m_width, m_height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

	int burst_size = max_get_burst_size(maxfile, NULL);

	int length = m_width * m_height * 4;

	float r = length % burst_size;
	if(r != 0){
		std::cout << "Problem with plane" << std::endl;
	}

	max_lmem_linear(initial_actions, "read_plane_0", 0, length);
}

Plane::~Plane()
{

}

void Plane::UpdatePlaneContent()
{
	max_actions_t* mem_actions = max_actions_init(m_maxfile, NULL);
	max_disable_reset(mem_actions);
	max_enable_partial_memory(mem_actions);
	max_disable_validation(mem_actions);

	max_lmem_linear(mem_actions, "write_plane_0", 0, m_width * m_height);
	max_queue_input(mem_actions,("cpu_to_" + m_name).c_str(), m_surface->pixels, m_surface->w * m_surface->h * 4);

	max_run_nonblock(m_engine, mem_actions);
	//max_run(engine, mem_actions);
	max_actions_free(mem_actions);
}
