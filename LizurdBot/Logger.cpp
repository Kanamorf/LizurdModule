#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <BWAPI.h>

#include "Logger.h"


using namespace std;

Logger* Logger::_instance = 0;

/// <summary>
/// Prevents a default instance of the <see cref="Logger" /> class from being created.
/// </summary>
Logger::Logger(void):
_tabCount(0)
{
	std::stringstream ss;
	ss << "c:\\SCLog\\";
	ss << "Release\\";
	ss << "StarCraftLog " + GetTime() + ".txt";
	_logFileName = ss.str();
}

/// <summary>
/// Finalizes an instance of the <see cref="Logger" /> class.
/// </summary>
Logger::~Logger(void)
{
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
void Logger::StartLog(const string &log)
{
	_tabCount = 0;
	ofstream logfile;
	logfile.open ( _logFileName.c_str(), ios::out | ios::app);
	logfile << GetTime() << " " << log << endl;
	logfile.close();
}

/// <summary>
/// Logs the specified string.
/// </summary>
/// <param name="log">The string to log.</param>
void Logger::Log(const string &log)
{
	_tabCount++;
	ofstream logfile;
	logfile.open ( _logFileName.c_str(), ios::out | ios::app);
	logfile << GetTime() << " ";
	for(int i = 0; i< _tabCount;i++)
	{
		logfile << "\t";
	}
	logfile << log << endl;
	logfile.close();
}

void Logger::CriticalLog(const string &log)
{
	ofstream logfile;
	logfile.open ( _logFileName.c_str(), ios::out | ios::app);
	logfile << GetTime() << " ";
	logfile << log << endl << endl;
	logfile.close();
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

void Logger::TimerLog(const string &log)
{
	ofstream logfile;
	logfile.open ( _logFileName.c_str(), ios::out | ios::app);
	logfile << GetTime() << " ";
	logfile << log << endl << endl;
	logfile.close();
}
