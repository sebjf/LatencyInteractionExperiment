/*
 * FittsLawTest.cpp
 *
 *  Created on: 28 Apr 2014
 *      Author: sfriston
 */

#include "FittsLawTest.h"

#include "SDL/SDL_image.h"

FittsLawTestRunner::FittsLawTestRunner(Sprite* staging_sprite, Sprite* target_sprite)
{
	this->staging_area = staging_sprite;
	this->target = target_sprite;

	stage = CompleteStage;

	LoadImages();
}

void FittsLawTestRunner::Begin(FittsLawTestCondition* condition)
{
	this->condition = condition;
	stage = InitialiseStage;
}

bool FittsLawTestRunner::Update(int x, int y, bool lmb)
{
	switch(stage)
	{
	case InitialiseStage:
		/* In this stage the sprites are intialised with the correct content and size and the buffers for the
		 * latency emulation are configured */
		if(Initialise()){
			stage = BeginWaitForStartStage;
		}
		break;

	case BeginWaitForStartStage:

		if(BeginWaitForStart()){
			stage = WaitForStartStage;
		}
		break;

	case WaitForStartStage:
		/* In this stage the user is prompted to click on the starting point to begin the timed test. The staging
		 * area is green and the next target is visible. */
		if(WaitForStart(x,y,lmb)){
			stage = BeginMoveToTargetStage;
		}
		break;

	case BeginMoveToTargetStage:
		if(BeginMoveToTarget()){
			stage = MoveToTargetStage;
		}
		break;

	case MoveToTargetStage:
		/* In this stage the user is to move to the target. The staging area disappears and the target becomes
		 * green drawing the user to it */
		if(MoveToTarget(x,y,lmb)){
			stage = CompleteStage;
		}

		break;
	case CompleteStage:
		/* The user has clicked on the target and the test is now complete */

		Complete();

		return true;
	}

	return false;
}

bool FittsLawTestRunner::Initialise()
{
	//Reset the sprite properties in accordance with the conditions

	staging_area->SetSpriteColour(255,255,255,255);
	target->SetSpriteColour(255,255,255,255);

	//Reset the sprite content, scaling and off-setting to match the intended appearance

	staging_area->SetSpriteCenterLocation(condition->staging_area.center_x, condition->staging_area.center_y);
	target->SetSpriteCenterLocation(condition->target.center_x, condition->target.center_y);

	staging_area->UpdateSpriteProperties();
	target->UpdateSpriteProperties();

	staging_area->SetSpriteSurface(staging_area_texture, condition->staging_area.width, condition->staging_area.height);
	target->SetSpriteSurface(target_texture, condition->target.width, condition->target.height);

	staging_area->UpdateSpriteContent();
	target->UpdateSpriteContent();

	return true;
}

bool FittsLawTestRunner::BeginWaitForStart()
{
	staging_area->SetSpriteColour(255,200,255,200);
	staging_area->UpdateSpriteProperties();

	return true;
}

bool FittsLawTestRunner::WaitForStart(int x, int y, bool lmb)
{
	return (condition->staging_area.isCursorInRect(x,y) && lmb);
}

bool FittsLawTestRunner::BeginMoveToTarget()
{
	staging_area->SetSpriteColour(255,255,255,255);
	staging_area->UpdateSpriteProperties();
	target->SetSpriteColour(255,200,255,200);
	target->UpdateSpriteProperties();

	return true;
}

bool FittsLawTestRunner::MoveToTarget(int x, int y, bool lmb)
{
	return (condition->target.isCursorInRect(x,y) && lmb);
}

void FittsLawTestRunner::Complete()
{
	staging_area->SetSpriteColour(0,255,255,255);
	target->SetSpriteColour(0,255,255,255);
	staging_area->UpdateSpriteProperties();
	target->UpdateSpriteProperties();
}

double FittsLawTestRunner::GetDelay()
{
	double d = 0;
	if(condition != NULL)
	{
		d = condition->latency_in_ms;
	}
	return d;
}

void FittsLawTestRunner::LoadImages()
{
	/* these will load images eventually to create a more appealing interface for the user but for now we will test
	 * with colour blocks */

	target_texture = SDL_CreateRGBSurface(0,50,50, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	SDL_FillRect(target_texture, NULL, SDL_MapRGBA(target_texture->format, 255,255,255,255));

	staging_area_texture = SDL_CreateRGBSurface(0,50,50, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
	SDL_FillRect(staging_area_texture, NULL, SDL_MapRGBA(target_texture->format, 255,255,255,255));
}
