#pragma once

namespace Catherine
{
	class IRenderTarget;

	class IPostProcess
	{
	public:
		virtual bool Initialize() = 0;
		virtual void Uninitialize() = 0;

		virtual void Process(IRenderTarget * src, IRenderTarget * dst) = 0;
	};
}