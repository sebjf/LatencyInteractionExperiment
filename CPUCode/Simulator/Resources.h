/*
 * Resources.h
 *
 *  Created on: 29 May 2014
 *      Author: sfriston
 */

#ifndef RESOURCES_H_
#define RESOURCES_H_

#include "Delay.h"
#include <Utils/Mouse/mouse.h>
#include <Utils/VirtualMonitor/virtualmonitor.h>
#include <Graphics/Sprite.h>
#include <Graphics/Plane.h>
#include "MaxSLiCInterface.h"

class Resources
{
public:

	Resources(
			Mouse* mouse,
			DelayedInputController* input_controller,
			max_file_t* maxfile,
			max_engine_t* engine,
			max_actions_t* actions,
			Sprite* sprite_0,
			Sprite* sprite_1,
			Sprite* sprite_2,
			Plane* plane_0,
			VirtualMonitor* monitor,
			Stream* metadata,
			bool isSimulation)
	:mouse(*mouse),
	 input_controller(*input_controller),
	 maxfile(*maxfile),
	 engine(*engine),
	 actions(*actions),
	 sprite_0(*sprite_0),
	 sprite_1(*sprite_1),
	 sprite_2(*sprite_2),
	 plane_0(*plane_0),
	 monitor(*monitor),
	 metadata(*metadata),
	 isSimulation(isSimulation)
	{}

	~Resources();

	Mouse& mouse;
	DelayedInputController& input_controller;

	max_file_t& maxfile;
	max_engine_t& engine;
	max_actions_t& actions;

	Sprite& sprite_0;
	Sprite& sprite_1;
	Sprite& sprite_2;
	Plane& plane_0;

	VirtualMonitor& monitor;

	Stream& metadata;

	bool isSimulation;
};

Resources* InitialiseResources();

#endif /* RESOURCES_H_ */
