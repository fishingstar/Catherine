#pragma once

#include <IModel.h>
#include <assimp/scene.h>
#include <string>
#include <vector>
#include <unordered_map>

namespace Catherine
{
	class IMesh;
	class IMaterial;
	class ITexture;

	class Model : public IModel
	{
	public:
		virtual void LoadFromFile(const char * path) override;
		virtual void Render(WorldContext * context) override;

	private:
		void ProcessNode(aiNode * node, const aiScene * scene);
		IMesh * ProcessMesh(aiMesh * mesh, const aiScene * scene);
		IMaterial * ProcessMaterial(aiMaterial * material);
		ITexture * ProcessTexture(aiMaterial * material, aiTextureType type);

	private:
		std::string m_Path;

		std::vector<IMesh *> m_Meshes;
		std::vector<IMaterial *> m_Materials;
		std::unordered_map<std::string, ITexture *> m_Textures;
	};
}