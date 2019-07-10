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

		virtual void SetFrontFace(FrontFaceMode mode) override;

		virtual void EnableDepthTest(bool enabled) override;
		virtual void SetDepthTestMode(DepthTestMode mode) override;

		virtual void EnableCullFace(bool enabled) override;
		virtual void SetCullFaceMode(CullFaceMode mode) override;

		virtual IVertexArray * CreateVertexArray() override;
		virtual IVertexBuffer * CreateVertexBuffer(unsigned int size, unsigned int usage, const void * data, const std::vector<AttributeLayout> & attributes) override;
		virtual IIndexBuffer * CreateIndexBuffer(unsigned int stride, unsigned int size, unsigned int usage, const void * data) override;

	private:
		void ProcessInput();
	};
}