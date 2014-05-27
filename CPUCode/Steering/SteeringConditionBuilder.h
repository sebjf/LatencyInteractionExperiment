/*
 * SteeringConditionBuilder.h
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#ifndef STEERINGCONDITIONBUILDER_H_
#define STEERINGCONDITIONBUILDER_H_

#include <string>
#include <SDL/SDL.h>
#include "SteeringLawTestConditions.h"

class SteeringConditionBuilder
{
public:
	SteeringConditionBuilder(std::string map_search_dir);

	void LoadFromCSV(std::string filename);

	std::vector<SteeringLawTestCondition*> m_conditions;

private:

	std::string m_map_search_dir;

	void LoadPath(std::string filename, SteeringLawTestCondition* condition);

};

#endif /* STEERINGCONDITIONBUILDER_H_ */
