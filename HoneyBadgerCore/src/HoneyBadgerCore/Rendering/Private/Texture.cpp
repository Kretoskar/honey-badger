#include "hbpch.h"
#include "stb_image.h"
#include "HoneyBadgerCore/Rendering/Public/Texture.h"

HoneyBadger::Texture::Texture(HBString path, unsigned unit, unsigned format, unsigned pixelType, unsigned texType)
	: _type(texType), _unit(unit)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* _bytes = stbi_load(path.Get(), &_width, &_height, &_numColCh, 0);

	glGenTextures(1, &_id);

	glActiveTexture(GL_TEXTURE0 + _unit);
	glBindTexture(_type, _id);

	glTexParameteri(_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(_type, 0, GL_RGBA, _width, _height, 0, format, pixelType, _bytes);
	glGenerateMipmap(_type);

	stbi_image_free(_bytes);
	glBindTexture(_type, 0);
}

void HoneyBadger::Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + _unit);
	glBindTexture(_type, _id);
}

void HoneyBadger::Texture::Delete()
{
	glDeleteTextures(1, &_id);
}
