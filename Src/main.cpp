#include <global.h>
#include <log.h>
#include <DeviceFactory.h>

using namespace Catherine;

int main()
{
	g_Device = DeviceFactory::Instance()->CreateDevice();
	if (g_Device == nullptr)
	{
		LogModule::Instance()->LogError("Create Device Failed...");
		return -1;
	}

	bool tmp_initialized = g_Device->Initialize();
	if (!tmp_initialized)
	{
		LogModule::Instance()->LogError("Device Initialize Failed...");
		return -1;
	}

	while (!g_Device->WindowShouldClose())
	{
		g_Device->OnFrameBegin();

		// logic, render

		g_Device->OnFrameEnd();
	}

	g_Device->Uninitialize();
	
	return 0;
}
