/*
 * PhantomManager.h
 *
 *  Created on: 12 Jun 2014
 *      Author: sfriston
 */

#ifndef PHANTOMMANAGER_H_
#define PHANTOMMANAGER_H_

#include <Simulator/Delay.h>
#include <Phantom/Phantom.h>

/* Since the phantom test util only uses the starting position for auto calibration,
 * its probably basing it on the zero and a known resolution, like below */

#define PH_X_ENCODER_MIN -2025
#define PH_X_ENCODER_MAX 2773
#define PH_X_ENCODER_ZERO 439
#define PH_X_SPAN_MM 350

#define PH_ENCODER_X_RESOLUTION 	13.7f
#define PH_ENCODER_X_ZERO			440

#define PH_ENCODER_Y_RESOLUTION		11.665f
#define PH_ENCODER_Y_ZERO			-1801

#define PH_ENCODER_Z_RESOLUTION		11.665f
#define PH_ENCODER_Z_ZERO			1487

#define RANGE_X  350 //in mm
#define RANGE_Y  245 //doesn't matter which way round these go
#define RANGE_Z  245

struct PhantomAxisCalibration
{
	float m_encoder_resolution; //in ticks per mm
	float m_encoder_zero;

	float AbsolutePosition(float encoder_value)
	{
		return ((encoder_value - m_encoder_zero) / m_encoder_resolution);
	}
};

class PhantomInputDevice : public InputDevice
{
public:
	PhantomInputDevice();
	PhantomInputDevice(LibPhantom::Phantom* phantom);
	virtual ~PhantomInputDevice();

	MouseState read();
	void reset();

private:
	LibPhantom::Phantom* phantom;

	bool newphantom;

	unsigned int offset_x;
	unsigned int offset_y;

	bool invert_y;

	/* calibration parameters for our particular device */

	PhantomAxisCalibration m_x_axis;
	PhantomAxisCalibration m_y_axis;
	PhantomAxisCalibration m_z_axis;

	int screen_center_x;
	int screen_center_y;

	float screen_pixel_pitch;
};


#endif /* PHANTOMMANAGER_H_ */
