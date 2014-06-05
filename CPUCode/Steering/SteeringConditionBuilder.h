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

	std::vector<SteeringLawTestCondition*> m_conditions;


	void LoadSingle(std::string filename);
	void LoadSingle(std::istream& is);

	std::vector<SDL_Surface*> GetMaps();
	std::vector<int> GetRefs();

private:

	std::string m_search_dir;


	void InitialiseCondition(SteeringLawTestCondition* condition, std::istream& stream);
	SDL_Surface* ReadBitmap(std::istream& stream);

};

#endif /* STEERINGCONDITIONBUILDER_H_ */
