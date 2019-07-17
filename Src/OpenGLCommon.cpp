#include "OpenGLCommon.h"
#include <vector>
#include <algorithm>

namespace Catherine
{
	std::vector<std::pair<FrontFaceMode, GLenum>> OpenGLFrontFaceMode = 
	{
		{ FrontFaceMode::Clockwise,			GL_CW },
		{ FrontFaceMode::CounterClockwise,	GL_CCW }
	};

	std::vector<std::pair<CullFaceMode, GLenum>> OpenGLCullFaceMode =
	{
		{ CullFaceMode::Back,	GL_BACK },
		{ CullFaceMode::Front,	GL_FRONT },
		{ CullFaceMode::Both,	GL_FRONT_AND_BACK }
	};

	std::vector<std::pair<CompareMode, GLenum>> OpenGLCompareMode =
	{
		{ CompareMode::LessEqual,		GL_LEQUAL },
		{ CompareMode::Less,			GL_LESS },
		{ CompareMode::GreaterEqual,	GL_GEQUAL },
		{ CompareMode::Greater,			GL_GREATER },
		{ CompareMode::Equal,			GL_EQUAL },
		{ CompareMode::NotEqual,		GL_NOTEQUAL },
		{ CompareMode::Always,			GL_ALWAYS },
		{ CompareMode::Never,			GL_NEVER },
	};

	std::vector<std::pair<ValueType, GLenum>> OpenGLValueType =
	{
		{ ValueType::Float,	GL_FLOAT },
		{ ValueType::Int,	GL_INT },
		{ ValueType::UInt,	GL_UNSIGNED_INT },
		{ ValueType::Vec2f, GL_FLOAT_VEC2 },
		{ ValueType::Vec3f, GL_FLOAT_VEC3 },
		{ ValueType::Vec4f, GL_FLOAT_VEC4 },
		{ ValueType::Vec2i, GL_INT_VEC2 },
		{ ValueType::Vec3i, GL_INT_VEC3 },
		{ ValueType::Vec4i, GL_INT_VEC4 },
		{ ValueType::Mat2,	GL_FLOAT_MAT4 },
		{ ValueType::Mat3,	GL_FLOAT_MAT3 },
		{ ValueType::Mat4,	GL_FLOAT_MAT4 },
	};

	std::vector<std::pair<DrawMode, GLenum>> OpenGLDrawMode =
	{
		{ DrawMode::TRIANGLES, GL_TRIANGLES }
	};

	std::vector<std::pair<Usage, GLenum>> OpenGLUsage =
	{
		{ Usage::Static_Draw,	GL_STATIC_DRAW },
		{ Usage::Stream_Draw,	GL_STREAM_DRAW },
		{ Usage::Dynamic_Draw,	GL_DYNAMIC_DRAW }
	};

	std::vector<std::pair<PixelFormat, GLenum>> OpenGLPixelFormat =
	{
		{ PixelFormat::A8R8G8B8,	GL_RGBA },
		{ PixelFormat::R8G8B8,		GL_RGB }
	};

	template<typename type>
	static GLenum GetOpenGLDefines(std::vector<std::pair<type, GLenum>> defines, type key)
	{
		GLenum tmp_result = GL_NONE;

		auto iter = std::find_if(
			defines.begin(),
			defines.end(),
			[key](const std::pair<type, GLenum> & item) { return item.first == key; }
		);

		if (iter != defines.end())
			tmp_result = iter->second;

		return tmp_result;
	}

	GLenum OpenGLCommon::GetOpenGLFrontFaceMode(FrontFaceMode mode)
	{
		return GetOpenGLDefines(OpenGLFrontFaceMode, mode);
	}

	GLenum OpenGLCommon::GetOpenGLCullFaceMode(CullFaceMode mode)
	{
		return GetOpenGLDefines(OpenGLCullFaceMode, mode);
	}

	GLenum OpenGLCommon::GetOpenGLDepthTestMode(DepthTestMode mode)
	{
		return GetOpenGLDefines(OpenGLCompareMode, mode);
	}

	GLenum OpenGLCommon::GetOpenGLType(ValueType type)
	{
		return GetOpenGLDefines(OpenGLValueType, type);
	}

	GLenum OpenGLCommon::GetOpenGLDrawMode(DrawMode mode)
	{
		return GetOpenGLDefines(OpenGLDrawMode, mode);
	}

	GLenum OpenGLCommon::GetOpenGLUsage(Usage mode)
	{
		return GetOpenGLDefines(OpenGLUsage, mode);
	}

	GLenum OpenGLCommon::GetOpenGLPixelFormat(PixelFormat format)
	{
		return GetOpenGLDefines(OpenGLPixelFormat, format);
	}
}