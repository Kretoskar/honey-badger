#pragma once

#include "hbpch.h"

#include "HoneyBadgerCore/Rendering/Public/Vertex.h"
#include "HoneyBadgerCore/Rendering/Public/VertexArrayObject.h"
#include "HoneyBadgerCore/vendor/json.hpp"
#include "HoneyBadgerCore/ResourceHandling/Public/Guid.h"

namespace HoneyBadger
{
	struct Material;

	struct MeshData
	{
		std::string _guid;
		std::vector<Vertex> _vertices;
		std::vector<unsigned> _indices;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(MeshData, _guid, _vertices, _indices)
	};

	class Mesh
	{
	public:
		Mesh() = default;

		Mesh(MeshData meshData)
		{
			_meshData = meshData;
			Init();
		}

		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices);
		virtual ~Mesh();

		void Init();
		void Init(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices);

		void Draw(Material* material);
		const std::string& GetGuid() const { return _meshData._guid; };

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Mesh, _meshData)

	protected:
		MeshData _meshData;
		VertexArrayObject _vao;
	};
}