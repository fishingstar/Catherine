#pragma once

#include <vector>

namespace Catherine
{
	class SceneObject;
	class CameraContext;

	class CameraManager
	{
	public:
		CameraManager();
		~CameraManager();

		void Register(SceneObject * obj);
		void Unregister(SceneObject * obj);

		CameraContext * GetCameraContext();

	private:
		CameraContext * m_CameraContext;

		std::vector<SceneObject *> m_Cameras;
	};
}