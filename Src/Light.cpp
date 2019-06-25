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

	float Light::GetAttenuationConstant() const
	{
		return m_AttenuationConstant;
	}

	void Light::SetAttenuationConstant(float value)
	{
		m_AttenuationConstant = value;
	}

	float Light::GetAttenuationLinear() const
	{
		return m_AttenuationLinear;
	}

	void Light::SetAttenuationLinear(float value)
	{
		m_AttenuationLinear = value;
	}

	float Light::GetAttenuationQuadratic() const
	{
		return m_AttenuationQuadratic;
	}

	void Light::SetAttenuationQuadratic(float value)
	{
		m_AttenuationQuadratic = value;
	}

	float Light::GetRange() const
	{
		return m_Range;
	}

	void Light::SetRange(float value)
	{
		m_Range = value;
	}

	float Light::GetSpotAngle() const
	{
		return m_SpotAngle;
	}

	void Light::SetSpotAngle(float value)
	{
		m_SpotAngle = value;
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