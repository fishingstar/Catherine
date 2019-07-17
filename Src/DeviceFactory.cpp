#include "DeviceFactory.h"
#include "OpenGLDevice.h"

namespace Catherine
{
	DeviceFactory * DeviceFactory::Instance()
	{
		static DeviceFactory s_instance;
		return &s_instance;
	}

	IDevice * DeviceFactory::CreateDevice()
	{
		// opengl
		IDevice * tmp_result = new OpenGLDevice();
		// directx
		// ...

		return tmp_result;
	}

	void DeviceFactory::DeleteDevice(IDevice * device)
	{
		if (device != nullptr)
		{
			delete device;
		}
	}
}