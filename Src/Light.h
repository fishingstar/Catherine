#pragma once

#include <IComponent.h>
#include <LightContext.h>
#include <glm/glm.hpp>

namespace Catherine
{
	class Light : public IComponent
	{
	public:
		virtual void OnAddComponent(ISceneObject * owner) override;
		virtual void OnRemoveComponent(ISceneObject * owner) override;

		virtual void Update(float deltaTime) override;

		virtual ComponentKind GetComponentKind() const override;

	public:
		LightType GetLightType() const { return m_LightType; }
		void SetLightType(LightType type) { m_LightType = type; }

		const glm::vec4 & GetLightColor() const { return m_LightColor; }
		void SetLightColor(const glm::vec4 & color) { m_LightColor = color; }

		float GetIntensity() const { return m_Intensity; }
		void SetIntensity(float intensity) { m_Intensity = intensity; }

		float GetAttenuationConstant() const { return m_AttenuationConstant; }
		void SetAttenuationConstant(float value) { m_AttenuationConstant = value; }

		float GetAttenuationLinear() const { return m_AttenuationLinear; }
		void SetAttenuationLinear(float value) { m_AttenuationLinear = value; }

		float GetAttenuationQuadratic() const { return m_AttenuationQuadratic; }
		void SetAttenuationQuadratic(float value) { m_AttenuationQuadratic = value; }

		float GetRange() const { return m_Range; }
		void SetRange(float value) { m_Range = value; }

		float GetSpotAngle() const { return m_SpotAngle; }
		void SetSpotAngle(float value) { m_SpotAngle = value; }

	private:
		LightType m_LightType = LightType::Directional;

		// base light color
		glm::vec4 m_LightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		// intensity for all kinds of light
		float m_Intensity = 1.0f;

		// used for point light and spot light
		float m_AttenuationConstant = 1.0f;
		float m_AttenuationLinear = 0.9f;
		float m_AttenuationQuadratic = 0.032f;
		float m_Range = 10.0f;

		// used for spot light
		float m_SpotAngle = 45.0f;
	};
}