#include <MeshFilter.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <LogUtility.h>
#include <FileUtility.h>
#include <Mesh.h>
#include <Material.h>
#include <OpenGLTexture.h>

namespace Catherine
{
	void MeshFilter::Update(float deltaTime)
	{
		// do some update logic
	}

	ComponentKind MeshFilter::GetComponentKind() const
	{
		return ComponentKind::MeshFilter;
	}

	void MeshFilter::LoadFromFile(const char * path)
	{
		m_Path = FileUtility::GetDictionary(path);

		Assimp::Importer tmp_importer;

		const aiScene * tmp_scene = tmp_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
		if (tmp_scene == nullptr)
		{
			LogError("Model LoadFromFile Failed");
			return;
		}

		ProcessNode(tmp_scene->mRootNode, tmp_scene);
	}

	void MeshFilter::ProcessNode(aiNode * node, const aiScene * scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh * tmp_src = scene->mMeshes[node->mMeshes[i]];
			IMesh * tmp_dst = ProcessMesh(tmp_src, scene);
			m_Meshes.push_back(tmp_dst);

			aiMaterial * tmp_srcMat = scene->mMaterials[tmp_src->mMaterialIndex];
			IMaterial * tmp_material = ProcessMaterial(tmp_srcMat);
			m_Materials.push_back(tmp_material);
		}

		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			aiNode * tmp_node = node->mChildren[i];
			ProcessNode(tmp_node, scene);
		}
	}

	IMesh * MeshFilter::ProcessMesh(aiMesh * mesh, const aiScene * scene)
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

	IMaterial * MeshFilter::ProcessMaterial(aiMaterial * material)
	{
		IMaterial * tmp_material = new Material();
		tmp_material->Initialize(nullptr);

		ITexture * tmp_diffuse = ProcessTexture(material, aiTextureType_DIFFUSE);
		if (tmp_diffuse)
		{
			tmp_material->SetTexture("diffuse", tmp_diffuse);
		}

		ITexture * tmp_normal = ProcessTexture(material, aiTextureType_NORMALS);
		if (tmp_normal)
		{
			tmp_material->SetTexture("normal", tmp_normal);
		}

		return tmp_material;
	}

	ITexture * MeshFilter::ProcessTexture(aiMaterial * material, aiTextureType type)
	{
		if (material->GetTextureCount(type) == 0)
			return 0;

		aiString tmp_path;
		material->GetTexture(type, 0, &tmp_path);
		std::string tmp_cpath = m_Path + "/" + tmp_path.C_Str();

		ITexture * tmp_texture = nullptr;
		if (m_Textures.find(tmp_cpath) != m_Textures.end())
		{
			tmp_texture = m_Textures[tmp_cpath];
		}
		else
		{
			tmp_texture = new GLTexture();
			tmp_texture->LoadFromFile(tmp_cpath.c_str());
			m_Textures[tmp_cpath] = tmp_texture;
		}

		return tmp_texture;
	}
}