#pragma once

#include "DeviceCommon.h"
#include <vector>
#include "AttributeLayout.h"

namespace Catherine
{
	class IProgram;
	class ITexture;
	class IVertexArray;
	class IIndexBuffer;
	class IVertexBuffer;
	class IRenderTarget;

	class IDevice
	{
	public:
		virtual bool Initialize() = 0;
		virtual void Uninitialize() = 0;

		virtual bool Close() = 0;

		virtual void OnFrameBegin() = 0;
		virtual void OnFrameEnd() = 0;

		// state
		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void SetClearColor(float red, float green, float blue, float alpha) = 0;
		
		virtual void SetFrontFace(FrontFaceMode mode) = 0;

		virtual void EnableDepthTest(bool enabled) = 0;
		virtual void SetDepthTestMode(DepthTestMode mode) = 0;
		
		virtual void EnableCullFace(bool enabled) = 0;
		virtual void SetCullFaceMode(CullFaceMode mode) = 0;

		virtual void EnableBlend(bool enabled) = 0;
		virtual void SetBlendEquation(BlendEquation equation) = 0;
		virtual void SetBlendFunc(BlendFunc src, BlendFunc dst, BlendFunc src_alpha, BlendFunc dst_alpha) = 0;

		// resource
		virtual IProgram * CreateProgram() = 0;

		virtual ITexture * CreateTexture() = 0;
		virtual ITexture * CreateCubeTexture() = 0;
		virtual IRenderTarget * CreateRenderTarget() = 0;

		virtual IVertexArray * CreateVertexArray() = 0;
		virtual IVertexBuffer * CreateVertexBuffer(size_t size, Usage usage, const void * data, const std::vector<AttributeLayout> & attributes) = 0;
		virtual IIndexBuffer * CreateIndexBuffer(uint8_t stride, size_t size, Usage usage, const void * data) = 0;

		// draw
		virtual void Clear() = 0;

		virtual void DrawElement(DrawMode mode, size_t count, ValueType type, size_t offset) = 0;

		// other
		virtual void BlitFrameBuffer(uint32_t src_x0, uint32_t src_y0, uint32_t src_x1, uint32_t src_y1, uint32_t dst_x0, uint32_t dst_y0, uint32_t dst_x1, uint32_t dst_y1, BitField bufferbits, Filter filter) = 0;
	};
}
