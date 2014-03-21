/*
 * experiment.h
 *
 *  Created on: 4 Mar 2014
 *      Author: sfriston
 */

#ifndef EXPERIMENT_H_
#define EXPERIMENT_H_

#include "../Metrics/metrics.h"

#include <stdio.h>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>

struct Datapoint
{
	double timestamp_ms;
	int x;
	int y;

	Datapoint()
	{
		timestamp_ms = 0;
		x = 0;
		y = 0;
	}

	Datapoint(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	friend std::ostream& operator<<(std::ostream& os, const Datapoint& dt);
};



struct Log
{
	std::string name;
	std::string directory;
	std::vector<Datapoint> datapoints;
};

class ExperimentLog
{
public:
	ExperimentLog(std::string name, std::string directory);

	void Add(Datapoint datapoint);

	void Write();
	void Write(std::ostream& stream);

private:
	Log* log;
	PerformanceCounter* performanceCounter;
};

#endif /* EXPERIMENT_H_ */
