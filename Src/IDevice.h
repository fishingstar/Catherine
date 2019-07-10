#pragma once

#include <DeviceCommon.h>
#include <vector>
#include <AttributeLayout.h>

namespace Catherine
{
	class IVertexArray;
	class IIndexBuffer;
	class IVertexBuffer;

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

		virtual void SetFrontFace(FrontFaceMode mode) = 0;

		virtual void EnableDepthTest(bool enabled) = 0;
		virtual void SetDepthTestMode(DepthTestMode mode) = 0;
		
		virtual void EnableCullFace(bool enabled) = 0;
		virtual void SetCullFaceMode(CullFaceMode mode) = 0;

		virtual IVertexArray * CreateVertexArray() = 0;
		virtual IVertexBuffer * CreateVertexBuffer(unsigned int size, unsigned int usage, const void * data, const std::vector<AttributeLayout> & attributes) = 0;
		virtual IIndexBuffer * CreateIndexBuffer(unsigned int stride, unsigned int size, unsigned int usage, const void * data) = 0;
	};
}
