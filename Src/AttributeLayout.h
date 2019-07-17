#pragma once

#include "DeviceCommon.h"

namespace Catherine
{
	class AttributeLayout
	{
	public:
		AttributeLayout(unsigned int index, unsigned int count, ValueType type, bool normalized, unsigned int stride, unsigned int offset) :
			m_Index(index),
			m_Count(count),
			m_ValueType(type),
			m_Normalized(normalized),
			m_Stride(stride),
			m_Offset(offset)
		{

		}

		unsigned int GetIndex() const { return m_Index; }
		unsigned int GetCount() const { return m_Count; }
		ValueType GetValueType() const { return m_ValueType; }
		bool GetNormalized() const { return m_Normalized; }
		unsigned int GetStride() const { return m_Stride; }
		unsigned int GetOffset() const { return m_Offset; }

	private:
		unsigned int m_Index;
		unsigned int m_Count;
		ValueType m_ValueType;
		bool m_Normalized;
		unsigned int m_Stride;
		unsigned int m_Offset;
	};
}