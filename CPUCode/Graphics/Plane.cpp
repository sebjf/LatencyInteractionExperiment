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
#include <math.h>

Plane::Plane(std::string name, max_engine_t* engine, max_file_t* maxfile)
:m_name(name),
 m_engine(engine),
 m_maxfile(maxfile)
{
	m_width = (int)max_get_constant_uint64t(maxfile, "DisplayWidth");
	m_height = (int)max_get_constant_uint64t(maxfile, "DisplayHeight");

	m_burst_size = max_get_burst_size(maxfile, NULL);

	m_pixelsperburst = m_burst_size/4;

	m_map_width = (int)(ceil((float)m_width / (float)m_pixelsperburst) * (float)m_pixelsperburst);
	m_map_size = m_map_width * m_height * 4;

	m_is_simulation = max_get_constant_uint64t(m_maxfile,"IS_SIMULATION") > 0;

	m_offset_stream = new Stream(engine, "frame_offset_stream", 16);

	makeDefaultPlanes();
}

Plane::~Plane()
{

}

void Plane::makeDefaultPlanes()
{
	SDL_Surface* surf = AddSurface(MAP_BLACK);
	SDL_FillRect(surf, NULL, SDL_MapRGBA(surf->format, 0,0,0,255));
}

SDL_Surface* Plane::AddSurface(int ref)
{
	SDL_Surface* surface = SDL_CreateRGBSurface(0, m_map_width, m_height, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
	int offset = m_surfaces.size() * m_map_size;
	m_surfaces.push_back(surface);
	m_surfacemap[ref] = offset/m_burst_size;
	return surface;
}

void Plane::SetPlaneContent(std::vector<SDL_Surface*> surfaces, std::vector<int> refs)
{
	for(unsigned int i = 0; i < surfaces.size(); i++)
	{
		SDL_Surface* src = surfaces[i];
		SDL_Surface* dest = AddSurface(refs[i]);
		SDL_BlitSurface(src,NULL,dest,NULL);
	}
}

void Plane::SetPlaneContent(SDL_Surface* src, int ref)
{
	SDL_Surface* dest = AddSurface(ref);
	SDL_BlitSurface(src,NULL,dest,NULL);
}

void Plane::SetPlaneContent(SDL_Surface* src)
{
	SetPlaneContent(src, MAP_DEFAULT);
}

void Plane::SetPlaneContent(void* image, unsigned int image_size)
{
	SDL_RWops* image_ops = SDL_RWFromMem(image, image_size);
	SDL_Surface* img_surface = IMG_LoadJPG_RW(image_ops);
	SetPlaneContent(img_surface);
	SDL_FreeSurface(img_surface);
	SDL_FreeRW(image_ops);
}

void Plane::SetPlaneContent(std::string& filename)
{
	SDL_Surface* img = IMG_Load(filename.c_str());
	SetPlaneContent(img);
	SDL_FreeSurface(img);
}

void Plane::ShowPlane(int ref)
{
	current_ref = ref;
	int offset = m_surfacemap[ref];

	//PCIe words are 128 bits minimum, so pad the update out
	uint32_t offset_data[4];
	for(int i = 0; i < 4; i++)
	{
		offset_data[i] = (uint32_t)offset;
	}

	m_offset_stream->Write((void*)offset_data);
}

void Plane::UpdatePlaneContent()
{
	max_actions_t* mem_actions = max_actions_init(m_maxfile, NULL);
	max_enable_partial_memory(mem_actions);
	max_disable_validation(mem_actions);

	max_lmem_linear(mem_actions, "plane_0_write", 0, m_map_size * m_surfaces.size());

	for(unsigned int i = 0; i < m_surfaces.size(); i++)
	{
		max_queue_input(mem_actions,"cpu_to_plane_0", m_surfaces[i]->pixels, m_map_size);
	}

	max_ignore_stream(mem_actions,"displayDataOut");
	max_run(m_engine, mem_actions);

	max_actions_free(mem_actions);

	std::cout << "Wrote LMem." << std::endl;
}
