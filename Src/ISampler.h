#pragma once

#include "DeviceCommon.h"

namespace Catherine
{
	class ISampler
	{
	public:
		virtual bool Initialize() = 0;
		virtual void Uninitialize() = 0;

		virtual void SetWrapS(const WrapMode mode) = 0;
		virtual void SetWrapT(const WrapMode mode) = 0;
		virtual void SetWrapR(const WrapMode mode) = 0;
		virtual void SetMinFilter(const Filter filter) = 0;
		virtual void SetMagFilter(const Filter filter) = 0;
		virtual void SetBorderColor(const float * data) = 0;

		virtual void Bind(const uint8_t slot) = 0;
	};
}