#pragma once

#include "IDevice.h"

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
		virtual void ClearColor(float red, float green, float blue, float alpha) override;
		
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
		virtual IIndexBuffer * CreateIndexBuffer(unsigned int stride, size_t size, Usage usage, const void * data) override;

		// draw
		virtual void Clear() override;

		virtual void DrawElement(DrawMode mode, size_t count, ValueType type, size_t offset) override;

	private:
		void ProcessInput();
	};
}