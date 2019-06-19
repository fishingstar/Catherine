#pragma once

#include <IRenderer.h>

namespace Catherine
{
	class IProgram;

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
	};
}
