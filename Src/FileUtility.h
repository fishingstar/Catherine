#pragma once
#include <string>

namespace Catherine
{
	class FileUtility
	{
	public:
		static size_t LoadFileContent(const char * param_Path, void ** param_Ptr);
		static std::string GetDictionary(const std::string & path);
	};
}