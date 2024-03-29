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

	std::vector<std::pair<BlendFunc, GLenum>> OpenGLBlendMode =
	{
		{ BlendFunc::Zero,						GL_ZERO },
		{ BlendFunc::One,						GL_ONE },
		{ BlendFunc::Src_Color,					GL_SRC_COLOR },
		{ BlendFunc::One_Minus_Src_Color,		GL_ONE_MINUS_SRC_COLOR },
		{ BlendFunc::Dst_Color,					GL_DST_COLOR },
		{ BlendFunc::One_Minus_Dst_Color,		GL_ONE_MINUS_DST_COLOR },
		{ BlendFunc::Src_Alpha,					GL_SRC_ALPHA },
		{ BlendFunc::One_Minus_Src_Alpha,		GL_ONE_MINUS_SRC_ALPHA },
		{ BlendFunc::Dst_Alpha,					GL_DST_ALPHA },
		{ BlendFunc::One_Minus_Dst_Alpha,		GL_ONE_MINUS_DST_ALPHA },
		{ BlendFunc::Constant_Color,			GL_CONSTANT_COLOR },
		{ BlendFunc::One_Minus_Constant_Color,	GL_ONE_MINUS_CONSTANT_COLOR },
		{ BlendFunc::Constant_Alpha,			GL_CONSTANT_ALPHA },
		{ BlendFunc::One_Minus_Constant_Alpha,	GL_ONE_MINUS_CONSTANT_ALPHA },
	};

	std::vector<std::pair<Equation, GLenum>> OpenGLEquation =
	{
		{ Equation::Add,				GL_FUNC_ADD },
		{ Equation::Subtract,			GL_FUNC_SUBTRACT },
		{ Equation::Reverse_Subtract,	GL_FUNC_REVERSE_SUBTRACT }
	};

	std::vector<std::pair<ValueType, GLenum>> OpenGLValueType =
	{
		{ ValueType::Float,	GL_FLOAT },
		{ ValueType::Int,	GL_INT },
		{ ValueType::UInt,	GL_UNSIGNED_INT },
		{ ValueType::UInt_24_8, GL_UNSIGNED_INT_24_8 },
		{ ValueType::Byte,	GL_BYTE },
		{ ValueType::UByte,	GL_UNSIGNED_BYTE },
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
		{ PixelFormat::A8R8G8B8,			GL_RGBA },
		{ PixelFormat::R8G8B8,				GL_RGB },
		{ PixelFormat::RGBA32F,				GL_RGBA32F},
		{ PixelFormat::Depth_Component,		GL_DEPTH_COMPONENT },
		{ PixelFormat::Depth_Component16,	GL_DEPTH_COMPONENT16 },
		{ PixelFormat::Depth_Component24,	GL_DEPTH_COMPONENT24 },
		{ PixelFormat::Depth_Component32,	GL_DEPTH_COMPONENT32 },
		{ PixelFormat::Stencil_Index,		GL_STENCIL_INDEX },
		{ PixelFormat::Stencil_Index8,		GL_STENCIL_INDEX8 },
		{ PixelFormat::Depth_Stencil,		GL_DEPTH_STENCIL },
		{ PixelFormat::Depth24_Stencil8,	GL_DEPTH24_STENCIL8 },
	};

	std::vector<std::pair<SamplerState, GLenum>> OpenGLSamplerState =
	{
		{ SamplerState::MinFilter, GL_TEXTURE_MIN_FILTER },
		{ SamplerState::MagFilter, GL_TEXTURE_MAG_FILTER },
		{ SamplerState::LODBias, GL_TEXTURE_LOD_BIAS },
		{ SamplerState::AddressU, GL_TEXTURE_WRAP_S },
		{ SamplerState::AddressV, GL_TEXTURE_WRAP_T },
		{ SamplerState::AddressW, GL_TEXTURE_WRAP_R },
		{ SamplerState::Anisotropy, GL_TEXTURE_MAX_ANISOTROPY },
		{ SamplerState::BorderColor, GL_TEXTURE_BORDER_COLOR },
	};

	std::vector<std::pair<Filter, GLenum>> OpenGLFilter = 
	{
		{ Filter::Nearest, GL_NEAREST },
		{ Filter::Linear, GL_LINEAR },
		{ Filter::Nearest_Mipmap_Nearest, GL_NEAREST_MIPMAP_NEAREST },
		{ Filter::Linear_Mipmap_Nearest, GL_LINEAR_MIPMAP_NEAREST },
		{ Filter::Nearest_Mipmap_Linear, GL_NEAREST_MIPMAP_LINEAR },
		{ Filter::Linear_Mipmap_Linear, GL_LINEAR_MIPMAP_LINEAR }
	};

	std::vector<std::pair<WrapMode, GLenum>> OpenGLWrapMode =
	{
		{ WrapMode::Clamp_To_Border, GL_CLAMP_TO_BORDER },
		{ WrapMode::Clamp_To_Edge, GL_CLAMP_TO_EDGE },
		{ WrapMode::Mirrored_Repeat, GL_MIRRORED_REPEAT },
		{ WrapMode::Mirror_Clamp_To_Edge, GL_MIRROR_CLAMP_TO_EDGE },
		{ WrapMode::Repeat, GL_REPEAT }
	};

	std::vector<std::pair<BufferBit, GLenum>> OpenGLBufferBit = 
	{
		{ BufferBit::Color, GL_COLOR_BUFFER_BIT },
		{ BufferBit::Depth, GL_DEPTH_BUFFER_BIT },
		{ BufferBit::Stencil, GL_STENCIL_BUFFER_BIT },
		{ BufferBit::Color_Depth, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT },
		{ BufferBit::Color_Stencil, GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT },
		{ BufferBit::Depth_Stencil, GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT },
		{ BufferBit::All, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT }
	};

	std::vector<std::pair<RenderTargetUsage, GLenum>> OpenGLRenderTargetUsage = 
	{
		{ RenderTargetUsage::Default, GL_FRAMEBUFFER },
		{ RenderTargetUsage::Read, GL_READ_FRAMEBUFFER },
		{ RenderTargetUsage::Draw, GL_DRAW_FRAMEBUFFER }
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

	GLenum OpenGLCommon::GetOpenGLBlendFunc(BlendFunc func)
	{
		return GetOpenGLDefines(OpenGLBlendMode, func);
	}

	GLenum OpenGLCommon::GetOpenGLBlendEquation(BlendEquation equation)
	{
		return GetOpenGLDefines(OpenGLEquation, equation);
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

	GLenum OpenGLCommon::GetOpenGLSamplerState(SamplerState state)
	{
		return GetOpenGLDefines(OpenGLSamplerState, state);
	}

	GLenum OpenGLCommon::GetOpenGLFilter(Filter filter)
	{
		return GetOpenGLDefines(OpenGLFilter, filter);
	}

	GLenum OpenGLCommon::GetOpenGLWrapMode(WrapMode mode)
	{
		return GetOpenGLDefines(OpenGLWrapMode, mode);
	}

	GLenum OpenGLCommon::GetOpenGLBufferBit(BufferBit bit)
	{
		return GetOpenGLDefines(OpenGLBufferBit, bit);
	}

	GLbitfield OpenGLCommon::GetOpenGLBufferBits(BitField bits)
	{
		GLbitfield tmp_bits = GL_NONE;
		tmp_bits |= bits & (BitField)BufferBit::Color ? GetOpenGLBufferBit(BufferBit::Color) : GL_NONE;
		tmp_bits |= bits & (BitField)BufferBit::Depth ? GetOpenGLBufferBit(BufferBit::Depth) : GL_NONE;
		tmp_bits |= bits & (BitField)BufferBit::Stencil ? GetOpenGLBufferBit(BufferBit::Depth) : GL_NONE;
		return tmp_bits;
	}

	GLenum OpenGLCommon::GetOpenGLRenderTargetUsage(RenderTargetUsage usage)
	{
		return GetOpenGLDefines(OpenGLRenderTargetUsage, usage);
	}
}