#include "LogUtility.h"
#include "log.h"

namespace Catherine
{
	void Log(const char * param_Log)
	{
		LogModule::Instance()->Log(param_Log);
	}

	void Log(const std::string & param_Log)
	{
		Log(param_Log.c_str());
	}

	void LogWarning(const char * param_Log)
	{
		LogModule::Instance()->LogWarning(param_Log);
	}

	void LogWarning(const std::string & param_Log)
	{
		LogWarning(param_Log.c_str());
	}

	void LogError(const char * param_Log)
	{
		LogModule::Instance()->LogError(param_Log);
	}

	void LogError(const std::string & param_Log)
	{
		LogError(param_Log.c_str());
	}
}