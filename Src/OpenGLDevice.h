#pragma once

#include <IDevice.h>

namespace Catherine
{
	class OpenGLDevice : public IDevice
	{
	public:
		virtual bool Initialize() override;
		virtual void Uninitialize() override;

		virtual void OnFrameBegin() override;
		virtual void OnFrameEnd() override;

		virtual bool WindowShouldClose() override;

	private:
		void ProcessInput();
	};
}