#include <VertexLayout.h>

namespace Catherine
{
	void VertexLayout::AddAttribute(unsigned int count, unsigned int type, bool normalized, unsigned int stride, unsigned int offset)
	{
		// TODO : emplace_back
		AttributeItem tmp_item;
		tmp_item.count = count;
		tmp_item.type = type;
		tmp_item.normalized = normalized;
		tmp_item.stride = stride;
		tmp_item.offset = offset;
		AddAttribute(tmp_item);
	}

	void VertexLayout::AddAttribute(const AttributeItem & param_Item)
	{
		m_Attibutes.push_back(param_Item);
	}

	unsigned int VertexLayout::Count() const
	{
		return (unsigned int)m_Attibutes.size();
	}

	const VertexLayout::AttributeItem & VertexLayout::GetItem(int index) const
	{
		return m_Attibutes[index];
	}
}