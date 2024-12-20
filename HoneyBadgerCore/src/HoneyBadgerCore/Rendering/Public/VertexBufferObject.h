#pragma once

#include <vector>

#include "HoneyBadgerCore/Rendering/Public/Vertex.h"

namespace HoneyBadger
{
	class VertexBufferObject
	{
	public:
		VertexBufferObject(float* vertices, long long size);
		VertexBufferObject(const std::vector<Vertex>& vertices);
		void Init(float* vertices, long long size);
		void Init(const std::vector<Vertex>& vertices);

		void Bind() const;
		void Delete();

		unsigned int GetId() const { return _id; }

	private:
		unsigned int _id;
	};
}