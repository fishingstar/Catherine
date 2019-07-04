#pragma once

namespace Catherine
{
	class IRenderContext;
	class ICameraContext;
	class ILightContext;

	class IWorldContext
	{
	public:
		virtual void AddRenderContext(IRenderContext * context) = 0;
		virtual void SetCameraContext(ICameraContext * context) = 0;
		virtual void SetLightContext(ILightContext * context) = 0;
	};
}