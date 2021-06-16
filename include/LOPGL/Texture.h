#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "stb_image.h"
#include "glad/glad.h"

namespace Hdgbdn
{
	class Texture
	{
	private:
		unsigned int texture_id;
		int width, height, nrComponents;
	public:
		Texture();
		Texture(const char* path, bool flip = true, int wrapping = GL_TEXTURE_WRAP_R, int filtering = GL_LINEAR);
		unsigned int GetID();
	};
}

#endif