#pragma once

namespace HoneyBadger
{
	class VertexBufferObject;

	class VertexArrayObject
	{

	public:
		VertexArrayObject();

		void LinkAttrib(const VertexBufferObject& vbo, unsigned layout, int numComponents, unsigned type, int stride, void* offset);
		void Bind();
		void Delete();

		unsigned int GetId() const { return _id; }

	private:
		unsigned int _id;
	};
}