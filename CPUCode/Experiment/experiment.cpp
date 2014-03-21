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
#include <iterator>
#include <fstream>
#include <iostream>
#include <time.h>


using namespace std;

std::ostream& operator<<(std::ostream& os, const Datapoint& dt)
{
	os << dt.timestamp_ms;
	os << dt.x;
	os << dt.y;
	return os;
}

ExperimentLog::ExperimentLog(std::string name, std::string directory)
{
	log = new Log();
	log->name = name;
	log->directory = directory;

	performanceCounter = new PerformanceCounter();
}

void ExperimentLog::Add(Datapoint datapoint)
{
	if(datapoint.timestamp_ms == 0){
		datapoint.timestamp_ms = performanceCounter->GetTimestamp_ms();
	}
	log->datapoints.push_back(datapoint);
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
	myfile.write(log->name.c_str(), strlen(log->name.c_str()));
	myfile.write((char*)&(log->datapoints[0]), (log->datapoints.size() * sizeof(Datapoint)));

	//std::ostream_iterator<Datapoint> output_iterator(myfile);
	//std::copy(log->datapoints.begin(), log->datapoints.end(), output_iterator);
}

void ExperimentLog::Write()
{
	std::string filename = log->name + string("_") + currentDateTime();

	ofstream myfile;

	myfile.open((log->directory + filename).c_str(), ios::binary);

	Write(myfile);

	myfile.close();
}

