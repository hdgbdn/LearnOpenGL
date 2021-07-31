#ifndef HDGBDN_LIGHT_H
#define HDGBDN_LIGHT_H

#include "glm/glm.hpp"
#include "VAO.h"
#include "VBO.h"

namespace hdgbdn
{
	class Light
	{
	public:
		Light(const glm::vec3& pos, const glm::vec3& col): position(pos), color(col) {}
		Light(const Light& rhs): position(rhs.position), color(rhs.color) {}
		Light& operator=(const Light& rhs)
		{
			position = rhs.position;
			color = rhs.color;
		}
		glm::vec3 getPosition() const
		{
			return position;
		}

		glm::vec3 getColor() const
		{
			return color;
		}

		glm::vec3* getPositionRaw()
		{
			return &position;
		}
		glm::vec3* getColorRaw()
		{
			return &color;
		}
		virtual ~Light() = 0;
	private:
		glm::vec3 position;
		glm::vec3 color;
	};
	inline Light::~Light() {}

	class DirectionalLight: public Light
	{
	public:
		DirectionalLight(const glm::vec3& pos = glm::vec3(1.f, 1.f, 1.f), const glm::vec3& col = glm::vec3(1.f, 1.f, 1.f), const glm::vec3& dir = glm::vec3(1.f, 1.f, 1.f)): Light(pos, col), direction(dir) {}
		DirectionalLight(const DirectionalLight& rhs) = default;
		DirectionalLight& operator=(const DirectionalLight&) = default;
		glm::vec3 getDirection() const
		{
			return direction;
		}
		glm::vec3* getDirectionRaw()
		{
			return &direction;
		}
	private:
		glm::vec3 direction;
	};
}

#endif