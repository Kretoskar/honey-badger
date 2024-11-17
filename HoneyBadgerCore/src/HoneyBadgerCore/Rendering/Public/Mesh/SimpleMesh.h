#pragma once

#include "HoneyBadgerCore/Rendering/Public/Mesh/Mesh.h"
#include "HoneyBadgerCore/Rendering/Public/Vertex.h"

namespace HoneyBadger
{
	class SimpleMesh : public Mesh
	{
	public:
		SimpleMesh() {};
		// TODO: std::move?
		SimpleMesh(const std::vector<Vertex>& vertices);
		virtual ~SimpleMesh() {}
	};
}