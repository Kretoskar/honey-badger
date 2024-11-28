#pragma once

#include <string>
#include "HoneyBadgerCore/Core/Public/HBString.h"

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

		const std::vector<std::string>& GetLines();
		void OverrideContent(const std::string& newContent);

		static std::string GetFileName(const std::string& path);
		static std::string GetFileExtension(const std::string& path);
		static std::string GetFileNameAndExtension(const std::string& path);

	private:
		bool _isValid = false;
		std::string* _fileContents;
		std::string _path;
		std::vector<std::string> _lines;
	};
}