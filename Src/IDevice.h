#pragma once

#include <DeviceCommon.h>
#include <vector>
#include <AttributeLayout.h>

namespace Catherine
{
	class IProgram;
	class ITexture;
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

		// state
		virtual void ClearColor(float red, float green, float blue, float alpha) = 0;
		
		virtual void SetFrontFace(FrontFaceMode mode) = 0;

		virtual void EnableDepthTest(bool enabled) = 0;
		virtual void SetDepthTestMode(DepthTestMode mode) = 0;
		
		virtual void EnableCullFace(bool enabled) = 0;
		virtual void SetCullFaceMode(CullFaceMode mode) = 0;

		// resource
		virtual IProgram * CreateProgram() = 0;

		virtual ITexture * CreateTexture() = 0;

		virtual IVertexArray * CreateVertexArray() = 0;
		virtual IVertexBuffer * CreateVertexBuffer(size_t size, Usage usage, const void * data, const std::vector<AttributeLayout> & attributes) = 0;
		virtual IIndexBuffer * CreateIndexBuffer(unsigned int stride, size_t size, Usage usage, const void * data) = 0;

		// draw
		virtual void Clear() = 0;

		virtual void DrawElement(DrawMode mode, size_t count, ValueType type, size_t offset) = 0;
	};
}
