#pragma once

#include <string>

namespace Catherine
{
	class IProgram;

	class ProgramManager
	{
	public:
		static ProgramManager * Instance();

		IProgram * GetProgram(const std::string & vertex, const std::string & fragment);

	private:
		ProgramManager() { }

	private:

	};
}