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
	int m_ref;

	int m_latency_in_ms;
	Path path;

	//These are for reference only and are not used in calculations of stimuli
	int m_curvature;

	SDL_Surface* m_map;

};

#endif /* STEERINGLAWTESTCONDITIONS_H_ */
