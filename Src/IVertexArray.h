#pragma once

namespace Catherine
{
	class IVertexArray
	{
	public:
		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void SetVertexCount(size_t count) = 0;
		virtual size_t GetVertexCount() const = 0;

		virtual void SetIndexCount(size_t count) = 0;
		virtual size_t GetIndexCount() const = 0;
	};
}