#pragma once

#include <string>

namespace Catherine
{
	void Log(const char * param_Log);
	void Log(const std::string & param_Log);
	
	void LogWarning(const char * param_Log);
	void LogWarning(const std::string & param_Log);

	void LogError(const char * param_Log);
	void LogError(const std::string & param_Log);
}