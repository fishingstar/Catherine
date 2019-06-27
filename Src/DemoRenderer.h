#pragma once

#include <IRenderer.h>

namespace Catherine
{
	class ICamera;
	class ILight;
	class IMaterial;
	class IModel;

	class DemoRenderer : public IRenderer
	{
	public:
		virtual bool Initialize() override;
		virtual void Uninitialize() override;

		virtual void PreRender() override;
		virtual void Render() override;
		virtual void PostRender() override;

	private:
		void CreateLights();

	private:
		// cameraӦ����world��ĸ������Ϊ��demo����
		ICamera * m_Camera = nullptr;
		
		// lightӦ����world�ﴴ��������Ϊ��demo�в��Թ���
		ILight * m_DirLight = nullptr;
		ILight * m_PointLight[4] = { nullptr };
		ILight * m_SpotLight = nullptr;

		// materialӦ��Ҳ�Ǹ�����world�еĶ�������Ϊ��demo����
		IMaterial * m_Material = nullptr;

		// modelӦ����world��������Ϊ�˲���
		IModel * m_Model = nullptr;
	};
}
