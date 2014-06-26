/*
 * PhantomManager.cpp
 *
 *  Created on: 12 Jun 2014
 *      Author: sfriston
 */

#include "PhantomInputDevice.h"
#include <iostream>


PhantomInputDevice::PhantomInputDevice(LibPhantom::Phantom* phantom)
:phantom(phantom),
 newphantom(false),
 offset_x(0),
  offset_y(0),
  invert_y(true)
{
	if(!phantom){
		std::cout << "Could not find Phantom device." << std::endl;
		return;
	}
	phantom->startPhantom();
}

PhantomInputDevice::PhantomInputDevice()
: newphantom(true),
  offset_x(0),
  offset_y(0),
  invert_y(true)
{
	phantom = LibPhantom::Phantom::findPhantom(0);
	if(!phantom){
		std::cout << "Could not find Phantom device." << std::endl;
		return;
	}
	phantom->startPhantom();

}

PhantomInputDevice::~PhantomInputDevice()
{
	phantom->stopPhantom();
	if(newphantom){
		delete phantom;
	}
}

MouseState PhantomInputDevice::read()
{
	LibPhantom::PhantomDataRead d = phantom->isoIterate();
	MouseState s;
	s.lmb = (d.status.button1 == 0);
	s.x = d.encoder_x + offset_x;
	s.y = d.encoder_y + offset_y;

	if(invert_y){
		s.y = -s.y;
	}

	return s;
}

void PhantomInputDevice::reset()
{
	MouseState s = read();

	offset_x = -s.x;
	offset_y = -s.y;
}
