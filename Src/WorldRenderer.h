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
		
		// light应该在world里创建，这里为了demo中测试功能
		static ILight * m_DirLight;
		static ILight * m_PointLight[4];
		static ILight * m_SpotLight;
	};
}
