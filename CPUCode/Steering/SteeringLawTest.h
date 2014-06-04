/*
 * SteeringLawTest.h
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#ifndef STEERINGLAWTEST_H_
#define STEERINGLAWTEST_H_

#include <Graphics/Plane.h>
#include <Graphics/Sprite.h>
#include "SteeringLawTestConditions.h"
#include "PathFollower.h"

enum SteeringStage
{
	InitialiseStage,
	TraceStage,
	CompleteStage
};


class SteeringLawTestRunner
{
public:
	SteeringLawTestRunner(Plane& background, Sprite& ball);

	bool Update(int x, int y);
	float GetDelay();
	void Begin(SteeringLawTestCondition* condition);

private:
	Plane& m_background;
	Sprite& m_ball;

	SteeringStage m_stage;

	SteeringLawTestCondition* m_condition;

	PathFollower* m_tracer;

	void Initialise();
	bool Trace(int x, int y);

	int m_latency;

};

#endif /* STEERINGLAWTEST_H_ */
