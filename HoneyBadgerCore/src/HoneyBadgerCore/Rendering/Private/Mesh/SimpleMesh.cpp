#include "hbpch.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/SimpleMesh.h"
#include "HoneyBadgerCore/Core/Public/Engine.h"
#include "HoneyBadgerCore/ResourceHandling/Public/AssetsRegistry.h"

HoneyBadger::SimpleMesh::SimpleMesh(const std::vector<Vertex>& vertices)
{
	std::vector<unsigned> indices;
	indices.reserve(vertices.size());

	for (size_t i = 0; i < vertices.size(); ++i)
	{
		indices.push_back(i);
	}


	Init(vertices, indices, Engine::AssetsReg->UnlitColorMaterial.get());
}