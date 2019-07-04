#pragma once

#include <IRenderer.h>
#include <vector>

namespace Catherine
{
	class IWorld;
	// temp
	class ICamera;
	class ILight;
	class IMaterial;
	class IModel;

	class WorldRenderer : public IRenderer
	{
	public:
		virtual bool Initialize() override;
		virtual void Uninitialize() override;

		virtual void PreRender() override;
		virtual void Render() override;
		virtual void PostRender() override;

	public:
		void RegisterWorld(IWorld * world);

	private:
		void CreateLights();

	public:
		std::vector<IWorld *> m_Worlds;

		// cameraӦ����world��ĸ������Ϊ��demo����
		static ICamera * m_Camera;
		
		// lightӦ����world�ﴴ��������Ϊ��demo�в��Թ���
		static ILight * m_DirLight;
		static ILight * m_PointLight[4];
		static ILight * m_SpotLight;

		// materialӦ��Ҳ�Ǹ�����world�еĶ�������Ϊ��demo����
		IMaterial * m_Material = nullptr;

		// modelӦ����world��������Ϊ�˲���
		IModel * m_Model = nullptr;
	};
}
