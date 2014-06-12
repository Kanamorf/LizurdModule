#pragma once
#include <string>
#include <fstream>

namespace Lizurd
{

	class Logger
	{
	public:

		//Only one Logger so don't copy
		Logger(const Logger& logger) {}         
		Logger& operator=(const Logger&);      
		static Logger& GetInstance();
		void Log(const std::string &source, const std::string &log);
		void CriticalLog(const std::string &source, const std::string &log);
		std::string GetTime();
		static void CleanUp();
	private:
		Logger(void);
		~Logger(void);
		static Logger* _instance;
		std::string _logFileName;
		
		std::ofstream _logfile;
	};

}