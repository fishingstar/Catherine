#pragma once

#include <vector>

namespace Catherine
{
	class VertexLayout
	{
	public:
		struct AttributeItem
		{
			unsigned int count;
			unsigned int type;
			bool normalized;
			unsigned int stride;
			unsigned int offset;
		};

	public:
		void AddAttribute(unsigned int count, unsigned int type, bool normalized, unsigned int stride, unsigned int offset);
		void AddAttribute(const AttributeItem & param_Item);

		unsigned int Count() const;
		const AttributeItem & GetItem(int index) const;

	private:
		std::vector<AttributeItem> m_Attibutes;
	};
}