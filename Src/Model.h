#pragma once

#include <IModel.h>
#include <assimp/scene.h>
#include <vector>

namespace Catherine
{
	class IMesh;
	class IMaterial;
	class ITexture;

	class Model : public IModel
	{
	public:
		virtual void LoadFromFile(const char * path) override;
		virtual void Render() override;

	private:
		void ProcessNode(aiNode * node, const aiScene * scene);
		IMesh * ProcessMesh(aiMesh * mesh);
		IMaterial * ProcessMaterial(aiMaterial * material);
		ITexture * ProcessTexture(aiTexture * texture);

	private:
		std::vector<IMesh *> m_Meshes;
		std::vector<IMaterial *> m_Materials;
		std::vector<ITexture *> m_Textures;
	};
}