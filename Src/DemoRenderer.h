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
		// camera应该是world里的概念，这里为了demo测试
		ICamera * m_Camera = nullptr;
		
		// light应该在world里创建，这里为了demo中测试功能
		ILight * m_DirLight = nullptr;
		ILight * m_PointLight[4] = { nullptr };
		ILight * m_SpotLight = nullptr;

		// material应该也是附着在world中的对象，这里为了demo测试
		IMaterial * m_Material = nullptr;

		// model应该由world管理，这里为了测试
		IModel * m_Model = nullptr;
	};
}
