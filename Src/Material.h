#pragma once

#include "IMaterial.h"
#include "DeviceCommon.h"
#include <vector>

namespace Catherine
{
	class IProgram;
	class ITexture;

	class Material : public IMaterial
	{
	public:
		virtual bool Initialize(const char * param_Config) override;

		virtual void SetInt(const char * key, int value) override;
		virtual void SetFloat(const char * key, float value) override;
		virtual void SetVec2(const char * key, const glm::vec2 & value) override;
		virtual void SetVec3(const char * key, const glm::vec3 & value) override;
		virtual void SetVec4(const char * key, const glm::vec4 & value) override;
		virtual void SetMat4x4(const char * key, const glm::mat4x4 & value) override;
		virtual void SetTexture(const char * key, ITexture * value) override;

		virtual void SetCommonUniform(const WorldContext * context) override;

		virtual float GetRenderPriority() const override;

		virtual void Use() override;

	private:
		IProgram * m_Program = nullptr;

		unsigned int m_Slot = 0;
		std::vector<std::pair<unsigned int, ITexture *>> m_Textures;

		bool m_DepthTestEnabled = true;
		DepthTestMode m_DepthTestMode = DepthTestMode::LessEqual;

		bool m_CullFaceEnabled = true;
		CullFaceMode m_CullFaceMode = CullFaceMode::Back;

		bool m_BlendEnabled = false;
		BlendFunc m_SrcFunc = BlendFunc::Src_Alpha;
		BlendFunc m_DstFunc = BlendFunc::One_Minus_Src_Alpha;
		BlendFunc m_SrcAlphaFunc = BlendFunc::Src_Alpha;
		BlendFunc m_DstAlphaFunc = BlendFunc::One_Minus_Src_Alpha;
		BlendEquation m_BlendEquation = BlendEquation::Add;
		// TODO : blend constant color
		// glm::vec4 m_BlendColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		float m_RenderPriority = 2000.0f;
	};
}