#include <log.h>
#include <iostream>

namespace Catherine
{
	LogModule * LogModule::Instance()
	{
		static LogModule s_instance;
		return &s_instance;
	}

	void LogModule::Log(const char * param_Log)
	{
		std::cout << "[Log]" << param_Log << std::endl;
	}

	void LogModule::LogWarning(const char * param_Log)
	{
		std::cout << "[Warning]" << param_Log << std::endl;
	}

	void LogModule::LogError(const char * param_Log)
	{
		std::cout << "[Error]" << param_Log << std::endl;
	}
}
