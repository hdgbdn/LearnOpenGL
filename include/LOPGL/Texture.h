#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "stb_image.h"
#include "glad/glad.h"
#include <string>
#include <memory>

namespace hdgbdn
{
	enum TextureType {
		DIFFUSE = 0,
		SPECULAR,
		NORMAL,
		HEIGHT,
	};
	class Texture
	{
	public:
		Texture() = default;
		Texture(const Texture&) = default;
		Texture(Texture&&) = default;
		Texture& operator=(const Texture&) = default;
		Texture& operator=(Texture&&) = default;
		Texture(std::string path, bool flip = true, int wrapping = GL_TEXTURE_WRAP_R, int filtering = GL_LINEAR, TextureType type = TextureType::DIFFUSE);
		~Texture();
		void setType(TextureType);
		TextureType getType() const;
		std::string getPath() const;
		operator unsigned int();
		operator unsigned int() const;
		unsigned int* getIDRaw() const;
		static void BindToUnit(const Texture&, int);
	private:
		std::string path;
		std::shared_ptr<unsigned int> pID;
		TextureType texType;
		int width, height, nrComponents;
	};
}

#endif