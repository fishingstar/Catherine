#include "TileBasedDeferredPipeline.h"
#include "IDevice.h"
#include "IProgram.h"
#include "DeviceConst.h"

namespace Catherine
{
	extern IDevice * g_Device;

	static const char * s_ComputeShader = "./res/shader/TBDRLight.cs";

	TileBasedDeferredPipeline::~TileBasedDeferredPipeline()
	{

	}

	bool TileBasedDeferredPipeline::Initialize()
	{
		// compute shader
		m_ComputeProgram = g_Device->CreateProgram();
		m_ComputeProgram->AttachComputeShader(s_ComputeShader);
		bool tmp_compileReuslt = m_ComputeProgram->Compile();
		if (!tmp_compileReuslt)
			return false;
		bool tmp_linkResult = m_ComputeProgram->Link();
		if (!tmp_linkResult)
			return false;

		return true;
	}

	void TileBasedDeferredPipeline::Uninitialize()
	{

	}

	void TileBasedDeferredPipeline::Render(const WorldContext * context)
	{
		// 1st geometry pass
		RenderGeometry(context);
		// 2nd compute pass
		ComputeLight(context);
		// 3rd lighting pass
		RenderLighting(context);
	}

	void TileBasedDeferredPipeline::RenderGeometry(const WorldContext * context)
	{

	}

	void TileBasedDeferredPipeline::ComputeLight(const WorldContext * context)
	{
		m_ComputeProgram->Use();
		g_Device->DispatchCompute(DEFAULT_SCREEN_WIDTH / 16, DEFAULT_SCREEN_HEIGHT / 16, 1);
	}

	void TileBasedDeferredPipeline::RenderLighting(const WorldContext * context)
	{

	}
}