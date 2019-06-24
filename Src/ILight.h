#pragma once

#include <glm/glm.hpp>

namespace Catherine
{
	enum class LightType
	{
		Directional,
		Point,
		Spot
	};

	class ILight
	{
	public:
		virtual LightType GetLightType() const = 0;
		virtual void SetLightType(LightType type) = 0;

		virtual const glm::vec4 & GetLightColor() const = 0;
		virtual void SetLightColor(const glm::vec4 & color) = 0;

		virtual float GetIntensity() const = 0;
		virtual void SetIntensity(float intensity) = 0;

		virtual const glm::vec3 & GetPosition() const = 0;
		virtual void SetPosition(const glm::vec3 & pos) = 0;

		virtual const glm::vec3 & GetRotation() const = 0;
		virtual void SetRotation(const glm::vec3 & rotation) = 0;
	};
}