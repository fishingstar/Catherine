#include "CameraManager.h"
#include "CameraContext.h"
#include "SceneObject.h"
#include "Transform.h"
#include "Camera.h"
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

	void CameraManager::Register(SceneObject * obj)
	{
		auto iter = std::find(m_Cameras.begin(), m_Cameras.end(), obj);
		if (iter == m_Cameras.end())
		{
			m_Cameras.push_back(obj);
		}
	}

	void CameraManager::Unregister(SceneObject * obj)
	{
		auto iter = std::find(m_Cameras.begin(), m_Cameras.end(), obj);
		if (iter != m_Cameras.end())
		{
			m_Cameras.erase(iter);
		}
	}

	CameraContext * CameraManager::GetCameraContext()
	{
		SceneObject * tmp_object = m_Cameras.size() > 0 ? m_Cameras.front() : nullptr;
		if (tmp_object)
		{
			Transform * tmp_transform = (Transform *)tmp_object->GetComponent(ComponentKind::Transform);
			m_CameraContext->SetPosition(tmp_transform->GetPosition());
			m_CameraContext->SetRotation(tmp_transform->GetRotation());

			Camera * tmp_camera = (Camera *)tmp_object->GetComponent(ComponentKind::Camera);
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