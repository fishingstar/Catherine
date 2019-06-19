#pragma once

#include <IRenderer.h>

namespace Catherine
{
	class IProgram;
	class ITexture;

	class DemoRenderer : public IRenderer
	{
	public:
		virtual bool Initialize() override;
		virtual void Uninitialize() override;

		virtual void PreRender() override;
		virtual void Render() override;
		virtual void PostRender() override;

	private:
		IProgram * m_Program = nullptr;
		ITexture * m_Texture1 = nullptr;
		ITexture * m_Texture2 = nullptr;

		unsigned int m_VAO = 0;
	};
}
