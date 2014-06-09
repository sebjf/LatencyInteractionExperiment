/*
 * experiment.h
 *
 *  Created on: 4 Mar 2014
 *      Author: sfriston
 */

#ifndef EXPERIMENT_H_
#define EXPERIMENT_H_

#include "../Fitts/FittsLawTestConditions.h"
#include "Delay.h"

#include <ostream>
#include <istream>
#include <iostream>
#include <string>
#include <vector>
#include <msgpack.hpp>

template<typename T>
inline std::ostream& operator<<(std::ostream& stm, const std::vector<T>& obj) {

    if (!obj.empty()) {
        for (size_t i = 0 ; i<obj.size()-1 ; ++i) {
            stm << obj[i];
        }
        stm << obj.back();
    }
    return stm;
}

struct Datapoint
{
	/* This is the non-delayed user input - the motions the user has just made */
	MouseState real;

	/* This is the delayed user input that is fed to the cursor & tests - what the user sees */
	MouseState visible;

	Datapoint(MouseState real, MouseState visible)
	:real(real),
	 visible(visible)
	{
	}

	Datapoint()
	{
	}

	friend std::ostream& operator<< (std::ostream& stream, const Datapoint& dp);

	MSGPACK_DEFINE(real,visible);
};



/* A log is the largest discrete object that will be stored and records a user movement under certain conditions. A
 * log should record for 500 - 1000ms typically. Multiple logs may be written to a single file to make data wrangling
 * easier but there is no higher level of information, a Log should store everything required to peform analysis for
 * all experiments */

enum TestType
{
	Fitts,
	Steering
};

struct Log
{
	std::string participant_name;
	int participant_id;
	std::string datetime_human_readable;

	std::string conditions_filename;
	int type;
	int condition_id;

	std::vector<Datapoint> datapoints;

	Log();
	Log(std::string name, int id, std::string conditions_filename, TestType type, int condition_id);

	void Add(const Datapoint& dp)
	{
		datapoints.push_back(dp);
	}

	friend std::ostream& operator<< (std::ostream& stream, const Log& log);

	MSGPACK_DEFINE(participant_name, participant_id, datetime_human_readable, conditions_filename, type, condition_id, datapoints);
};

class Logger
{
public:
	Logger(std::string directory, std::string filenameformat, std::string extension);

	void AddNewLog(const Log& log);

	//Writes the current collection of logs to a new file. each call to this will result in a new file. files contain multiple logs.
	void Clear();
	void Save();
	void AppendAll();
	void Append(std::string filename);

	//Because msgpack does not work with pointers, the Logger object needs to control the logs objects itself because
	//it is not clear when or where the references will change. To get the active log always use this method.
	Log& CurrentLog();

	void SaveFormatMatlab();

private:
	std::vector<Log> logs;
	std::string directory;
	std::string filename_format;
	std::string filename_extension;

	std::string getNextFilename();

	void Write(std::ostream& stream);

	void Append(char* data, int size);

	std::vector<std::string> findLogFilenames();

	void SaveFormatMatlab(std::ostream& os);
	void SaveFormatMatlab(Log& log, std::ostream& os);

};

#endif /* EXPERIMENT_H_ */
