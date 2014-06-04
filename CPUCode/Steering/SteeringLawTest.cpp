/*
 * SteeringLawTest.cpp
 *
 *  Created on: 27 May 2014
 *      Author: sfriston
 */

#include "SteeringLawTest.h"
#include <math.h>
#include <boost/numeric/ublas/vector.hpp>


SteeringLawTestRunner::SteeringLawTestRunner(Plane& background, Sprite& ball)
:m_background(background),
m_ball(ball),
m_latency(0)
{
	m_stage = CompleteStage;
}

void SteeringLawTestRunner::Begin(SteeringLawTestCondition* condition)
{
	m_condition = condition;
	m_stage = InitialiseStage;
}

bool SteeringLawTestRunner::Update(int x, int y)
{
	switch(m_stage)
	{
	case InitialiseStage:
		Initialise();
		m_stage = TraceStage;
		break;

	case TraceStage:
		if(Trace(x,y))
		{
			m_stage = CompleteStage;
		}
		break;

	case CompleteStage:
		return true;
	}

	return false;
}

void SteeringLawTestRunner::Initialise()
{
	m_tracer = new PathFollower(m_condition->path);
	m_background.ShowPlane((uint64_t)m_condition->m_map);
	m_latency = m_condition->m_latency_in_ms;

	//load up images for background, and ball
}

float SteeringLawTestRunner::GetDelay()
{
	return m_latency;
}

bool SteeringLawTestRunner::Trace(int x, int y)
{
	m_tracer->Update(x,y);

	Vector2 ball_location = m_tracer->GetBallLocation();
	m_ball.SetSpriteCenterLocation((int)ball_location(0),(int)ball_location(1));

	return m_tracer->IsComplete();
}
