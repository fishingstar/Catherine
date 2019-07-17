#pragma once

#include "IDevice.h"

namespace Catherine
{
	class DeviceFactory
	{
	public:
		static DeviceFactory * Instance();

		IDevice * CreateDevice();
		void DeleteDevice(IDevice * device);

	private:
		DeviceFactory() { }
	};
}