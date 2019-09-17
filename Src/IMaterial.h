#pragma once

#include "glm/glm.hpp"
#include "RenderCommon.h"

namespace Catherine
{
	class ITexture;
	class RenderContext;
	class CameraContext;
	class LightContext;

	class IMaterial
	{
	public:
		virtual bool Initialize(const char * param_Config) = 0;

		virtual void SetInt(const char * key, int value) = 0;
		virtual void SetFloat(const char * key, float value) = 0;
		virtual void SetVec2(const char * key, const glm::vec2 & value) = 0;
		virtual void SetVec3(const char * key, const glm::vec3 & value) = 0;
		virtual void SetVec4(const char * key, const glm::vec4 & value) = 0;
		virtual void SetMat4x4(const char * key, const glm::mat4x4 & value) = 0;
		virtual void SetTexture(const char * key, ITexture * value) = 0;

		virtual void SetModelUniform(const RenderContext * context) = 0;
		virtual void SetCameraUniform(const CameraContext * context) = 0;
		virtual void SetLightUniform(const LightContext * context) = 0;
		virtual void SetShadowUniform(const CameraContext * context) = 0;

		virtual float GetRenderPriority() const = 0;

		virtual bool HasPass(ShaderPass pass) const = 0;
		virtual bool IsForwardInDerferredPath() const = 0;

		virtual void Use(ShaderPass pass) = 0;
	};
}