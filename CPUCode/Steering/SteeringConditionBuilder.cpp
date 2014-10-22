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
#include <boost/filesystem/path.hpp>
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

	if(num_segments > 600)
	{
		std::cout << "Error in file num path segments" << std::endl;
		return is;
	}

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

SDL_Surface* SteeringConditionBuilder::ReadBitmap(std::istream& stream)
{
	int length;
	stream >> length;

	char img_data[length];
	stream.get(); //remove the new line character from after the length value.
	stream.read(img_data,length);
	SDL_RWops* img_ops = SDL_RWFromMem(img_data,length);

	return IMG_LoadBMP_RW(img_ops);
}

void SteeringConditionBuilder::InitialiseCondition(SteeringLawTestCondition* condition, std::istream& stream)
{
	stream >> condition->m_condition_id;
	stream >> condition->m_latency_in_ms;
	stream >> condition->path;

	condition->m_map = ReadBitmap(stream);
	condition->m_ball = ReadBitmap(stream);
}

void SteeringConditionBuilder::Load(std::string filename)
{
	std::ifstream file((m_search_dir + filename).c_str(), std::ifstream::in);
	if(file.fail())
	{
		std::cout << "Could not open file: " << filename << " " << strerror(errno) << std::endl;
	}

	int count = 1;

	if(filename.find(".mbin") != std::string::npos){
		file >> count;
	}

	for(int i = 0; i < count; i++){
		SteeringLawTestCondition* condition = LoadSingle(file);
		condition->m_filename = boost::filesystem::path(filename).leaf();
		m_conditions.push_back(condition);
	}
}

SteeringLawTestCondition* SteeringConditionBuilder::LoadSingle(std::istream& is)
{
	 SteeringLawTestCondition* condition = new SteeringLawTestCondition();
	 InitialiseCondition(condition, is);
	 return condition;
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

std::vector<int> SteeringConditionBuilder::GetRefs()
{
	std::vector<int> refs;

	for(unsigned int i = 0; i < m_conditions.size(); i++)
	{
		refs.push_back(m_conditions[i]->m_condition_id);
	}

	return refs;

}
