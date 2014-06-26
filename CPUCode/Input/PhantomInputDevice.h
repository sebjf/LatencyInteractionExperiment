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

class PhantomInputDevice : public InputDevice
{
public:
	PhantomInputDevice();
	PhantomInputDevice(LibPhantom::Phantom* phantom);
	~PhantomInputDevice();

	MouseState read();
	void reset();

private:
	LibPhantom::Phantom* phantom;

	bool newphantom;

	unsigned int offset_x;
	unsigned int offset_y;

	bool invert_y;

};


#endif /* PHANTOMMANAGER_H_ */
