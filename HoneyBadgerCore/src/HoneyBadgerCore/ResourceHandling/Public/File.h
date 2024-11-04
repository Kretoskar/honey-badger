#pragma once

#include <string>

namespace HoneyBadger
{
	class File
	{
	public:
		File(const char* path, bool lookInResFolder = true);
		~File();

		bool IsValid() const { return _isValid; }
		const std::string* const GetFileContents() const { return _fileContents; }

		static std::string GetPathInRes(const char* path) 
		{
			char result[100];

			strcpy(result, "../res/");
			strcat(result, path);

			return std::string(result);
		}

	private:
		bool _isValid = false;
		std::string* _fileContents;
	};
}