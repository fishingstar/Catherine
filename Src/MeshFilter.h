#pragma once

#include "IComponent.h"
#include <vector>
#include "assimp/scene.h"

namespace Catherine
{
	class IMesh;

	class MeshFilter : public IComponent
	{
	public:
		virtual void OnAddComponent(SceneObject * owner) override;
		virtual void OnRemoveComponent(SceneObject * owner) override;

		virtual void Update(float deltaTime) override;

		virtual ComponentKind GetComponentKind() const override;

	public:
		void LoadFromFile(const char * path);

		const std::vector<IMesh *> & GetMeshes() const { return m_Meshes; }

	private:
		void ProcessNode(aiNode * node, const aiScene * scene);
		IMesh * ProcessMesh(aiMesh * mesh, const aiScene * scene);

	private:
		std::vector<IMesh *> m_Meshes;
	};
}