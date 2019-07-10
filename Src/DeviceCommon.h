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

	enum class ValueType
	{
		Float,
		Int,
		Vec2f,
		Vec3f,
		Vec4f,
		Vec2i,
		Vec3i,
		Vec4i,
		Mat2x2,
		Mat3x3,
		Mat4x4,
	};
}