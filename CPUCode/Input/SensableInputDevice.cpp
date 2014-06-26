/*
 * SensableInputDevice.cpp
 *
 *  Created on: 26 Jun 2014
 *      Author: sfriston
 */

#include "SensableInputDevice.h"


SensableInputDevice::SensableInputDevice() {

	device = hdInitDevice(HD_DEFAULT_DEVICE);


}

SensableInputDevice::~SensableInputDevice() {
	// TODO Auto-generated destructor stub
}
