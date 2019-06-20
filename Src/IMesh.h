#pragma once

namespace Catherine
{
	class VertexLayout;

	class IMesh
	{
	public:
		virtual void LoadFromFile(const char * param_Path) = 0;

		virtual const void * GetVertexBuffer(unsigned int & size) const = 0;
		virtual const void * GetIndexBuffer(unsigned int & size) const = 0;
		virtual const VertexLayout * GetVertexLayout() const = 0;

		virtual bool IsElementIndex() const = 0;
	};
}