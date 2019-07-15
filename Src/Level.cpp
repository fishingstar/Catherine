#include <Level.h>
#include <SceneObject.h>
#include <Transform.h>
#include <Light.h>
#include <Camera.h>
#include <MeshFilter.h>
#include <MeshRenderer.h>
#include <glm/glm.hpp>
#include <Material.h>

namespace Catherine
{
	const char * s_testModel = "./res/model/nanosuit/nanosuit.obj";

	bool Level::Initialize()
	{
		// TODO : add objects manually, because of no level config file supported now...

		// camera
		SceneObject * tmp_camera = new SceneObject(this);
		tmp_camera->Initialize();
		m_SceneObjects.push_back(tmp_camera);

		Transform * tmp_cameraTransform = (Transform *)tmp_camera->AddComponent(ComponentKind::Transform);
		tmp_cameraTransform->SetPosition(glm::vec3(6.0f, 15.0f, 6.0f));
		tmp_cameraTransform->SetRotation(glm::vec3(45.0f, -45.0f, 0.0f));

		Camera * tmp_cameraComponent = (Camera *)tmp_camera->AddComponent(ComponentKind::Camera);
		tmp_cameraComponent->SetProjectionMode(ProjectionMode::Persperctive);
		tmp_cameraComponent->SetClearColor(glm::vec3(0.2f, 0.3f, 0.4f));

		
		// directional light
		SceneObject * tmp_dirLight = new SceneObject(this);
		tmp_dirLight->Initialize();
		m_SceneObjects.push_back(tmp_dirLight);

		Transform * tmp_dirTransform = (Transform *)tmp_dirLight->AddComponent(ComponentKind::Transform);
		tmp_dirTransform->SetRotation(glm::vec3(0.3f, -0.3f, -0.6f));

		Light * tmp_dirComponent = (Light *)tmp_dirLight->AddComponent(ComponentKind::Light);
		tmp_dirComponent->SetLightType(LightType::Directional);
		tmp_dirComponent->SetLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		
		// spot light
		SceneObject * tmp_spotLight = new SceneObject(this);
		tmp_spotLight->Initialize();
		m_SceneObjects.push_back(tmp_spotLight);

		Transform * tmp_spotTransform = (Transform *)tmp_spotLight->AddComponent(ComponentKind::Transform);
		tmp_spotTransform->SetPosition(glm::vec3(0.0f, 10.0f, 2.0f));
		tmp_spotTransform->SetRotation(glm::vec3(0.0f, 0.0f, -1.0f));

		Light * tmp_spotComponent = (Light *)tmp_spotLight->AddComponent(ComponentKind::Light);
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
			SceneObject * tmp_pointLight = new SceneObject(this);
			tmp_pointLight->Initialize();
			m_SceneObjects.push_back(tmp_pointLight);

			Transform * tmp_pointTransform = (Transform *)tmp_pointLight->AddComponent(ComponentKind::Transform);
			tmp_pointTransform->SetPosition(tmp_pos[i]);

			Light * tmp_pointComponent = (Light *)tmp_pointLight->AddComponent(ComponentKind::Light);
			tmp_pointComponent->SetLightType(LightType::Point);
			tmp_pointComponent->SetLightColor(tmp_color[i]);
		}


		// visibile object
		SceneObject * tmp_warrior = new SceneObject(this);
		tmp_warrior->Initialize();
		m_SceneObjects.push_back(tmp_warrior);

		Transform * tmp_meshTransform = (Transform *)tmp_warrior->AddComponent(ComponentKind::Transform);
		MeshFilter * tmp_meshFilter = (MeshFilter *)tmp_warrior->AddComponent(ComponentKind::MeshFilter);
		tmp_meshFilter->LoadFromFile(s_testModel);
		MeshRenderer * tmp_meshRenderer = (MeshRenderer *)tmp_warrior->AddComponent(ComponentKind::MeshRenderer);
		IMaterial * tmp_glassMtl = new Material();
		tmp_glassMtl->Initialize("./res/material/nanosuit_glass.mtl");
		tmp_meshRenderer->AddMaterial(tmp_glassMtl);
		IMaterial * tmp_legMtl = new Material();
		tmp_legMtl->Initialize("./res/material/nanosuit_leg.mtl");
		tmp_meshRenderer->AddMaterial(tmp_legMtl);
		IMaterial * tmp_handMtl = new Material();
		tmp_handMtl->Initialize("./res/material/nanosuit_hand.mtl");
		tmp_meshRenderer->AddMaterial(tmp_handMtl);
		IMaterial * tmp_mouseMtl = new Material();
		tmp_mouseMtl->Initialize("./res/material/nanosuit_mouse.mtl");
		tmp_meshRenderer->AddMaterial(tmp_mouseMtl);
		IMaterial * tmp_armMtl = new Material();
		tmp_armMtl->Initialize("./res/material/nanosuit_arm.mtl");
		tmp_meshRenderer->AddMaterial(tmp_armMtl);
		IMaterial * tmp_helmetMtl = new Material();
		tmp_helmetMtl->Initialize("./res/material/nanosuit_helmet.mtl");
		tmp_meshRenderer->AddMaterial(tmp_helmetMtl);
		IMaterial * tmp_bodyMtl = new Material();
		tmp_bodyMtl->Initialize("./res/material/nanosuit_body.mtl");
		tmp_meshRenderer->AddMaterial(tmp_bodyMtl);

		return true;
	}

	void Level::Uninitialize()
	{
		// TODO : component is not destroyed yet
		for (size_t i = 0; i < m_SceneObjects.size(); i++)
		{
			if (m_SceneObjects[i])
			{
				m_SceneObjects[i]->Uninitialize();

				delete m_SceneObjects[i];
				m_SceneObjects[i] = nullptr;
			}
		}
		m_SceneObjects.clear();
	}

	void Level::Update(float deltaTime)
	{
		for (auto i = 0; i < m_SceneObjects.size(); i++)
		{
			m_SceneObjects[i]->Update(deltaTime);
		}
	}

	void Level::Render(WorldContext * context)
	{
		for (size_t i = 0; i < m_SceneObjects.size(); i++)
		{
			SceneObject * tmp_sceneObject = m_SceneObjects[i];
			MeshRenderer * tmp_renderer = (MeshRenderer *)tmp_sceneObject->GetComponent(ComponentKind::MeshRenderer);
			if (tmp_renderer != nullptr)
			{
				tmp_renderer->Render(context);
			}
		}
	}
}