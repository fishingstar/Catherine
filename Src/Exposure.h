#pragma once

#include "IPostProcess.h"

namespace Catherine
{
	class IMaterial;
	class ISampler;
	// temp code
	class IVertexArray;

	class Exposure : public IPostProcess
	{
	public:
		virtual bool Initialize() override;
		virtual void Uninitialize() override;

		virtual void Process(IRenderTarget * src, IRenderTarget * dst) override;

	private:

		IMaterial * m_ExposureMaterial = nullptr;
		ISampler * m_ExposureSampler = nullptr;

		IVertexArray * m_ScreenVertexArray;
	};
}