/*
 * SensableInputDevice.h
 *
 *  Created on: 26 Jun 2014
 *      Author: sfriston
 */

#ifndef SENSABLEINPUTDEVICE_H_
#define SENSABLEINPUTDEVICE_H_

#include <HD/hd.h>

class SensableInputDevice {
public:
	SensableInputDevice();
	virtual ~SensableInputDevice();

private:
	static bool device_initialised;
	static HHD device;
};

#endif /* SENSABLEINPUTDEVICE_H_ */
