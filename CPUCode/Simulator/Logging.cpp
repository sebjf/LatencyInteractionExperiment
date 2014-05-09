/*
 * experiment.cpp
 *
 *  Created on: 4 Mar 2014
 *      Author: sfriston
 */

#include <string>
#include <iterator>
#include <fstream>
#include <iostream>
#include <time.h>
#include <sstream>
#include <sys/stat.h>

#include "Logging.h"
#include "Context.h"

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

Log::Log()
{
	//this exists soley for msgpack
}

Log::Log(std::string name, int id, FittsLawTestCondition* condition)
{
	participant_name = name;
	participant_id = id;
	test_condition = *condition;
	datetime_human_readable = currentDateTime();
}

Logger::Logger(std::string directory, std::string format)
{
	logfiles_directory = directory;
	filename_format = format;
}

void Logger::AddNewLog(Log log)
{
	logs.push_back(log);
}

Log& Logger::CurrentLog()
{
	std::vector<Log>::iterator i = logs.end();
	return *i;
}

void Logger::Clear()
{
	logs.clear();
}

void Logger::Write()
{
	std::fstream myfile;
	myfile.open(getNextFilename().c_str(), std::ios::binary);
	Write(myfile);
	myfile.close();
}

void Logger::Write(std::fstream& myfile)
{
	msgpack::sbuffer sbuf;
	msgpack::pack(sbuf, logs);
	myfile.write(sbuf.data(),sbuf.size());
}


void Logger::Read(char* data, int size)
{
	msgpack::unpacked msg;
	msgpack::unpack(&msg, data, size);

	msgpack::object obj = msg.get();

	obj.convert(&logs);
}

void Logger::WriteToMatlab()
{

}

//http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
inline bool fileexists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0); 
}

/* */
std::string Logger::getNextFilename()
{
	int suffix = 0;
	std::string full_path;

	do{
		std::stringstream sstr;
		sstr << logfiles_directory << filename_format << suffix << ".dat";
		suffix++;
		full_path = sstr.str();
	}while(fileexists(full_path));

	return full_path;
}

