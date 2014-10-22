/*
 * PhantomManager.cpp
 *
 *  Created on: 12 Jun 2014
 *      Author: sfriston
 */

#include "PhantomInputDevice.h"
#include <iostream>
#include <math.h>


PhantomInputDevice::PhantomInputDevice(LibPhantom::Phantom* phantom)
:phantom(phantom),
 newphantom(false),
 offset_x(0),
  offset_y(0),
  invert_y(false)
{
	screen_pixel_pitch = 0.2768f;

	screen_center_x = 640;
	screen_center_y = 360;

	m_x_axis.m_encoder_resolution = PH_ENCODER_X_RESOLUTION;
	m_x_axis.m_encoder_zero = PH_ENCODER_X_ZERO;

	m_y_axis.m_encoder_resolution = PH_ENCODER_Y_RESOLUTION;
	m_y_axis.m_encoder_zero = PH_ENCODER_Y_ZERO;

	m_z_axis.m_encoder_resolution = PH_ENCODER_Z_RESOLUTION;
	m_z_axis.m_encoder_zero = PH_ENCODER_Z_ZERO;

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

MouseState PhantomInputDevice::readDevice()
{
	LibPhantom::PhantomDataRead d = phantom->isoIterate();
	MouseState s;

	//s.lmb = (d.status.button1 == 0) || (d.status.button2 == 0);

	//debounce the mouse
	s.lmb = false;
	bool mouse_down = (d.status.button1 == 0) || (d.status.button2 == 0);
	if(mouse_down){
		if(!m_mouse_down){
			s.lmb = true;
		}
	}
	m_mouse_down = mouse_down;

	float encoder_x = (signed short)d.encoder_x;
	float encoder_y = (signed short)d.encoder_y;
	float encoder_z = (signed short)d.encoder_z;

	float x = m_x_axis.AbsolutePosition(encoder_x) * (1 / (screen_pixel_pitch * 1.5)); //pitch updated for scaling (calculated)
	float y = m_z_axis.AbsolutePosition(encoder_y) * (1 / (screen_pixel_pitch * 1.5));

	x = x + 744; //centre of monitor (manually calibrated)
	y = (y) + 1000;

	s.x = x;
	s.y = y;

	if(invert_y){
		s.y = -s.y;
	}

	return s;
}

void PhantomInputDevice::reset()
{
	MouseState s = readDevice();

	offset_x = -s.x;
	offset_y = -s.y;
}
