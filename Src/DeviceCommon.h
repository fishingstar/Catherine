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
}