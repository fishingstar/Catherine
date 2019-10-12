#pragma once

enum class RenderPipeline
{
	Forward,
	Deferred,
	TiledBasedDeferred,
	ClusterBasedDeferred,
	ForwardPlus
};

const RenderPipeline g_RenderPipeline = RenderPipeline::TiledBasedDeferred;