#include "hbpch.h"
#include "HoneyBadgerCore/ResourceHandling/Public/File.h"

#include <fstream>
#include <iostream>

namespace HoneyBadger
{
	File::File(const char* path, bool lookInResFolder)
	{
		std::string pathStr = GetPathInRes(path);


		std::ifstream file(pathStr);

		if (file.good())
		{
			_fileContents = new std::string((std::istreambuf_iterator<char>(file)),
				std::istreambuf_iterator<char>());
			_isValid = true;
		}
		else
		{
			_fileContents = new std::string("");
			_isValid = false;
		}
	}

	File::~File()
	{
		delete _fileContents;
	}

	const std::vector<std::string>& File::GetLines()
	{
		if (!_fileContents)
		{
			return {};
		}

		if (_lines.size() == 0)
		{
			std::string line;

			for (size_t i = 0; i < _fileContents->length(); ++i) 
			{
				if (_fileContents->at(i) == '\n') 
				{
					_lines.push_back(line);   // Add the current line to the vector
					line.clear();             // Clear the current line for the next one
				}
				else 
				{
					line += _fileContents->at(i);      // Add character to the current line
				}
			}

			// Add the last line if there's no newline at the end of the string
			if (!line.empty()) 
			{
				_lines.push_back(line);
			}
		}

		return _lines;
	}
}