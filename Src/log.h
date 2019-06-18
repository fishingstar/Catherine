#pragma once

namespace Catherine
{
	class LogModule
	{
	public:
		static LogModule * Instance();

		void Log(const char * param_Log);
		void LogWarning(const char * param_Log);
		void LogError(const char * param_Log);

	private:
		LogModule() { }

	};
}
