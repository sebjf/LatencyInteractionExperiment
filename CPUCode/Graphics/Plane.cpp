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
	m_burst_offset = 0;
}

Plane::~Plane()
{

}

void Plane::SetPlaneContentInteractive()
{
//	SDL_FillRect(m_surface, NULL, SDL_MapRGBA(m_surface->format,0,0,0,255));

	int w;
	int h;
	int x;
	int y;

	std::cout << "Enter the x: " << std::endl;
	std::cin >> x;
	std::cout << "Enter the y: " << std::endl;
	std::cin >> y;

	std::cout << "Enter the width: " << std::endl;
	std::cin >> w;
	std::cout << "Enter the height: " << std::endl;
	std::cin >> h;

	SDL_Rect dest1;

	dest1.x = x;
	dest1.y = y;
	dest1.w = w;
	dest1.h = h;

	//SDL_Surface* img = IMG_Load("/home/sfriston/Experiments/background.bmp");

	SDL_FillRect(m_surface, &dest1, SDL_MapRGBA(m_surface->format,100,100,127,255));

	//SDL_BlitSurface(img, NULL, m_surface, &dest1);
	UpdatePlaneContent();

}

void Plane::SetPlaneContent(SDL_Surface* img)
{
	SDL_Rect dest;
	dest.x = m_offsetx;
	dest.y = m_offsety;
	dest.w = img->w;
	dest.h = img->h;

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

	const int pixels_per_burst = m_burst_size / 4;
	const int bursts_per_command = 10;
	const int pixels_per_command = pixels_per_burst * bursts_per_command;

	const int clip = 1240 * 2;

	//mem command generator generates cmnds on each boundary of pixels_per_command, so ensure the counter max is
	//NOT a multiple of this or else at the end of the frame new words will constantly be generated
	int number_of_pixels_to_read = (m_width * m_height) - clip;
	if((number_of_pixels_to_read % pixels_per_command) == 0){
		number_of_pixels_to_read++;
	}

	const int length_in_pixels = number_of_pixels_to_read;
	const int length_in_bytes = length_in_pixels * 4;
	const int length_in_bursts = length_in_bytes / m_burst_size;
	const int length_in_bytes_clipped = length_in_bursts * m_burst_size;

	max_set_uint64t(mem_actions, "mcp_kernel", "FrameSizePixels", length_in_pixels);

	max_lmem_linear(mem_actions, "plane_0_write", 0, length_in_bytes_clipped);
	max_queue_input(mem_actions,"cpu_to_plane_0", m_surface->pixels, length_in_bytes_clipped);

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
