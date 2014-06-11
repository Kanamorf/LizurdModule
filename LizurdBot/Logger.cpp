#include <iostream>

#include <ctime>
#include <sstream>
#include <BWAPI.h>
#include <iomanip>

#include "Logger.h"


using namespace std;
using namespace Lizurd;

Logger* Logger::_instance = 0;

/// <summary>
/// Prevents a default instance of the <see cref="Logger" /> class from being created.
/// </summary>
Logger::Logger(void)
{
	std::stringstream ss;
	ss << "c:\\SCLog\\";
	ss << "Release\\";
	ss << "StarCraftLog " + GetTime() + ".txt";
	_logFileName = ss.str();
	
	_logfile.open ( _logFileName.c_str(), ios::out | ios::app);
}

/// <summary>
/// Finalizes an instance of the <see cref="Logger" /> class.
/// </summary>
Logger::~Logger(void)
{
	_logfile.close();
}

/// <summary>
/// Gets the instance.
/// </summary>
/// <returns>The instance of the logger class</returns>
Logger& Logger::GetInstance()
{
	if(_instance == 0)
	{
		_instance = new Logger();
	}
	return *_instance;
}

/// <summary>
/// Logs the specified string.
/// </summary>
/// <param name="log">The string to log.</param>
void Logger::Log(const std::string &source, const string &log)
{
	
	_logfile << std::setw(11) << std::setfill(' ') << std::left << GetTime() << " ";
	_logfile  << std::setw(35) << std::setfill(' ') << std::left  << source  << std::right << log << endl;

}

void Logger::CriticalLog(const std::string &source, const string &log)
{
	_logfile << GetTime() << " ";
	_logfile << "[" << source << "]" << std::setw(20) << " " << log << endl << endl;

	BWAPI::Broodwar->sendText(log.c_str());
}

/// <summary>
/// Cleans up.
/// </summary>
void Logger::CleanUp()
{
	delete _instance; 
	_instance = 0;
}

/// <summary>
/// Gets the time.
/// </summary>
/// <returns>The current time formatted as a string</returns>
std::string Logger::GetTime()
{
	std::stringstream ss;
	time_t t = time(0);   // get time now
    struct tm now;
	errno_t err = localtime_s( &now, &t );
	ss << "{" << now.tm_hour << '-' << now.tm_min << '-' <<  now.tm_sec << "}";
	return ss.str();
}

