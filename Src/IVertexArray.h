#pragma once

namespace Catherine
{
	class IVertexArray
	{
	public:
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
	};
}