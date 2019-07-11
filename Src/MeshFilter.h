#pragma once

#include <IComponent.h>
#include <vector>
#include <unordered_map>
#include <assimp/scene.h>

namespace Catherine
{
	class IMesh;
	class IMaterial;
	class ITexture;

	class MeshFilter : public IComponent
	{
	public:
		virtual void Update(float deltaTime) override;
		virtual ComponentKind GetComponentKind() const override;

	public:
		void LoadFromFile(const char * path);

		// temp interface : meshrenderer need to get material information for rendering
		// material will be moved to meshrenderer in the future
		const std::vector<IMaterial *> & GetMaterials() const { return m_Materials; }
		const std::vector<IMesh *> & GetMeshes() const { return m_Meshes; }

	private:
		void ProcessNode(aiNode * node, const aiScene * scene);
		IMesh * ProcessMesh(aiMesh * mesh, const aiScene * scene);
		IMaterial * ProcessMaterial(aiMaterial * material);
		ITexture * ProcessTexture(aiMaterial * material, aiTextureType type);

	private:
		std::string m_Path;

		std::vector<IMesh *> m_Meshes;

		// TODO: material and texture references should be managed by meshrenderer or managers
		//		 not here at least, but just for test now
		std::vector<IMaterial *> m_Materials;
		std::unordered_map<std::string, ITexture *> m_Textures;
	};
}