#pragma once

namespace Catherine
{
	class IDevice
	{
	public:
		virtual bool Initialize() = 0;
		virtual void Uninitialize() = 0;

		virtual bool WindowShouldClose() = 0;

		virtual void OnFrameBegin() = 0;
		virtual void OnFrameEnd() = 0;

		virtual void ClearColor(float red, float green, float blue, float alpha) = 0;
		virtual void Clear() = 0;
	};
}
