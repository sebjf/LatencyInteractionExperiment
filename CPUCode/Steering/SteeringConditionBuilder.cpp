/*
 * SteeringConditionBuilder.cpp
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#include "SteeringConditionBuilder.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <errno.h>
#include <Utils/Split.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

SteeringConditionBuilder::SteeringConditionBuilder(std::string dir)
:m_map_search_dir(dir)
{

}

void SteeringConditionBuilder::LoadFromCSV(std::string filename)
{
	std::ifstream file(filename.c_str(), std::ifstream::in);
	if(file.fail())
	{
		std::cout << "Could not open file: " << filename << " " << strerror(errno) << std::endl;
	}

	std::string value;
	while(file.good())
	{
		 getline (file, value);

		 std::vector<std::string> items;
		 split(value,',',items);

		 SteeringLawTestCondition* condition = new SteeringLawTestCondition();

		 if(items.size() < 4){
			 continue; //incomplete line. skip.
		 }

		 LoadPath(items[0].c_str(), condition);
		 condition->path.m_width 	= atoi(items[1].c_str());
		 condition->m_curvature 	= atoi(items[2].c_str());
		 condition->m_latency_in_ms = atoi(items[3].c_str());

		 m_conditions.push_back(condition);
	}

	if(m_conditions.size() <= 0){
		std::cout << "No conditions were loaded from the CSV, there may be a problem with it." << std::endl;
	}
}

void SteeringConditionBuilder::LoadPath(std::string filename, SteeringLawTestCondition* condition )
{
	SDL_Surface* path_map = IMG_Load((m_map_search_dir + filename).c_str());
	condition->m_map = path_map;

	Uint32 mask = SDL_MapRGBA(path_map->format,255,0,0,255);

	for(int x = 0; x < path_map->w; x++)
	{
		for(int y = 0; y < path_map->h; y++)
		{
			Uint32 pixel = ((Uint32*)path_map->pixels)[y * path_map->pitch + x];
			if(pixel == mask)
			{
				PathSegment s;
				s.x = x;
				s.y = y;
				s.forward = 0;

				condition->path.m_points.push_back(s);

				break;
			}
		}

	}

}
