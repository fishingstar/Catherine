#pragma once

#include <DeviceCommon.h>
#include <glad/glad.h>

namespace Catherine
{
	class OpenGLCommon
	{
	public:
		static GLenum GetOpenGLFrontFaceMode(FrontFaceMode mode);
		static GLenum GetOpenGLCullFaceMode(CullFaceMode mode);
		static GLenum GetOpenGLDepthTestMode(DepthTestMode mode);
		static GLenum GetOpenGLType(ValueType type);

	private:
		OpenGLCommon() { }
	};
}