#pragma once

#include "glm/glm.hpp"

namespace Catherine
{
	enum class LightType
	{
		Directional,
		Point,
		Spot
	};

	class LightContext
	{
	public:
		struct DirectionalContext
		{
			bool enabled = false;

			// intensity
			float m_Intensity = 1.0f;

			// base light color
			glm::vec4 m_LightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

			// directional light rotation
			glm::vec3 m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		};

		struct SpotContext
		{
			bool enabled = false;

			// intensity
			float m_Intensity = 1.0f;

			// range and attenuation
			float m_AttenuationConstant = 1.0f;
			float m_AttenuationLinear = 0.9f;
			float m_AttenuationQuadratic = 0.032f;
			float m_Range = 10.0f;

			// angle range
			float m_SpotAngle = 45.0f;

			// base light color
			glm::vec4 m_LightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

			// spot light position and rotation
			glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::vec3 m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		};

		struct PointContext
		{
			bool enabled = false;

			// intensity
			float m_Intensity = 1.0f;

			// range and attenuation
			float m_AttenuationConstant = 1.0f;
			float m_AttenuationLinear = 0.9f;
			float m_AttenuationQuadratic = 0.032f;
			float m_Range = 10.0f;

			// base light color
			glm::vec4 m_LightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

			// point light position
			glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		};

		const static unsigned int POINT_LIGHT_COUNT = 4;

	public:
		LightContext();
		~LightContext();

		DirectionalContext * GetDirectionContext() const { return m_DirectionContext; }
		SpotContext * GetSpotContext() const { return m_SpotContext; }
		PointContext * GetPointConext(unsigned int index) const { return index < POINT_LIGHT_COUNT ? m_PointContext[index] : nullptr; }

	private:
		DirectionalContext * m_DirectionContext;
		SpotContext * m_SpotContext;
		PointContext * m_PointContext[POINT_LIGHT_COUNT];
	};
}