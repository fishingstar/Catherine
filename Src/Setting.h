#pragma once

enum class RenderPipeline
{
	Forward,
	Deferred,
	TiledBasedDeferred,
	ForwardPlus
};

const RenderPipeline g_RenderPipeline = RenderPipeline::Forward;