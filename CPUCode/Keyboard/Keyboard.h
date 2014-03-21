/*
 * Keyboard.h
 *
 *  Created on: 21 Mar 2014
 *      Author: sfriston
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

class KeyboardDevice
{
public:
	KeyboardDevice(char* dev)
	{
		fd = open(dev, O_RDONLY | O_NONBLOCK);
		if (fd == -1) {
			fprintf(stderr, "Cannot open %s: %s. Did you run CHMOD on the device?\n", dev, strerror(errno));
		}
	}

	bool isKeyDown(int keycode)
	{
		if(fd == -1){
			return false;
		}

		struct input_event ev;
		ssize_t n;

		n = read(fd, &ev, sizeof ev);

		if (n != sizeof ev) {
			errno = EIO;
			return false;
		}

		if (ev.type == EV_KEY && ev.value == 1){
			return (ev.code == keycode);
		}

		return false;
	}

private:
	int fd;
};


#endif /* KEYBOARD_H_ */
