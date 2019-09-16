#pragma once

#include "IDevice.h"

struct GLFWwindow;

namespace Catherine
{
	class OpenGLDevice : public IDevice
	{
	public:
		virtual bool Initialize() override;
		virtual void Uninitialize() override;

		virtual void OnFrameBegin() override;
		virtual void OnFrameEnd() override;

		virtual bool Close() override;

		// state
		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColor(float red, float green, float blue, float alpha) override;
		
		virtual void SetFrontFace(FrontFaceMode mode) override;

		virtual void EnableDepthTest(bool enabled) override;
		virtual void SetDepthTestMode(DepthTestMode mode) override;

		virtual void EnableCullFace(bool enabled) override;
		virtual void SetCullFaceMode(CullFaceMode mode) override;

		virtual void EnableBlend(bool enabled) override;
		virtual void SetBlendEquation(BlendEquation equation) override;
		virtual void SetBlendFunc(BlendFunc src, BlendFunc dst, BlendFunc src_alpha, BlendFunc dst_alpha) override;

		// resource
		virtual IProgram * CreateProgram() override;

		virtual ITexture * CreateTexture() override;
		virtual ITexture * CreateCubeTexture() override;
		virtual IRenderTarget * CreateRenderTarget() override;

		virtual IVertexArray * CreateVertexArray() override;
		virtual IVertexBuffer * CreateVertexBuffer(size_t size, Usage usage, const void * data, const std::vector<AttributeLayout> & attributes) override;
		virtual IIndexBuffer * CreateIndexBuffer(uint8_t stride, size_t size, Usage usage, const void * data) override;

		// draw
		virtual void Clear(BitField bits) override;

		virtual void DrawElement(DrawMode mode, size_t count, ValueType type, size_t offset) override;

		// other
		virtual void BlitFrameBuffer(uint32_t src_x0, uint32_t src_y0, uint32_t src_x1, uint32_t src_y1, uint32_t dst_x0, uint32_t dst_y0, uint32_t dst_x1, uint32_t dst_y1, BitField bufferbits, Filter filter) override;

	private:
		void ProcessInput();

	private:
		GLFWwindow * m_Window = nullptr;
	};
}