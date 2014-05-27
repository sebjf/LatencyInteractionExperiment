/*
 * FittsLawTest.h
 *
 *  Created on: 28 Apr 2014
 *      Author: sfriston
 */

#ifndef FITTSLAWTEST_H_
#define FITTSLAWTEST_H_

#include "SDL/SDL.h"
#include <Graphics/Sprite.h>
#include "FittsLawTestConditions.h"


enum FittsStage {
	InitialiseState,
	BeginMoveToStagingState,
	MoveToStagingState,
	BeginMoveToTargetState,
	MoveToTargetState,
	BeginMoveToStagingEndState,
	MoveToStagingEndState,
	CompleteStage };



class FittsLawTestRunner
{
public:
	FittsLawTestRunner(Sprite& staging_sprite, Sprite& target_sprite);

	Sprite& staging_area;
	Sprite& target;

	/*Begins a new test with the specified conditions*/
	void Begin(FittsLawTestCondition* condition);

	/* Update is called repeatedly until the test is complete. it is responsible for checking conditions and
	 * advancing the test based on the user input passed to it. */
	bool Update(int x, int y, bool lmb);

	FittsStage stage;
	FittsLawTestCondition* condition;

	double GetDelay();

private:

	SDL_Surface* staging_area_texture;
	SDL_Surface* target_texture;

	/*These are the implementations for each stage - returning true will advance the test to the next stage*/
	bool Initialise();
	bool BeginMoveToStage();
	bool WaitForStage(int x, int y, bool lmb);
	bool BeginMoveToTarget();
	bool MoveToTarget(int x, int y, bool lmb);
	void Complete();

	bool staging_sprite_set;

	float current_latency_in_ms;

	/*Utility functions*/
	void LoadImages();

};

#endif /* FITTSLAWTEST_H_ */
