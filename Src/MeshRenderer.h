#pragma once

#include <IComponent.h>
#include <vector>

namespace Catherine
{
	class WorldContext;
	class RenderContext;
	class IMaterial;

	class MeshRenderer : public IComponent
	{
	public:
		virtual void OnAddComponent(SceneObject * owner) override;
		virtual void OnRemoveComponent(SceneObject * owner) override;

		virtual void Update(float deltaTime) override;

		virtual ComponentKind GetComponentKind() const override;

	public:
		void Render(WorldContext * context);

	private:
		void ClearRenderContext();

	private:
		// RenderContext should be managed by pool
		std::vector<RenderContext *> m_RenderContexts;
		std::vector<IMaterial *> m_Materials;
	};
}