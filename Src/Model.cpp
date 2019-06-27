#include <Model.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <LogUtility.h>
#include <Mesh.h>

namespace Catherine
{
	void Model::LoadFromFile(const char * path)
	{
		Assimp::Importer tmp_importer;

		const aiScene * tmp_scene = tmp_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
		if (tmp_scene == nullptr)
		{
			LogError("Model LoadFromFile Failed");
			return;
		}

		ProcessNode(tmp_scene->mRootNode, tmp_scene);
	}

	void Model::ProcessNode(aiNode * node, const aiScene * scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh * tmp_src = scene->mMeshes[node->mMeshes[i]];
			IMesh * tmp_dst = ProcessMesh(tmp_src);
			m_Meshes.push_back(tmp_dst);
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			aiNode * tmp_node = node->mChildren[i];
			ProcessNode(tmp_node, scene);
		}
	}

	IMesh * Model::ProcessMesh(aiMesh * mesh)
	{
		std::vector<Vertex> tmp_vertexArray;
		std::vector<unsigned int> tmp_indexArray;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex tmp_vertex;

			if (mesh->HasPositions())
			{
				tmp_vertex.Position.x = mesh->mVertices[i].x;
				tmp_vertex.Position.y = mesh->mVertices[i].y;
				tmp_vertex.Position.z = mesh->mVertices[i].z;
			}
			
			if (mesh->HasNormals())
			{
				tmp_vertex.Normal.x = mesh->mNormals[i].x;
				tmp_vertex.Normal.y = mesh->mNormals[i].y;
				tmp_vertex.Normal.z = mesh->mNormals[i].z;
			}
			
			if (mesh->HasTextureCoords(0))
			{
				tmp_vertex.Texcoord.x = mesh->mTextureCoords[0][i].x;
				tmp_vertex.Texcoord.y = mesh->mTextureCoords[0][i].y;
			}

			tmp_vertexArray.push_back(tmp_vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace tmp_face = mesh->mFaces[i];
			for (unsigned int j = 0; j < tmp_face.mNumIndices; j++)
			{
				tmp_indexArray.push_back(tmp_face.mIndices[j]);
			}
		}

		IMesh * tmp_mesh = new Mesh();
		tmp_mesh->Initialize(tmp_vertexArray, tmp_indexArray);

		return tmp_mesh;
	}

	IMaterial * Model::ProcessMaterial(aiMaterial * material)
	{
		return nullptr;
	}

	ITexture * Model::ProcessTexture(aiTexture * texture)
	{
		return nullptr;
	}

	void Model::Render()
	{
		for (size_t i = 0; i < m_Meshes.size(); i++)
		{
			m_Meshes[i]->Render();
		}
	}
}