#pragma once

#include "hbpch.h"

#include "HoneyBadgerCore/Rendering/Public/Vertex.h"
#include "HoneyBadgerCore/Rendering/Public/VertexArrayObject.h"

#include "HoneyBadgerCore/vendor/json.hpp"

namespace HoneyBadger
{
	struct Material;

	class Mesh
	{
	public:
		// 
		Mesh() = default;
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices);
		virtual ~Mesh();

		void Init();
		void Init(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices);

		void Draw(Material* material);

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Mesh, _vertices, _indices)

	protected:
		std::vector<Vertex> _vertices;
		std::vector<unsigned> _indices;
		VertexArrayObject _vao;
	};
}