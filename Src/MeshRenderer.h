#pragma once

#include "IComponent.h"
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
		// collect rendercontexts
		void Render(WorldContext * context);

		// add to material list to render meshes
		void AddMaterial(IMaterial * material);

		// cast shadow properties
		bool GetCastShadow() const { return m_CastShadow; }
		void SetCastShadow(bool value) { m_CastShadow = value; }

		// receive shadow properties
		bool GetReveiceShadow() const { return m_ReceiveShadow; }
		void SetReceiveShadow(bool value) { m_ReceiveShadow = value; }

	private:
		void ClearRenderContext();

	private:
		// TODO : RenderContext should be managed by pool
		std::vector<RenderContext *> m_RenderContexts;
		std::vector<IMaterial *> m_Materials;

		bool m_CastShadow = true;
		bool m_ReceiveShadow = true;
	};
}