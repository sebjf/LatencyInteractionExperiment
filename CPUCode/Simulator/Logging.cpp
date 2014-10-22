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
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/algorithm/string_regex.hpp>

#include "Logging.h"

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

Log::Log(int participant_id, std::string filename, TestType type, int condition_id)
:participant_id(participant_id),
 conditions_filename(filename),
 type(type),
 condition_id(condition_id)
{
	datetime_human_readable = currentDateTime();
}

Logger::Logger(int participant_id, std::string directory, std::string format, std::string extension)
 :participant_id(participant_id),
  filename_format(format),
  filename_extension(extension)
{
	std::ostringstream stream;
	stream << directory << "participant_" <<  participant_id << "/";
	this->directory =  stream.str();
	boost::filesystem::create_directories(this->directory);
}

void Logger::AddNewLog(const Log& log)
{
	logs.push_back(log);
}

Log& Logger::CurrentLog()
{
	return logs[logs.size()-1];
}

void Logger::Clear()
{
	logs.clear();
}

void Logger::Save()
{
	if(logs.size() <= 0){
		return;
	}

	std::string filename = getNextFilename();
	std::fstream myfile;
	myfile.exceptions(std::ios::failbit);
	try{
		myfile.open(filename.c_str(), std::ios::binary | std::ios::out);
		Write(myfile);
		myfile.close();
	}catch(const std::exception& ex){
		std::cout << "Could not write to " << filename << ex.what() << std::endl;
	}
}

void Logger::Write(std::ostream& myfile)
{
	msgpack::sbuffer sbuf;
	msgpack::pack(sbuf, logs);
	myfile.write(sbuf.data(),sbuf.size());
}

void Logger::Append(char* data, int size)
{
	msgpack::unpacked msg;
	msgpack::unpack(&msg, data, size);

	msgpack::object obj = msg.get();

	std::vector<Log> new_logs;
	obj.convert(&new_logs);

	logs.insert(logs.end(), new_logs.begin(), new_logs.end());
}

std::string Logger::getNextFilename()
{
	int suffix = 0;
	std::string full_path;

	do{
		std::stringstream sstr;
		sstr << directory << filename_format << suffix << filename_extension;
		suffix++;
		full_path = sstr.str();
	}while(boost::filesystem::exists(full_path));

	return full_path;
}

bool endsWidth (std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

//http://stackoverflow.com/questions/1257721/can-i-use-a-mask-to-iterate-files-in-a-directory-with-boost
std::vector<std::string> Logger::findLogFilenames()
{
	std::string target_path = directory;
	std::string my_filter = "*" + filename_extension;

	std::vector< std::string > all_matching_files;

	boost::filesystem::directory_iterator end_itr;
	for( boost::filesystem::directory_iterator i( target_path ); i != end_itr; ++i )
	{
	    boost::smatch what;
	    // Skip if no match
	    //useless centos 5 has an ancient version of boost from 2006
//	    if( !boost::regex_match( i->leaf(), what, my_filter ) ) continue;

	    if(endsWidth( i->leaf(), filename_extension)){
	    	// File matches, store it
	    	all_matching_files.push_back( i->string() );
	    }
	}

	return all_matching_files;
}

void Logger::Append(std::string filename)
{
	std::ifstream file(filename.c_str(), std::ios::binary | std::ios::in);
	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	char* data = new char[size];
	if (file.read(data, size))
	{
	    Append(data, size);
	}
	delete data;
	file.close();
}

void Logger::AppendAll()
{
	std::vector<std::string> filenames = findLogFilenames();
	for(unsigned int i = 0; i < filenames.size(); i++)
	{
		Append(filenames[i]);
	}
}

void Logger::SaveFormatMatlab()
{
	AppendAll();
	std::cout << "Writing " << logs.size() << " logs.";

	std::fstream myfile;
	std::string filename = directory + filename_format + "MATLAB" + ".csv";
	myfile.open(filename.c_str(), std::ios::out);

	myfile.precision(std::numeric_limits<double>::digits10 + 2);

	myfile << logs;
	myfile.close();
}

std::ostream& operator<< (std::ostream& stream, const Log& log)
{
	stream << log.conditions_filename << ",";
	stream << log.participant_id   << ",";
	stream << log.datetime_human_readable << ",";

	stream << log.type << ",";
	stream << log.condition_id << ",";
	stream << log.datapoints.size() << ",";

	for(unsigned int i = 0; i < log.datapoints.size()-1; i++){
		stream << log.datapoints[i] << ",";
	}
	stream << log.datapoints.back();

	stream << std::endl;

	return stream;
}

std::ostream& operator<< (std::ostream& stream, const Datapoint& dp)
{
	stream << dp.real << "," << dp.visible;
	return stream;
}

