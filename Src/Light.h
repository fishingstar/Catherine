#pragma once

#include <ILight.h>

namespace Catherine
{
	class Light : public ILight
	{
	public:
		virtual LightType GetLightType() const override;
		virtual void SetLightType(LightType type) override;

		virtual const glm::vec4 & GetLightColor() const override;
		virtual void SetLightColor(const glm::vec4 & color) override;

		virtual float GetIntensity() const override;
		virtual void SetIntensity(float intensity) override;

		virtual const glm::vec3 & GetPosition() const override;
		virtual void SetPosition(const glm::vec3 & pos) override;

		virtual const glm::vec3 & GetRotation() const override;
		virtual void SetRotation(const glm::vec3 & rotation) override;

	private:
		LightType m_LightType = LightType::Directional;

		glm::vec4 m_LightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		float m_Intensity = 1.0f;

		float m_Range = 10.0f;
		// used for spot light
		float m_SpotAngle = 45.0f;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	};
}