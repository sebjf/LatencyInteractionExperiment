/*
 * experiment.cpp
 *
 *  Created on: 4 Mar 2014
 *      Author: sfriston
 */

#include "experiment.h"

#include <stdlib.h>
#include <memory.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>


using namespace std;

ExperimentLog::ExperimentLog(char* participant)
{
	expectedTimeInMinutes = 20;
	expectedLoopRateInMS = 1;

	long datapoints = expectedTimeInMinutes * 60 * (1000 / expectedLoopRateInMS);

	log.MaxDatapoints = datapoints;
	log.DatapointCount = 0;
	log.Datapoints = (Datapoint*)malloc(log.MaxDatapoints * sizeof(Datapoint));

	performanceCounter = new PerformanceCounter();
}

void ExperimentLog::Begin(Condition condition)
{
	log.Condition = condition;
}

void ExperimentLog::Add(Coordinate coordinate)
{
	Datapoint d;
	d.Position = coordinate;
	d.Timestamp_ms = performanceCounter->GetTimestamp_ms();
	Add(d);
}

void ExperimentLog::Add(Datapoint datapoint)
{
	if(log.DatapointCount >= log.MaxDatapoints){
		return;
	}
	log.Datapoints[log.DatapointCount] = datapoint;
	log.DatapointCount++;

}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

void ExperimentLog::Write(ostream& myfile)
{
	myfile.write((char*)&log.Condition, sizeof(Condition));
	myfile.write((char*)&log.DatapointCount, sizeof(int));
	myfile.write((char*)log.Datapoints, sizeof(Datapoint) * log.DatapointCount);
}

void ExperimentLog::Write()
{
	string filename = string("participant 1") + string("_") + currentDateTime();
	ofstream myfile;

	myfile.open(filename.c_str(), ios::binary);

	Write(myfile);

	myfile.close();
}

