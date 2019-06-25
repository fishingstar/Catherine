#pragma once

#include <IRenderer.h>

namespace Catherine
{
	class ICamera;
	class ILight;
	class IMaterial;

	class DemoRenderer : public IRenderer
	{
	public:
		virtual bool Initialize() override;
		virtual void Uninitialize() override;

		virtual void PreRender() override;
		virtual void Render() override;
		virtual void PostRender() override;

	private:
		// lightӦ����world�ﴴ��������Ϊ��demo�в��Թ���
		void CreateLights();

	private:
		ICamera * m_Camera = nullptr;
		
		ILight * m_DirLight = nullptr;
		ILight * m_PointLight[4] = { nullptr };

		IMaterial * m_Material = nullptr;

		unsigned int m_VAO = 0;
	};
}
