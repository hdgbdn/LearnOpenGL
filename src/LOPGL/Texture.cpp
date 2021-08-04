#include <iostream>
#include <filesystem>
#include "glad/glad.h"
#include "stb_image.h"
#include "Texture.h"

using namespace hdgbdn;
using namespace std;

Texture::Texture(string path, bool flip, int wrapping, int filtering, TextureType type) :
	path(path), texture_id(0), width(0), height(0), nrComponents(0), texType(type),
	pData()
{
	glGenTextures(1, &texture_id);
	stbi_set_flip_vertically_on_load(flip);
	pData = shared_ptr<stbi_uc>(stbi_load(path.c_str(), &width, &height, &nrComponents, 0), ([&](stbi_uc* data)
		{
			stbi_image_free(data);
			if (texture_id != 0) glDeleteTextures(1, &texture_id);
		}));
	if (pData.get())
	{
		GLenum internalFormat;
		GLenum dataFormat;
		if (nrComponents == 1)
		{
			internalFormat = dataFormat = GL_RED;
		}
		else if (nrComponents == 3)
		{
			internalFormat = GL_RGB;
			dataFormat = GL_RGB;
		}
		else if (nrComponents == 4)
		{
			internalFormat = GL_RGBA;
			dataFormat = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, pData.get());
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
	}
	else
	{
		texture_id = 0;
		std::cout << "Texture failed to load at path: " << path << std::endl;
	}
}

void Texture::setType(TextureType type)
{
	texType = type;
}

TextureType Texture::getType() const
{
	return texType;
}

std::string Texture::getPath() const
{
	return path;
}


Texture::operator unsigned int()
{
	return texture_id;
}

Texture::operator unsigned int() const
{
	return texture_id;
}

void Texture::BindToUnit(const Texture& tex, int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, tex);
}