#pragma once

#include <IRenderer.h>
#include <vector>

namespace Catherine
{
	class IWorld;
	// temp
	class ILight;

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
		
		// lightӦ����world�ﴴ��������Ϊ��demo�в��Թ���
		static ILight * m_DirLight;
		static ILight * m_PointLight[4];
		static ILight * m_SpotLight;
	};
}
