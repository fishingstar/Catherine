#pragma once

#include <stdint.h>

namespace Catherine
{
	enum class FrontFaceMode
	{
		Clockwise,
		CounterClockwise
	};

	enum class CullFaceMode
	{
		Back,
		Front,
		Both
	};

	enum class CompareMode
	{
		LessEqual,
		Less,
		GreaterEqual,
		Greater,
		Equal,
		NotEqual,
		Always,
		Never
	};

	using DepthTestMode = CompareMode;

	enum class BlendFunc
	{
		Zero,
		One,
		Src_Color,
		One_Minus_Src_Color,
		Dst_Color,
		One_Minus_Dst_Color,
		Src_Alpha,
		One_Minus_Src_Alpha,
		Dst_Alpha,
		One_Minus_Dst_Alpha,
		Constant_Color,
		One_Minus_Constant_Color,
		Constant_Alpha,
		One_Minus_Constant_Alpha
	};

	enum class Equation
	{
		Add,
		Subtract,
		Reverse_Subtract
	};

	using BlendEquation = Equation;

	enum class ValueType
	{
		Float,
		Int,
		UInt,
		UInt_24_8,
		Byte,
		UByte,
		Vec2f,
		Vec3f,
		Vec4f,
		Vec2i,
		Vec3i,
		Vec4i,
		Mat2,
		Mat3,
		Mat4,
	};

	enum class DrawMode
	{
		TRIANGLES,
	};

	enum class Usage
	{
		Static_Draw,
		Stream_Draw,
		Dynamic_Draw,
	};

	// TODO : fill enum...
	enum class PixelFormat
	{
		A8R8G8B8,
		R8G8B8,
		RGBA32F,
		Depth_Component,
		Depth_Component16,
		Depth_Component24,
		Depth_Component32,
		Stencil_Index,
		Stencil_Index8,
		Depth_Stencil,
		Depth24_Stencil8,
	};

	enum class SamplerState
	{
		MinFilter,
		MagFilter,
		MipFilter,
		LODBias,
		AddressU,
		AddressV,
		AddressW,
		Anisotropy,
		BorderColor,
		Count
	};

	enum class Filter
	{
		Nearest,
		Linear,
		Nearest_Mipmap_Nearest,
		Linear_Mipmap_Nearest,
		Nearest_Mipmap_Linear,
		Linear_Mipmap_Linear,
	};

	enum class WrapMode
	{
		Clamp_To_Border,
		Clamp_To_Edge,
		Mirrored_Repeat,
		Mirror_Clamp_To_Edge,
		Repeat,
	};

	enum class BufferBit
	{
		Color = 1,
		Depth = 2,
		Stencil = 4,
		Color_Depth = 3,
		Color_Stencil = 5,
		Depth_Stencil = 6,
		All = 7,
	};

	typedef uint32_t BitField;

	enum class RenderTargetUsage
	{
		Default,
		Read,
		Draw
	};
}