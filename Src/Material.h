#pragma once

#include <IMaterial.h>
#include <DeviceCommon.h>

namespace Catherine
{
	class IProgram;
	class ITexture;

	class Material : public IMaterial
	{
	public:
		virtual bool Initialize(const char * param_Config);

		virtual void SetMat4x4(const char * key, const glm::mat4x4 & value);

		virtual void Use();

	private:
		bool m_DepthTestEnabled = true;
		DepthTestMode m_DepthTestMode = DepthTestMode::LessEqual;

		bool m_CullFaceEnabled = true;
		CullFaceMode m_CullFaceMode = CullFaceMode::Back;

		IProgram * m_Program = nullptr;

		ITexture * m_Texture1 = nullptr;
		ITexture * m_Texture2 = nullptr;
	};
}