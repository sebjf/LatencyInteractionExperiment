#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
#include "MaxSLiCInterface.h"

#include <MaxVideoCpuResources.h>

#include "Experiment/experiment.h"

#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>

struct InputUpdate
{
	uint x;
	uint y;
	uint padding;
	uint padding2;
};


//http://stackoverflow.com/questions/20943322/accessing-keys-from-linux-input-device

static const char *const evval[3] = {
    "RELEASED",
    "PRESSED ",
    "REPEATED"
};

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


int main(int argc, char *argv[])
{

	if(isSim(argc,argv)){
		printf("Running Simulation.");
	}

	makeRealtime();

	Mouse* mouse = new Mouse();
	KeyboardDevice* keyboard = new KeyboardDevice("/dev/input/event0");
	ExperimentLog* log = new ExperimentLog("participant");


	/* Configure the card and start the kernel running */
	max_file_t* maxfile = LatencyInteractionExperiment_init();
	max_engine_t* engine = max_load(maxfile, "local:*");
	max_actions_t* actions = max_actions_init(maxfile, "default");

	VirtualMonitor* monitor = new VirtualMonitor(maxfile);

	if(isSim(argc,argv)){
		monitor->Connect(engine);
	}

	Stream* inputStream = new Stream(engine,"positions",sizeof(InputUpdate));

	InputUpdate update;
	update.x = 0;
	update.y = 0;

	max_run(engine, actions);

	mouse->Scale = 0.4f;

	float x = 0;
	float y = 0 ;

	while(1){
		MouseDelta m = mouse->readMouse(false);

		x += m.x;
		y += m.y;

		update.x = (int)x;
		update.y = (int)y;

		inputStream->Write(&update);

		monitor->Refresh(1066);

		Coordinate c;
		c.x = (int)x;
		c.y = (int)y;
		log->Add(c);

		if(keyboard->isKeyDown(KEY_Q)){
			break;
		}
	}

	log->Write();

	printf("\nDone.\n");
	return 0;
}
