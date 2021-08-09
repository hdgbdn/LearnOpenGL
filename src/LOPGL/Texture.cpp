#include <iostream>
#include <filesystem>
#include "glad/glad.h"
#include "stb_image.h"
#include "Texture.h"

using namespace hdgbdn;
using namespace std;

Texture::Texture(string path, bool flip, int wrapping, int filtering, TextureType type) :
	path(path), pID(), width(0), height(0), nrComponents(0), texType(type)
{
	pID = shared_ptr<unsigned int>(new unsigned int(0), [](unsigned int* id)
		{
			glDeleteTextures(1, id);
		});
	glGenTextures(1, pID.get());
	stbi_set_flip_vertically_on_load(flip);
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);

	if (data == nullptr) std::cout << "Texture failed to load at path: " << path << " creating an empty texture" << std::endl;
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

	glBindTexture(GL_TEXTURE_2D, *pID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
	stbi_image_free(data);
}

Texture::~Texture() {}


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
	return *pID;
}

Texture::operator unsigned int() const
{
	return *pID;
}

unsigned int* Texture::getIDRaw() const
{
	return pID.get();
}


void Texture::BindToUnit(const Texture& tex, int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, tex);
}