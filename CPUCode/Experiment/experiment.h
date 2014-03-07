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

struct Coordinate
{
	int x;
	int y;
};

struct Condition
{
	int Latency_ms;
	int Width;
	Coordinate Position;
};

struct Datapoint
{
	double Timestamp_ms;
	Coordinate Position;
};

struct LogHeader
{
	struct Condition Condition;
	int DatapointCount;
	Datapoint* Datapoints;

	//The following members will not be written to file
	int MaxDatapoints;
};

class ExperimentLog
{
public:
	ExperimentLog(char* participant);
	void Begin(Condition condition);
	void Add(Coordinate coordinate);
	void Add(Datapoint datapoint);

	void Write();
	void Write(std::ostream& stream);

private:
	int expectedTimeInMinutes;
	int expectedLoopRateInMS;

	LogHeader log;

	PerformanceCounter* performanceCounter;
};

#endif /* EXPERIMENT_H_ */
