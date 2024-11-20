#include "hbpch.h"
#include "HoneyBadgerCore/Rendering/Public/Mesh/Mesh.h"
#include <glad/glad.h>


#include "HoneyBadgerCore/Rendering/Public/Material.h"
#include "HoneyBadgerCore/Rendering/Public/VertexBufferObject.h"
#include "HoneyBadgerCore/Rendering/Public/ElementBufferObject.h"


HoneyBadger::Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices)
{
	Init(vertices, indices);
}

HoneyBadger::Mesh::~Mesh()
{
	_vao.Delete();
}

void HoneyBadger::Mesh::Init()
{
	Init(_vertices, _indices);
}

void HoneyBadger::Mesh::Init(const std::vector<Vertex>& vertices, const std::vector<unsigned>& indices)
{
	_vertices = vertices;
	_indices = indices;

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

void HoneyBadger::Mesh::Draw(Material* material)
{
	material->Bind();
	_vao.Bind();

	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
}