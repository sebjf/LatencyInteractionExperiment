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
#include <istream>
#include <errno.h>
#include <vector>
#include <Utils/Split.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

std::istream& operator >>(std::istream& is, PathSegment& segment)
{
	is >> segment.x;
	is >> segment.y;
	is >> segment.forward;
	return is;
}

std::istream& operator >>(std::istream& is, Path& path)
{
	is >> path.m_width;

	int num_segments;
	is >> num_segments;
	for(int i = 0; i < num_segments; i++)
	{
		PathSegment s;
		is >> s;
		path.m_points.push_back(s);
	}

	return is;
}

SteeringConditionBuilder::SteeringConditionBuilder(std::string dir)
:m_search_dir(dir)
{

}

void SteeringConditionBuilder::InitialiseCondition(SteeringLawTestCondition* condition, std::istream& stream)
{
	stream >> condition->m_latency_in_ms;
	stream >> condition->path;

	int length;
	stream >> length;

	uint8_t img_data[length];
	stream.read((char*)img_data,length);
	SDL_RWops* img_ops = SDL_RWFromMem(stream,length);

	condition->m_map = IMG_LoadBMP_RW(img_ops);
}

void SteeringConditionBuilder::LoadSingle(std::string filename)
{
	std::ifstream file((m_search_dir + filename).c_str(), std::ifstream::in);
	if(file.fail())
	{
		std::cout << "Could not open file: " << filename << " " << strerror(errno) << std::endl;
	}

	LoadSingle(file);
}

void SteeringConditionBuilder::LoadSingle(std::istream& is)
{
	 SteeringLawTestCondition* condition = new SteeringLawTestCondition();
	 InitialiseCondition(condition, is);
	 m_conditions.push_back(condition);
}

std::vector<SDL_Surface*> SteeringConditionBuilder::GetMaps()
{
	std::vector<SDL_Surface*> surfaces;

	for(unsigned int i = 0; i < m_conditions.size(); i++)
	{
		surfaces.push_back(m_conditions[i]->m_map);
	}

	return surfaces;
}
