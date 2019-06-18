#pragma once

#include <IDevice.h>

namespace Catherine
{
	class DeviceFactory
	{
	public:
		static DeviceFactory * Instance();

		IDevice * CreateDevice();

	private:
		DeviceFactory() { }
	};
}