#pragma once

#include <glm/glm.hpp>

namespace Catherine
{
	enum class ProjectionMode
	{
		Ortho,
		Persperctive
	};

	class ICamera
	{
	public:
		virtual ProjectionMode GetProjectionMode() = 0;
		virtual void SetProjectionMode(ProjectionMode param_Mode) = 0;

		virtual float GetNearPlane() const = 0;
		virtual void SetNearPlane(float param_Near) = 0;

		virtual float GetFarPlane() const = 0;
		virtual void SetFarPlane(float param_Far) = 0;

		virtual float GetAspect() const = 0;
		virtual void SetAspect(float param_Aspect) = 0;

		virtual float GetFOV() const = 0;
		virtual void SetFOV(float param_FOV) = 0;

		virtual float GetSize() const = 0;
		virtual void SetSize(float param_Size) = 0;

		virtual void SetPosition(float x, float y, float z) = 0;
		virtual void SetRotate(float x, float y, float z) = 0;

		virtual const glm::mat4x4 & GetViewMatrix() = 0;
		virtual const glm::mat4x4 & GetProjectionMatrix() = 0;
	};
}