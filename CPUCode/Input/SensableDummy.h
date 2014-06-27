/*
 * SensableDummy.h
 *
 *  Created on: 26 Jun 2014
 *      Author: sfriston
 */

#ifndef SENSABLEDUMMY_H_
#define SENSABLEDUMMY_H_

#include <Simulator/Delay.h>

class SensableDummy : public InputDevice
{
public:
	SensableDummy()
	:offset_x_in_mm(0),
	 offset_y_in_mm(0),
	 mm_per_pixel(0.25f),
	 invert_y(true)
	{}

	/* Current positions in world space of Phantom end effector in mm */
	float m_phantom_x;
	float m_phantom_y;

	bool m_phantom_lmb;

	MouseState read()
	{
		MouseState state;

		state.lmb = m_phantom_lmb;

		state.x = ((m_phantom_x + offset_x_in_mm) * (1/mm_per_pixel));
		state.y = ((m_phantom_y + offset_y_in_mm) * (1/mm_per_pixel));

		if(invert_y)
		{
			state.y = -state.y;
		}

		return state;
	}

	void reset()
	{
	}

private:
	float offset_x_in_mm;
	float offset_y_in_mm;
	float mm_per_pixel; //display pixel pitch
	bool invert_y;
};

#endif /* SENSABLEDUMMY_H_ */
