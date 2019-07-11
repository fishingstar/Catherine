#include <CameraManager.h>
#include <CameraContext.h>
#include <ISceneObject.h>
#include <Transform.h>
#include <CameraComponent.h>
#include <algorithm>

namespace Catherine
{
	CameraManager::CameraManager()
	{
		m_CameraContext = new CameraContext();
	}

	CameraManager::~CameraManager()
	{
		if (m_CameraContext)
		{
			delete m_CameraContext;
		}
	}

	void CameraManager::Register(ISceneObject * obj)
	{
		auto iter = std::find(m_SceneObjects.begin(), m_SceneObjects.end(), obj);
		if (iter == m_SceneObjects.end())
		{
			m_SceneObjects.push_back(obj);
		}
	}

	void CameraManager::Unregister(ISceneObject * obj)
	{
		auto iter = std::find(m_SceneObjects.begin(), m_SceneObjects.end(), obj);
		if (iter != m_SceneObjects.end())
		{
			m_SceneObjects.erase(iter);
		}
	}

	CameraContext * CameraManager::GetCameraContext()
	{
		ISceneObject * tmp_object = m_SceneObjects.size() > 0 ? m_SceneObjects.front() : nullptr;
		if (tmp_object)
		{
			Transform * tmp_transform = (Transform *)tmp_object->GetComponent(ComponentKind::Transform);
			m_CameraContext->SetPosition(tmp_transform->GetPosition());
			m_CameraContext->SetRotation(tmp_transform->GetRotation());

			CameraComponent * tmp_camera = (CameraComponent *)tmp_object->GetComponent(ComponentKind::Camera);
			m_CameraContext->SetProjectionMode(tmp_camera->GetProjectionMode());
			m_CameraContext->SetNearPlane(tmp_camera->GetNearPlane());
			m_CameraContext->SetFarPlane(tmp_camera->GetFarPlane());
			m_CameraContext->SetAspect(tmp_camera->GetAspect());
			m_CameraContext->SetFOV(tmp_camera->GetFOV());
			m_CameraContext->SetSize(tmp_camera->GetSize());
			m_CameraContext->SetClearColor(tmp_camera->GetClearColor());
		}

		return m_CameraContext;
	}
}