/*
 * SteeringLawTestConditions.h
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#ifndef STEERINGLAWTESTCONDITIONS_H_
#define STEERINGLAWTESTCONDITIONS_H_

#include <vector>
#include "Path.h"


class SteeringLawTestCondition
{
public:
	std::string m_filename;
	int m_condition_id;

	int m_latency_in_ms;
	Path path;

	//These are for reference only and are not used in calculations of stimuli
	int m_curvature;

	SDL_Surface* m_map;
	SDL_Surface* m_ball;

};

#endif /* STEERINGLAWTESTCONDITIONS_H_ */
