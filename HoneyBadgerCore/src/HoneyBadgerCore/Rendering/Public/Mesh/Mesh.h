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
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, Material* material);
		virtual ~Mesh();

		void Init(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, Material* material);

		void Draw();
		Material* GetMaterial() const { return _material; }

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Mesh, _vertices, _indices)

	protected:
		std::vector<Vertex> _vertices;
		std::vector<unsigned> _indices;
		Material* _material;
		VertexArrayObject _vao;
	};
}