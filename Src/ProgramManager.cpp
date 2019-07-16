#include <ProgramManager.h>
#include <IDevice.h>
#include <IProgram.h>

namespace Catherine
{
	extern IDevice * g_Device;

	ProgramManager * ProgramManager::Instance()
	{
		static ProgramManager s_instance;
		return &s_instance;
	}

	IProgram * ProgramManager::GetProgram(const std::string & vertex, const std::string & fragment)
	{
		IProgram * tmp_result = nullptr;

		if (!vertex.empty() && !fragment.empty())
		{
			// TODO : ckeck compile and link result...
			tmp_result = g_Device->CreateProgram();
			tmp_result->AttachShader(vertex.c_str(), fragment.c_str());
			tmp_result->Compile();
			tmp_result->Link();
		}
		
		return tmp_result;
	}
}