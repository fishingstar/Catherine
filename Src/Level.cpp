#include <Level.h>
#include <SceneObject.h>
#include <Transform.h>
#include <Light.h>
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
		m_SceneObjects.push_back(tmp_camera);

		tmp_camera->AddComponent(new Transform());
		Transform * tmp_cameraTransform = (Transform *)tmp_camera->GetComponent(ComponentKind::Transform);
		tmp_cameraTransform->SetPosition(glm::vec3(6.0f, 15.0f, 6.0f));
		tmp_cameraTransform->SetRotation(glm::vec3(45.0f, -45.0f, 0.0f));

		tmp_camera->AddComponent(new Camera());
		Camera * tmp_cameraComponent = (Camera *)tmp_camera->GetComponent(ComponentKind::Camera);
		tmp_cameraComponent->SetProjectionMode(ProjectionMode::Persperctive);
		tmp_cameraComponent->SetClearColor(glm::vec3(0.2f, 0.3f, 0.4f));

		
		// directional light
		ISceneObject * tmp_dirLight = new SceneObject(this);
		m_SceneObjects.push_back(tmp_dirLight);

		tmp_dirLight->AddComponent(new Transform());
		Transform * tmp_dirTransform = (Transform *)tmp_dirLight->GetComponent(ComponentKind::Transform);
		tmp_dirTransform->SetRotation(glm::vec3(0.3f, -0.3f, -0.6f));

		tmp_dirLight->AddComponent(new Light());
		Light * tmp_dirComponent = (Light *)tmp_dirLight->GetComponent(ComponentKind::Light);
		tmp_dirComponent->SetLightType(LightType::Directional);
		tmp_dirComponent->SetLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		
		// spot light
		ISceneObject * tmp_spotLight = new SceneObject(this);
		m_SceneObjects.push_back(tmp_spotLight);

		tmp_spotLight->AddComponent(new Transform());
		Transform * tmp_spotTransform = (Transform *)tmp_spotLight->GetComponent(ComponentKind::Transform);
		tmp_spotTransform->SetPosition(glm::vec3(0.0f, 10.0f, 2.0f));
		tmp_spotTransform->SetRotation(glm::vec3(0.0f, 0.0f, -1.0f));

		tmp_spotLight->AddComponent(new Light());
		Light * tmp_spotComponent = (Light *)tmp_spotLight->GetComponent(ComponentKind::Light);
		tmp_spotComponent->SetLightType(LightType::Spot);
		tmp_spotComponent->SetLightColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		tmp_dirComponent->SetIntensity(10.0f);

		
		glm::vec3 tmp_pos[4] = {
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 0.0f)
		};

		glm::vec4 tmp_color[4] = {
			glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
			glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)
		};

		// point light
		for (unsigned int i = 0; i < 4; i++)
		{
			ISceneObject * tmp_pointLight = new SceneObject(this);
			m_SceneObjects.push_back(tmp_pointLight);

			tmp_pointLight->AddComponent(new Transform());
			Transform * tmp_pointTransform = (Transform *)tmp_pointLight->GetComponent(ComponentKind::Transform);
			tmp_pointTransform->SetPosition(tmp_pos[i]);

			tmp_pointLight->AddComponent(new Light());
			Light * tmp_pointComponent = (Light *)tmp_pointLight->GetComponent(ComponentKind::Light);
			tmp_pointComponent->SetLightType(LightType::Point);
			tmp_pointComponent->SetLightColor(tmp_color[i]);
		}


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