#pragma once

#include "DeviceCommon.h"
#include "glad/glad.h"

namespace Catherine
{
	class OpenGLCommon
	{
	public:
		static GLenum GetOpenGLFrontFaceMode(FrontFaceMode mode);
		static GLenum GetOpenGLCullFaceMode(CullFaceMode mode);
		static GLenum GetOpenGLDepthTestMode(DepthTestMode mode);
		static GLenum GetOpenGLBlendFunc(BlendFunc func);
		static GLenum GetOpenGLBlendEquation(BlendEquation equation);
		static GLenum GetOpenGLType(ValueType type);
		static GLenum GetOpenGLDrawMode(DrawMode mode);
		static GLenum GetOpenGLUsage(Usage mode);
		static GLenum GetOpenGLPixelFormat(PixelFormat format);
		static GLenum GetOpenGLSamplerState(SamplerState state);
		static GLenum GetOpenGLFilter(Filter filter);
		static GLenum GetOpenGLBufferBit(BufferBit bit);
		static GLenum GetOpenGLBufferBits(BitField bits);

	private:
		OpenGLCommon() { }
	};
}