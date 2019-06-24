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

		virtual void ClearColor(float red, float green, float blue, float alpha) override;
		virtual void Clear() override;

		virtual void SetFrontFace(FrontFaceMode mode);

		virtual void EnableDepthTest(bool enabled);
		virtual void SetDepthTestMode(DepthTestMode mode);

		virtual void EnableCullFace(bool enabled);
		virtual void SetCullFaceMode(CullFaceMode mode);

	private:
		void ProcessInput();
	};
}