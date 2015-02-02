/*
 * EmbeddedConditions.cpp
 *
 *  Created on: 28 Jan 2015
 *      Author: sfriston
 */

#include <vector>
#include <Steering/SteeringConditionBuilder.h>
#include <Fitts/FittsLawTestConditions.h>


SteeringConditionBuilder* generateSteeringLawTestConditions()
{
	SteeringConditionBuilder* conditions = new SteeringConditionBuilder("/home/sfriston/Experiments/");
	conditions->Load("steering_conditions_1.mbin");
	return conditions;
}

FittsLawTestCondition* generateFittsLawTestCondition(int id, int x, int width, int latency)
{
	FittsLawTestCondition* condition = new FittsLawTestCondition();

	condition->m_filename 				= "Generated Condition";
	condition->m_condition_id 			= id;
	condition->staging_area.center_x 	= 50;
	condition->staging_area.center_y 	= 100;
	condition->staging_area.width 		= 50;
	condition->staging_area.height 		= 50;
	condition->target.center_x 			= x;
	condition->target.center_y 			= 100;
	condition->target.width 			= width;
	condition->target.height 			= 50;
	condition->latency_in_ms 			= latency;

	return condition;
}

std::vector<FittsLawTestCondition*>* generateFittsLawTestConditions()
{
	std::vector<FittsLawTestCondition*>* conditions = new std::vector<FittsLawTestCondition*>();

	conditions->push_back(generateFittsLawTestCondition(1,100,50,0));
	conditions->push_back(generateFittsLawTestCondition(2,100,5,10));
	conditions->push_back(generateFittsLawTestCondition(3,150,5,50));
	conditions->push_back(generateFittsLawTestCondition(4,200,10,100));
	conditions->push_back(generateFittsLawTestCondition(5,250,10,100));

	return conditions;
}
