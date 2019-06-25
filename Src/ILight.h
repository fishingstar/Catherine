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

		virtual float GetAttenuationConstant() const = 0;
		virtual void SetAttenuationConstant(float value) = 0;

		virtual float GetAttenuationLinear() const = 0;
		virtual void SetAttenuationLinear(float value) = 0;

		virtual float GetAttenuationQuadratic() const = 0;
		virtual void SetAttenuationQuadratic(float value) = 0;

		virtual float GetRange() const = 0;
		virtual void SetRange(float value) = 0;

		virtual float GetSpotAngle() const = 0;
		virtual void SetSpotAngle(float value) = 0;

		virtual const glm::vec3 & GetPosition() const = 0;
		virtual void SetPosition(const glm::vec3 & pos) = 0;

		virtual const glm::vec3 & GetRotation() const = 0;
		virtual void SetRotation(const glm::vec3 & rotation) = 0;
	};
}