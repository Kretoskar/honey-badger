#pragma once

#include "hbpch.h"

#include "HoneyBadgerCore/Rendering/Public/Vertex.h"
#include "HoneyBadgerCore/Rendering/Public/VertexArrayObject.h"

namespace HoneyBadger
{
	class Material;

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

	protected:
		std::vector<Vertex> _vertices;
		std::vector<unsigned> _indices;
		Material* _material;
		VertexArrayObject _vao;
	};
}