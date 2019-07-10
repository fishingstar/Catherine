#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace Catherine
{
	class WorldContext;

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 Texcoord;
	};

	class IMesh
	{
	public:
		virtual void Initialize(const std::vector<Vertex> & vertex, const std::vector<unsigned int> & index) = 0;
		virtual void Render(WorldContext * context) = 0;
	};
}