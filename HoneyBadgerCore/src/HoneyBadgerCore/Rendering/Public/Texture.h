#pragma once

#include <glad/glad.h>

#include "HoneyBadgerCore/Core/Public/HBString.h"

namespace HoneyBadger
{
	struct TextureData
	{
		std::string guid;
		std::string path;

		
	};

	class Texture
	{
		unsigned _id;
		unsigned _type;
		unsigned _unit;
		int _width, _height, _numColCh;

	public:
		Texture(HBString path, unsigned unit, unsigned format, unsigned pixelType = GL_UNSIGNED_BYTE, unsigned texType = GL_TEXTURE_2D);
		void Bind();
		void Delete();
	};
}