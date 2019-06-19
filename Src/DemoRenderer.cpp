#include <DemoRenderer.h>
#include <OpenGLProgram.h>

namespace Catherine
{
	bool DemoRenderer::Initialize()
	{
		m_Program = new GLProgram();
		m_Program->AttachShader(nullptr, nullptr);
		m_Program->Compile();
		m_Program->Link();
		return true;
	}

	void DemoRenderer::Uninitialize()
	{

	}

	void DemoRenderer::PreRender()
	{

	}

	void DemoRenderer::Render()
	{
		m_Program->Use();
	}

	void DemoRenderer::PostRender()
	{

	}
}
