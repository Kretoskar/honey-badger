#include "hbpch.h"
#include "HoneyBadgerCore/ResourceHandling/Public/File.h"

#include <fstream>
#include <iostream>

namespace HoneyBadger
{
	File::File(const char* path)
	{
		std::ifstream file(path);

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
}