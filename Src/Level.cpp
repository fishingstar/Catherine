#include <Level.h>
#include <SceneObject.h>
#include <Transform.h>
#include <MeshFilter.h>
#include <MeshRenderer.h>

namespace Catherine
{
	const char * s_testModel = "./res/model/nanosuit/nanosuit.obj";

	void Level::Initialize()
	{
		// TODO : add objects manually, because of no level config file supported now...

		// camera
		ISceneObject * tmp_camera = new SceneObject();
		tmp_camera->AddComponent(new Transform());
		m_SceneObjects.push_back(tmp_camera);

		// directional light
		ISceneObject * tmp_dirLight = new SceneObject();
		tmp_dirLight->AddComponent(new Transform());
		m_SceneObjects.push_back(tmp_dirLight);

		// point light
		ISceneObject * tmp_pointLight1 = new SceneObject();
		tmp_pointLight1->AddComponent(new Transform());
		m_SceneObjects.push_back(tmp_pointLight1);

		// point light
		ISceneObject * tmp_pointLight2 = new SceneObject();
		tmp_pointLight2->AddComponent(new Transform());
		m_SceneObjects.push_back(tmp_pointLight2);

		// point light
		ISceneObject * tmp_pointLight3 = new SceneObject();
		tmp_pointLight3->AddComponent(new Transform());
		m_SceneObjects.push_back(tmp_pointLight3);

		// object
		ISceneObject * tmp_warrior = new SceneObject();
		tmp_warrior->AddComponent(new Transform());
		tmp_warrior->AddComponent(new MeshFilter());
		tmp_warrior->AddComponent(new MeshRenderer());

		MeshFilter * tmp_meshFilter = (MeshFilter *)tmp_warrior->GetComponent(ComponentKind::MeshFilter);
		tmp_meshFilter->LoadFromFile(s_testModel);

		m_SceneObjects.push_back(tmp_warrior);
	}

	void Level::Update(float deltaTime)
	{

	}

	void Level::Render(WorldContext * context)
	{
		for (size_t i = 0; i < m_SceneObjects.size(); i++)
		{
			ISceneObject * tmp_sceneObject = m_SceneObjects[i];
			MeshRenderer * tmp_renderer = (MeshRenderer *)tmp_sceneObject->GetComponent(ComponentKind::MeshRenderer);
			if (tmp_renderer != nullptr)
			{
				tmp_renderer->Render(context);
			}
		}
	}
}