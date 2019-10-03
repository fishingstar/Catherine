#include "Level.h"
#include "SceneObject.h"
#include "Transform.h"
#include "Light.h"
#include "Camera.h"
#include "MeshFilter.h"
#include "MeshRenderer.h"
#include "glm/glm.hpp"
#include "Material.h"

namespace Catherine
{
	const char * s_testModel = "./res/model/nanosuit/nanosuit.fbx";
	const char * s_glassMaterial = "./res/model/nanosuit/material/nanosuit_glass.mtl";
	const char * s_legMaterial = "./res/model/nanosuit/material/nanosuit_leg.mtl";
	const char * s_handMaterial = "./res/model/nanosuit/material/nanosuit_hand.mtl";
	const char * s_mouseMaterial = "./res/model/nanosuit/material/nanosuit_mouse.mtl";
	const char * s_armMaterial = "./res/model/nanosuit/material/nanosuit_arm.mtl";
	const char * s_helmetMaterial = "./res/model/nanosuit/material/nanosuit_helmet.mtl";
	const char * s_bodyMaterial = "./res/model/nanosuit/material/nanosuit_body.mtl";

	const char * s_planeModel = "./res/model/buildin/plane.fbx";
	const char * s_planeMaterial = "./res/material/rust_icon.mtl";

	const char * s_skyboxModel = "./res/model/buildin/box.fbx";
	const char * s_skyboxMaterial = "./res/material/skybox.mtl";

	bool Level::Initialize()
	{
		// TODO : add objects manually, because of no level config file supported now...

		// camera
		SceneObject * tmp_camera = new SceneObject(this);
		tmp_camera->Initialize();
		m_SceneObjects.push_back(tmp_camera);

		Transform * tmp_cameraTransform = (Transform *)tmp_camera->AddComponent(ComponentKind::Transform);
		tmp_cameraTransform->SetPosition(glm::vec3(6.0f, 12.0f, 12.0f));
		tmp_cameraTransform->SetRotation(glm::vec3(15.0f, -15.0f, 0.0f));

		Camera * tmp_cameraComponent = (Camera *)tmp_camera->AddComponent(ComponentKind::Camera);
		tmp_cameraComponent->SetProjectionMode(ProjectionMode::Persperctive);
		tmp_cameraComponent->SetNearPlane(0.1f);
		tmp_cameraComponent->SetFarPlane(200.0f);
		tmp_cameraComponent->SetClearColor(glm::vec3(0.2f, 0.3f, 0.4f));

		
		// directional light
		SceneObject * tmp_dirLight = new SceneObject(this);
		tmp_dirLight->Initialize();
		m_SceneObjects.push_back(tmp_dirLight);

		Transform * tmp_dirTransform = (Transform *)tmp_dirLight->AddComponent(ComponentKind::Transform);
		tmp_dirTransform->SetRotation(glm::vec3(45.0f, 45.0f, 0.0f));

		Light * tmp_dirComponent = (Light *)tmp_dirLight->AddComponent(ComponentKind::Light);
		tmp_dirComponent->SetLightType(LightType::Directional);
		tmp_dirComponent->SetLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		
		// spot light
		SceneObject * tmp_spotLight = new SceneObject(this);
		tmp_spotLight->Initialize();
		m_SceneObjects.push_back(tmp_spotLight);

		Transform * tmp_spotTransform = (Transform *)tmp_spotLight->AddComponent(ComponentKind::Transform);
		tmp_spotTransform->SetPosition(glm::vec3(5.0f, 1.0f, -10.0f));
		tmp_spotTransform->SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));

		Light * tmp_spotComponent = (Light *)tmp_spotLight->AddComponent(ComponentKind::Light);
		tmp_spotComponent->SetLightType(LightType::Spot);
		tmp_spotComponent->SetLightColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		tmp_spotComponent->SetIntensity(10.0f);

		
		glm::vec3 tmp_pos[4] = {
			glm::vec3(1.0f, 1.0f, -10.0f),
			glm::vec3(-1.0f, 1.0f, -10.0f),
			glm::vec3(0.0f, 1.0f, -9.0f),
			glm::vec3(0.0f, 1.0f, -11.0f)
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
		tmp_meshRenderer->SetCastShadow(true);
		tmp_meshRenderer->SetReceiveShadow(true);
		IMaterial * tmp_helmetMtl = new Material();
		tmp_helmetMtl->Initialize(s_helmetMaterial);
		tmp_meshRenderer->AddMaterial(tmp_helmetMtl);
		IMaterial * tmp_glassMtl = new Material();
		tmp_glassMtl->Initialize(s_glassMaterial);
		tmp_meshRenderer->AddMaterial(tmp_glassMtl);
		IMaterial * tmp_bodyMtl = new Material();
		tmp_bodyMtl->Initialize(s_bodyMaterial);
		tmp_meshRenderer->AddMaterial(tmp_bodyMtl);
		IMaterial * tmp_armMtl = new Material();
		tmp_armMtl->Initialize(s_armMaterial);
		tmp_meshRenderer->AddMaterial(tmp_armMtl);
		IMaterial * tmp_handMtl = new Material();
		tmp_handMtl->Initialize(s_handMaterial);
		tmp_meshRenderer->AddMaterial(tmp_handMtl);
		IMaterial * tmp_legMtl = new Material();
		tmp_legMtl->Initialize(s_legMaterial);
		tmp_meshRenderer->AddMaterial(tmp_legMtl);


		// plane
		SceneObject * tmp_plane = new SceneObject(this);
		tmp_plane->Initialize();
		m_SceneObjects.push_back(tmp_plane);

		Transform * tmp_planeTransform = (Transform *)tmp_plane->AddComponent(ComponentKind::Transform);
		tmp_planeTransform->SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));
		tmp_planeTransform->SetScale(glm::vec3(40.0f, 1.0f, 40.0f));
		MeshFilter * tmp_planeMeshFilter = (MeshFilter *)tmp_plane->AddComponent(ComponentKind::MeshFilter);
		tmp_planeMeshFilter->LoadFromFile(s_planeModel);
		MeshRenderer * tmp_planeRenderer = (MeshRenderer *)tmp_plane->AddComponent(ComponentKind::MeshRenderer);
		tmp_planeRenderer->SetCastShadow(true);
		tmp_planeRenderer->SetReceiveShadow(true);
		IMaterial * tmp_planeMtl = new Material();
		tmp_planeMtl->Initialize(s_planeMaterial);
		tmp_planeRenderer->AddMaterial(tmp_planeMtl);


		// skybox
		SceneObject * tmp_skybox = new SceneObject(this);
		tmp_skybox->Initialize();
		m_SceneObjects.push_back(tmp_skybox);

		Transform * tmp_skyboxTransform = (Transform *)tmp_skybox->AddComponent(ComponentKind::Transform);
		MeshFilter * tmp_skyboxMeshFilter = (MeshFilter *)tmp_skybox->AddComponent(ComponentKind::MeshFilter);
		tmp_skyboxMeshFilter->LoadFromFile(s_skyboxModel);
		MeshRenderer * tmp_skyboxRenderer = (MeshRenderer *)tmp_skybox->AddComponent(ComponentKind::MeshRenderer);
		tmp_skyboxRenderer->SetCastShadow(false);
		tmp_skyboxRenderer->SetReceiveShadow(false);
		IMaterial * tmp_skyboxMtl = new Material();
		tmp_skyboxMtl->Initialize(s_skyboxMaterial);
		tmp_skyboxRenderer->AddMaterial(tmp_skyboxMtl);

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