#include <Level.h>
#include <SceneObject.h>
#include <Transform.h>
#include <Camera.h>
#include <MeshFilter.h>
#include <MeshRenderer.h>
#include <glm/glm.hpp>

namespace Catherine
{
	const char * s_testModel = "./res/model/nanosuit/nanosuit.obj";

	void Level::Initialize()
	{
		// TODO : add objects manually, because of no level config file supported now...

		// camera
		ISceneObject * tmp_camera = new SceneObject(this);
		tmp_camera->AddComponent(new Transform());
		tmp_camera->AddComponent(new Camera());

		Transform * tmp_cameraTransform = (Transform *)tmp_camera->GetComponent(ComponentKind::Transform);
		tmp_cameraTransform->SetPosition(glm::vec3(6.0f, 15.0f, 6.0f));
		tmp_cameraTransform->SetRotation(glm::vec3(45.0f, -45.0f, 0.0f));

		Camera * tmp_cameraComponent = (Camera *)tmp_camera->GetComponent(ComponentKind::Camera);
		tmp_cameraComponent->SetProjectionMode(ProjectionMode::Persperctive);
		tmp_cameraComponent->SetClearColor(glm::vec3(0.2f, 0.3f, 0.4f));

		m_SceneObjects.push_back(tmp_camera);


		// directional light
		ISceneObject * tmp_dirLight = new SceneObject(this);
		tmp_dirLight->AddComponent(new Transform());
		m_SceneObjects.push_back(tmp_dirLight);

		// point light
		ISceneObject * tmp_pointLight1 = new SceneObject(this);
		tmp_pointLight1->AddComponent(new Transform());
		m_SceneObjects.push_back(tmp_pointLight1);

		// point light
		ISceneObject * tmp_pointLight2 = new SceneObject(this);
		tmp_pointLight2->AddComponent(new Transform());
		m_SceneObjects.push_back(tmp_pointLight2);

		// point light
		ISceneObject * tmp_pointLight3 = new SceneObject(this);
		tmp_pointLight3->AddComponent(new Transform());
		m_SceneObjects.push_back(tmp_pointLight3);


		// visibile object
		ISceneObject * tmp_warrior = new SceneObject(this);
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