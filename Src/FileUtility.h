#pragma once

namespace Catherine
{
	class FileUtility
	{
	public:
		static unsigned int LoadFileContent(const char * param_Path, void ** param_Ptr);
	};
}