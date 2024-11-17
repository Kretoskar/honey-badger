#pragma once

#include "hbpch.h"
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
		SimpleMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices);
		virtual ~SimpleMesh() {}
	};
}