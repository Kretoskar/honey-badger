#pragma once

#include "hbpch.h"

#include "HoneyBadgerCore/Rendering/Public/Vertex.h"
#include "HoneyBadgerCore/Rendering/Public/VertexArrayObject.h"

#include "HoneyBadgerCore/ResourceHandling/Public/Asset.h"

namespace HoneyBadger
{
	struct Material;

	class Mesh : public Asset
	{
	public:
		Mesh() : Asset() {};
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, Material* material);
		virtual ~Mesh();

		void Init(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices, Material* material);

		void Draw();
		Material* GetMaterial() const { return _material; }

		virtual AssetType GetAssetType() override { return AssetType::Mesh; };

	protected:
		std::vector<Vertex> _vertices;
		std::vector<unsigned> _indices;
		Material* _material;
		VertexArrayObject _vao;
	};
}