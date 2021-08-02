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
		Light(const glm::vec3& pos, const glm::vec3& col) :
				position(pos), color(col), ambient(1.f), diffuse(1.f), specular(1.f) {}
		Light(const Light& rhs) = default;
		Light& operator=(const Light& rhs) = default;
		
		glm::vec3 getPosition() const { return position; }
		glm::vec3 getColor() const { return color; }
		float getAmbient() const { return ambient; }
		float getDiffuse() const { return diffuse; }
		float getSpecular() const { return specular; }

		glm::vec3* getPositionRaw() { return &position; }
		glm::vec3* getColorRaw() { return &color; }
		float* getAmbientRaw() { return &ambient; }
		float* getDiffuseRaw() { return &diffuse; }
		float* getSpecularRaw() { return &specular; }
		
		virtual ~Light() = 0;
	private:
		glm::vec3 position;
		glm::vec3 color;
		float ambient;
		float diffuse;
		float specular;
	};
	inline Light::~Light() {}

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(const glm::vec3& pos = glm::vec3(1.f, 1.f, 1.f), const glm::vec3& col = glm::vec3(1.f, 1.f, 1.f), const glm::vec3& dir = glm::vec3(1.f, 1.f, 1.f)) : Light(pos, col), direction(dir) {}
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

	class PointLight : public Light
	{
	public:
		PointLight(const glm::vec3& pos = glm::vec3(1.f, 1.f, 1.f),
			const glm::vec3& col = glm::vec3(1.f, 1.f, 1.f),
			float kc = 1.f, float kl = 0.09f, float kq = 0.032f)
			: Light(pos, col), kConstant(kc), kLinear(kl), kQuadratic(kq) {}
		PointLight(const PointLight&) = default;
		PointLight& operator=(const PointLight&) = default;
		float getKC() const { return kConstant; }
		float getKL() const { return kLinear; }
		float getKQ() const { return kQuadratic; }
		float* getKCraw() { return &kConstant; }
		float* getKLraw() { return &kLinear; }
		float* getKQraw() { return &kQuadratic; }
	private:
		float kConstant;
		float kLinear;
		float kQuadratic;
	};
}

#endif