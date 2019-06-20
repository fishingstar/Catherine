#pragma once

#include <Mesh.h>

namespace Catherine
{
	class DemoMesh : public Mesh
	{
	public:
		virtual void LoadFromFile(const char * param_Path) override;
	};
}