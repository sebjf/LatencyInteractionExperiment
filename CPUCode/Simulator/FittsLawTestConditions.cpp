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

std::vector<FittsLawTestCondition*> FittsLawTestConditionLoader::LoadHardcoded()
{
	return std::vector<FittsLawTestCondition*>();
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

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

		 if(items.size() < 8){
			 continue; //incomplete line. skip.
		 }

		 condition->staging_area.center_x 	= atoi(items[0].c_str());
		 condition->staging_area.center_y 	= atoi(items[1].c_str());
		 condition->staging_area.width 		= atoi(items[2].c_str());
		 condition->staging_area.height 	= atoi(items[3].c_str());
		 condition->target.center_x 		= atoi(items[4].c_str());
		 condition->target.center_y 		= atoi(items[5].c_str());
		 condition->target.width 			= atoi(items[6].c_str());
		 condition->target.height 			= atoi(items[7].c_str());
		 condition->latency_in_ms = 0;

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
