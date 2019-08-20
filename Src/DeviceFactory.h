#pragma once

namespace Catherine
{
	class IDevice;

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