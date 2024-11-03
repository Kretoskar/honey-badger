#pragma once

#include <string>

namespace HoneyBadger
{
	class File
	{
	public:
		File(const char* path);
		~File();

		bool IsValid() const { return _isValid; }
		const std::string* const GetFileContents() const { return _fileContents; }

	private:
		bool _isValid = false;
		std::string* _fileContents;
	};
}