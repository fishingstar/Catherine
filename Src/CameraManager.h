#pragma once

#include <vector>

namespace Catherine
{
	class ISceneObject;
	class CameraContext;

	class CameraManager
	{
	public:
		CameraManager();
		~CameraManager();

		void Register(ISceneObject * obj);
		void Unregister(ISceneObject * obj);

		CameraContext * GetCameraContext();

	private:
		CameraContext * m_CameraContext;

		std::vector<ISceneObject *> m_SceneObjects;
	};
}