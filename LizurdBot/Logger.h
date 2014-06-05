#pragma once
#include <string>

class Logger
{
public:

	//Only one Logger so don't copy
	Logger(const Logger& blackboard) {}         
	Logger& operator=(const Logger&);      
	static Logger& GetInstance();
	void Log(const std::string &source, const std::string &log);
	void CriticalLog(const std::string &source, const std::string &log);
	std::string GetTime();

private:
	Logger(void);
	~Logger(void);
	static Logger* _instance;
	std::string _logFileName;
	static void CleanUp();
};
