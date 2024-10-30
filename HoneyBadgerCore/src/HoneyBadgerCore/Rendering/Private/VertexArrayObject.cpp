#include "hbpch.h"

#include "HoneyBadgerCore/Rendering/Public/VertexBufferObject.h"
#include "HoneyBadgerCore/Rendering/Public/VertexArrayObject.h"

#include <glad/glad.h>

namespace HoneyBadger
{
	VertexArrayObject::VertexArrayObject()
	{
		glGenVertexArrays(1, &_id);
	}

	void VertexArrayObject::LinkAttrib(const VertexBufferObject& vbo, unsigned layout, int numComponents, unsigned type, int stride, void* offset)
	{
		vbo.Bind();
		glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);
	}

	void VertexArrayObject::Bind()
	{
		glBindVertexArray(_id);
	}

	void VertexArrayObject::Delete()
	{
		glDeleteVertexArrays(1, &_id);
	}
}