#include <Light.h>

namespace Catherine
{
	LightType Light::GetLightType() const
	{
		return m_LightType;
	}

	void Light::SetLightType(LightType type)
	{
		m_LightType = type;
	}

	const glm::vec4 & Light::GetLightColor() const
	{
		return m_LightColor;
	}

	void Light::SetLightColor(const glm::vec4 & color)
	{
		m_LightColor = color;
	}

	float Light::GetIntensity() const
	{
		return m_Intensity;
	}

	void Light::SetIntensity(float intensity)
	{
		m_Intensity = intensity;
	}

	const glm::vec3 & Light::GetPosition() const
	{
		return m_Position;
	}

	void Light::SetPosition(const glm::vec3 & pos)
	{
		m_Position = pos;
	}

	const glm::vec3 & Light::GetRotation() const
	{
		return m_Rotation;
	}

	void Light::SetRotation(const glm::vec3 & rotation)
	{
		m_Rotation = rotation;
	}
}