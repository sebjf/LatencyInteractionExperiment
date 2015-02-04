/*
 * FittsLawTest.cpp
 *
 *  Created on: 28 Apr 2014
 *      Author: sfriston
 */

#include "FittsLawTest.h"

#include "SDL/SDL_image.h"

FittsLawTestRunner::FittsLawTestRunner(Sprite& staging_sprite, Sprite& target_sprite)
:staging_area(staging_sprite),
 target(target_sprite),
 staging_sprite_set(false),
 current_latency_in_ms(0)
{
	stage = CompleteStage;
	LoadImages();
}

void FittsLawTestRunner::Begin(FittsLawTestCondition* condition)
{
	this->condition = condition;
	stage = InitialiseState;
}

bool FittsLawTestRunner::IsInitialising()
{
	return (stage == InitialiseState);
}

/* At the end of each motion there are two stages that ensure the user moves back to the original staging area.
 * This is because the next condition could introduce artificial latency. It only takes 500ms for a user to adapt
 * to latency, so we do not want them experiencing it while moving to begin the next trial.*/


bool FittsLawTestRunner::Update(int x, int y, bool lmb)
{
	switch(stage)
	{
	case InitialiseState:
		/* In this stage the sprites are intialised with the correct content and size and the buffers for the
		 * latency emulation are configured */
		if(Initialise()){
			stage = BeginMoveToStagingState;
		}
		break;

	case BeginMoveToStagingState:
		if(BeginMoveToStage()){
			stage = MoveToStagingState;

			current_latency_in_ms = 0;
		}
		break;

	case MoveToStagingState:
		/* In this stage the user is prompted to click on the starting point to begin the timed test. The staging
		 * area is green and the next target is visible. */
		if(WaitForStage(x,y,lmb)){
			//stage = BeginMoveToTargetState;
			if(BeginMoveToTarget()){
				stage = MoveToTargetState;
			}

			/*When the user is moving back to the stage to begin the next experiment, we do not want them to adapt
			 *to the new latency, so current_latency_in_ms contains the previous conditions latency, until this point*/
			current_latency_in_ms = condition->latency_in_ms;
		}
		break;

//	case BeginMoveToTargetState:
//		if(BeginMoveToTarget()){
//			stage = MoveToTargetState;
//		}
//		break;

	case MoveToTargetState:
		/* In this stage the user is to move to the target. The staging area disappears and the target becomes
		 * green drawing the user to it */
		if(MoveToTarget(x,y,lmb)){
			stage = CompleteStage;
			Complete();
		}
		break;

	case CompleteStage:
		/* The user has clicked on the target and the test is now complete */

		//Complete();

		return true;
	}

	return false;
}

bool FittsLawTestRunner::Initialise()
{
	//Reset the sprite properties in accordance with the conditions

	staging_area.SetSpriteColour(255,255,255,255);
	staging_area.SetSpriteCenterLocation(condition->staging_area.center_x, condition->staging_area.center_y);
	staging_area.UpdateSpriteProperties();

	if(!staging_sprite_set){
		staging_area.SetSpriteSurface(staging_area_texture, condition->staging_area.width, condition->staging_area.height);
		staging_area.UpdateSpriteContent();
		staging_sprite_set = true;
	}

	target.SetSpriteColour(0,255,255,255);
	target.SetSpriteCenterLocation(condition->target.center_x, condition->target.center_y);
	target.UpdateSpriteProperties();
	target.SetSpriteSurface(target_texture, condition->target.width, condition->target.height);
	target.UpdateSpriteContent();

	return true;
}

bool FittsLawTestRunner::BeginMoveToStage()
{
	staging_area.SetSpriteColour(255,200,255,200);
	staging_area.UpdateSpriteProperties();
	target.SetSpriteColour(0,255,255,255);
	target.UpdateSpriteProperties();

	return true;
}

bool FittsLawTestRunner::WaitForStage(int x, int y, bool lmb)
{
	return (condition->staging_area.isCursorInRect(x,y) && lmb);
}

bool FittsLawTestRunner::BeginMoveToTarget()
{
	staging_area.SetSpriteColour(255,255,255,255);
	staging_area.UpdateSpriteProperties();
	target.SetSpriteColour(255,200,255,200);
	target.UpdateSpriteProperties();

	return true;
}

bool FittsLawTestRunner::MoveToTarget(int x, int y, bool lmb)
{
	return (condition->target.isCursorInRect(x,y) && lmb);
}

void FittsLawTestRunner::Complete()
{
	staging_area.SetSpriteColour(255,255,255,255);
	target.SetSpriteColour(0,255,255,255);
	staging_area.UpdateSpriteProperties();
	target.UpdateSpriteProperties();
}

double FittsLawTestRunner::GetDelay()
{
	return current_latency_in_ms;
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
