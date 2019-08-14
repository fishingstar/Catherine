#include "LightManager.h"
#include "LightContext.h"
#include "SceneObject.h"
#include "Transform.h"
#include "Light.h"
#include "LogUtility.h"
#include <algorithm>

namespace Catherine
{
	LightManager::LightManager()
	{
		m_LightContext = new LightContext();
	}

	LightManager::~LightManager()
	{
		if (m_LightContext)
		{
			delete m_LightContext;
		}
	}

	void LightManager::Register(SceneObject * obj)
	{
		auto iter = std::find(m_Lights.begin(), m_Lights.end(), obj);
		if (iter == m_Lights.end())
		{
			m_Lights.push_back(obj);
		}
	}

	void LightManager::Unregister(SceneObject * obj)
	{
		auto iter = std::find(m_Lights.begin(), m_Lights.end(), obj);
		if (iter != m_Lights.end())
		{
			m_Lights.erase(iter);
		}
	}

	LightContext * LightManager::GetLightContext()
	{
		LightContext::DirectionalContext * tmp_dirContext = m_LightContext->GetDirectionContext();
		tmp_dirContext->enabled = false;
		LightContext::SpotContext * tmp_spotContext = m_LightContext->GetSpotContext();
		tmp_spotContext->enabled = false;
		for (unsigned int i = 0; i < LightContext::POINT_LIGHT_COUNT; i++)
		{
			LightContext::PointContext * tmp_pointContext = m_LightContext->GetPointConext(i);
			tmp_pointContext->enabled = false;
		}

		std::vector<SceneObject *> tmp_dirLights = GetDirectionalLights();
		SceneObject * tmp_dirLight = tmp_dirLights.empty() ? nullptr : tmp_dirLights.front();
		if (tmp_dirLight)
		{
			Transform * tmp_dirTransform = (Transform *)tmp_dirLight->GetComponent(ComponentKind::Transform);
			tmp_dirContext->m_Rotation = tmp_dirTransform->GetRotation();

			Light * tmp_dirComponent = (Light *)tmp_dirLight->GetComponent(ComponentKind::Light);
			tmp_dirContext->m_Intensity = tmp_dirComponent->GetIntensity();
			tmp_dirContext->m_LightColor = tmp_dirComponent->GetLightColor();

			tmp_dirContext->enabled = true;
			tmp_dirContext->Apply();
		}

		std::vector<SceneObject *> tmp_spotLights = GetSpotLights();
		SceneObject * tmp_spotLight = tmp_spotLights.empty() ? nullptr : tmp_spotLights.front();
		if (tmp_spotLight)
		{
			Transform * tmp_spotTransform = (Transform *)tmp_spotLight->GetComponent(ComponentKind::Transform);
			tmp_spotContext->m_Position = tmp_spotTransform->GetPosition();
			tmp_spotContext->m_Rotation = tmp_spotTransform->GetRotation();

			Light * tmp_spotComponent = (Light *)tmp_spotLight->GetComponent(ComponentKind::Light);
			tmp_spotContext->m_LightColor = tmp_spotComponent->GetLightColor();
			tmp_spotContext->m_Intensity = tmp_spotComponent->GetIntensity();
			tmp_spotContext->m_AttenuationConstant = tmp_spotComponent->GetAttenuationConstant();
			tmp_spotContext->m_AttenuationLinear = tmp_spotComponent->GetAttenuationLinear();
			tmp_spotContext->m_AttenuationQuadratic = tmp_spotComponent->GetAttenuationQuadratic();
			tmp_spotContext->m_Range = tmp_spotComponent->GetRange();
			tmp_spotContext->m_SpotAngle = tmp_spotComponent->GetSpotAngle();

			tmp_spotContext->enabled = true;
			tmp_spotContext->Apply();
		}

		std::vector<SceneObject *> tmp_pointLights = GetPointLights();
		for (unsigned int i = 0; i < LightContext::POINT_LIGHT_COUNT; i++)
		{
			if (i >= tmp_pointLights.size())
				break;

			SceneObject * tmp_pointLight = tmp_pointLights[i];
			if (tmp_pointLight)
			{
				LightContext::PointContext * tmp_pointContext = m_LightContext->GetPointConext(i);

				Transform * tmp_pointTransform = (Transform *)tmp_pointLight->GetComponent(ComponentKind::Transform);
				tmp_pointContext->m_Position = tmp_pointTransform->GetPosition();

				Light * tmp_pointComponent = (Light *)tmp_pointLight->GetComponent(ComponentKind::Light);
				tmp_pointContext->m_LightColor = tmp_pointComponent->GetLightColor();
				tmp_pointContext->m_Intensity = tmp_pointComponent->GetIntensity();
				tmp_pointContext->m_AttenuationConstant = tmp_pointComponent->GetAttenuationConstant();
				tmp_pointContext->m_AttenuationLinear = tmp_pointComponent->GetAttenuationLinear();
				tmp_pointContext->m_AttenuationQuadratic = tmp_pointComponent->GetAttenuationQuadratic();
				tmp_pointContext->m_Range = tmp_pointComponent->GetRange();

				tmp_pointContext->enabled = true;
				tmp_pointContext->Apply();
			}
		}

		return m_LightContext;
	}

	std::vector<SceneObject *> LightManager::GetDirectionalLights() const
	{
		std::vector<SceneObject *> tmp_lights = GetLightsByType(LightType::Directional);

		// sort by intensity

		return tmp_lights;
	}

	std::vector<SceneObject *> LightManager::GetSpotLights() const
	{
		std::vector<SceneObject *> tmp_lights = GetLightsByType(LightType::Spot);

		// sort by intensity

		return tmp_lights;
	}

	std::vector<SceneObject *> LightManager::GetPointLights() const
	{
		std::vector<SceneObject *> tmp_lights = GetLightsByType(LightType::Point);

		// sort by intensity

		return tmp_lights;
	}

	std::vector<SceneObject *> LightManager::GetLightsByType(LightType type) const
	{
		std::vector<SceneObject *> tmp_lights;

		for (size_t i = 0; i < m_Lights.size(); i++)
		{
			SceneObject * tmp_light = m_Lights[i];
			if (tmp_light == nullptr)
			{
				LogError("light sceneobject is null...");
				continue;
			}

			Light * tmp_component = (Light *)tmp_light->GetComponent(ComponentKind::Light);
			if (tmp_component == nullptr)
			{
				LogError("light component is not exited...");
				continue;
			}

			if (tmp_component->GetLightType() != type)
				continue;

			tmp_lights.push_back(tmp_light);
		}

		return tmp_lights;
	}
}