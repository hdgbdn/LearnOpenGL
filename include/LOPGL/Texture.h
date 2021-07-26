#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "stb_image.h"
#include "glad/glad.h"
#include <string>
#include <memory>

namespace hdgbdn
{
	class Texture
	{
	public:
		Texture(const Texture&) = delete;
		Texture(Texture&&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture& operator=(Texture&&) = delete;
		Texture(std::string path, bool flip = true, int wrapping = GL_TEXTURE_WRAP_R, int filtering = GL_LINEAR);
		~Texture() = default;
		operator unsigned int();
		operator unsigned int() const;
		static void BindToUnit(const Texture&, int);
	private:
		unsigned int texture_id;
		int width, height, nrComponents;
		std::shared_ptr<stbi_uc> pData;
	};
}

#endif