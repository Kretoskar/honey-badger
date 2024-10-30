#pragma once

#pragma once
#include <vector>

namespace HoneyBadger
{
	class ElementBufferObject
	{
	public:
		ElementBufferObject(unsigned int* indices, long long size);
		ElementBufferObject(const std::vector<unsigned>& indices);
		void Init(const std::vector<unsigned>& indices);
		void Init(unsigned int* indices, long long size);

		void Bind() const;
		void Delete();

		unsigned int GetId() const { return _id; }

	private:
		unsigned int _id;
	};
}