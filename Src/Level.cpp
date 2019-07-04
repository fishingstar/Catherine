#include <Level.h>
#include <SceneObject.h>
#include <TransformComponent.h>

namespace Catherine
{
	void Level::Initialize()
	{
		// camera
		ISceneObject * tmp_camera = new SceneObject();
		tmp_camera->AddComponent(new TransformComponent());
		m_SceneObjects.push_back(tmp_camera);

		// directional light
		ISceneObject * tmp_dirLight = new SceneObject();
		tmp_dirLight->AddComponent(new TransformComponent());
		m_SceneObjects.push_back(tmp_dirLight);

		// point light
		ISceneObject * tmp_pointLight1 = new SceneObject();
		tmp_pointLight1->AddComponent(new TransformComponent());
		m_SceneObjects.push_back(tmp_pointLight1);

		// point light
		ISceneObject * tmp_pointLight2 = new SceneObject();
		tmp_pointLight2->AddComponent(new TransformComponent());
		m_SceneObjects.push_back(tmp_pointLight2);

		// point light
		ISceneObject * tmp_pointLight3 = new SceneObject();
		tmp_pointLight3->AddComponent(new TransformComponent());
		m_SceneObjects.push_back(tmp_pointLight3);

		// object
		ISceneObject * tmp_object = new SceneObject();
		tmp_object->AddComponent(new TransformComponent());
		m_SceneObjects.push_back(tmp_object);
	}

	void Level::Update(float deltaTime)
	{

	}

	void Level::Render(WorldContext * context)
	{

	}
}