/*
 * FittsLawTestConditions.cpp
 *
 *  Created on: 30 Apr 2014
 *      Author: sfriston
 */

#include "FittsLawTestConditions.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <errno.h>
#include <Utils/Split.h>
#include <boost/filesystem/path.hpp>

std::vector<FittsLawTestCondition*> FittsLawTestConditionLoader::LoadCSV(std::string filename)
{
	std::vector<FittsLawTestCondition*> conditions;

	std::ifstream file(filename.c_str(), std::ifstream::in); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/
	if(file.fail())
	{
		std::cout << "Could not open file: " << filename << " " << strerror(errno) << std::endl;
	}
	std::string value;
	while(file.good())
	{
		 getline (file, value); // read a string until next comma: http://www.cplusplus.com/reference/string/getline/

		 std::vector<std::string> items;
		 split(value,',',items);

		 FittsLawTestCondition* condition = new FittsLawTestCondition();

		 if(items.size() < 10){
			 continue; //incomplete line. skip.
		 }

		 condition->m_filename 				= boost::filesystem::path(filename).leaf();
		 condition->m_condition_id 			= atoi(items[0].c_str());
		 condition->staging_area.center_x 	= atoi(items[1].c_str());
		 condition->staging_area.center_y 	= atoi(items[2].c_str());
		 condition->staging_area.width 		= atoi(items[3].c_str());
		 condition->staging_area.height 	= atoi(items[4].c_str());
		 condition->target.center_x 		= atoi(items[5].c_str());
		 condition->target.center_y 		= atoi(items[6].c_str());
		 condition->target.width 			= atoi(items[7].c_str());
		 condition->target.height 			= atoi(items[8].c_str());
		 condition->latency_in_ms 			= atoi(items[9].c_str());

		 if(condition->target.width <= 0 || //if this line is invalid, such as being the first line with headers
			condition->target.height <= 0 ||
			condition->staging_area.width <= 0 ||
			condition->staging_area.height <= 0){
			 continue;
		 }

		 conditions.push_back(condition);
	}

	if(conditions.size() <= 0){
		std::cout << "No conditions were loaded from the CSV, there may be a problem with it." << std::endl;
	}

	return conditions;

}

std::ostream& operator<< (std::ostream& stream, const Rectangle& rect)
{
	stream << rect.center_x << "," << rect.center_y << "," << rect.width << "," << rect.height;
	return stream;
}

std::ostream& operator<< (std::ostream& stream, const FittsLawTestCondition& condition)
{
	stream << condition.staging_area << "," << condition.target << "," << condition.latency_in_ms;
	return stream;
}
