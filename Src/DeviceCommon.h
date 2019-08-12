#pragma once

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
	};
}