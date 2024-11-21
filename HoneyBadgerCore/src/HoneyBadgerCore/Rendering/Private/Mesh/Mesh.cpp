#include "hbpch.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/Mesh.h"
#include <glad/glad.h>

#include "HoneyBadgerCore/ResourceHandling/Public/File.h"
#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "HoneyBadgerCore/Rendering/Public/VertexBufferObject.h"
#include "HoneyBadgerCore/Rendering/Public/ElementBufferObject.h"

namespace HoneyBadger
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices)
	{
		Init(vertices, indices);
	}

	Mesh::~Mesh()
	{
		_vao.Delete();
	}

	void Mesh::Init()
	{
		Init(_meshData._vertices, _meshData._indices);
	}

	void Mesh::Init(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices)
	{
		_meshData._vertices = vertices;
		_meshData._indices = indices;

		_vao.Bind();

		const VertexBufferObject vbo = VertexBufferObject(vertices);
		const ElementBufferObject ebo = ElementBufferObject(indices);

		// position
		_vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		//normals
		_vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
		// color
		_vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
		// UV
		_vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
	}

	void Mesh::Draw(Material* material)
	{
		material->Bind();
		_vao.Bind();

		glDrawElements(GL_TRIANGLES, _meshData._indices.size(), GL_UNSIGNED_INT, 0);
	}
}