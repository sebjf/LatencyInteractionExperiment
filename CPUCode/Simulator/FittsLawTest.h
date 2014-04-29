/*
 * FittsLawTest.h
 *
 *  Created on: 28 Apr 2014
 *      Author: sfriston
 */

#ifndef FITTSLAWTEST_H_
#define FITTSLAWTEST_H_

#include "SDL/SDL.h"
#include "Sprite.h"


enum FittsStage {
	InitialiseStage,
	BeginWaitForStartStage,
	WaitForStartStage,
	BeginMoveToTargetStage,
	MoveToTargetStage,
	CompleteStage };

class Rectangle
{
public:
	int center_x;
	int center_y;
	int width;
	int height;

	bool isCursorInRect(int x, int y)
	{
		return ((abs(center_x - x) <= width)
				&&
				(abs(center_y - y) <= height));
	}
};

class FittsLawTestCondition
{
public:
	Rectangle staging_area;
	Rectangle target;
	int latency_in_ms;

	FittsLawTestCondition()
	{
		staging_area.center_x = 100;
		staging_area.center_y = 100;
		staging_area.width = 50;
		staging_area.height = 50;
		target.center_x = 500;
		target.center_y = 100;
		target.width = 25;
		target.height = 25;
		latency_in_ms = 0;
	}
};

class FittsLawTestRunner
{
public:
	FittsLawTestRunner(Sprite* staging_sprite, Sprite* target_sprite);

	Sprite* staging_area;
	Sprite* target;

	/*Begins a new test with the specified conditions*/
	void Begin(FittsLawTestCondition* condition);

	/* Update is called repeatedly until the test is complete. it is responsible for checking conditions and
	 * advancing the test based on the user input passed to it. */
	bool Update(int x, int y, bool lmb);

	FittsStage stage;
	FittsLawTestCondition* condition;

private:

	SDL_Surface* staging_area_texture;
	SDL_Surface* target_texture;

	/*These are the implementations for each stage - returning true will advance the test to the next stage*/
	bool Initialise();
	bool BeginWaitForStart();
	bool WaitForStart(int x, int y, bool lmb);
	bool BeginMoveToTarget();
	bool MoveToTarget(int x, int y, bool lmb);
	void Complete();

	/*Utility functions*/
	void LoadImages();

};

#endif /* FITTSLAWTEST_H_ */
