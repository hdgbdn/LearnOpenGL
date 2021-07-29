#pragma once
#include "glm/glm.hpp"

namespace hdgbdn
{
	class Color
	{
		friend Color operator*(const Color&, const Color&);
	public:
		Color(const glm::vec3&);
		Color(glm::vec3&&);
		Color(const glm::vec4&);
		Color(glm::vec4&&);
		Color(float, float, float, float a = 1.f);
		float* GetRawPointer();
		glm::vec4 GetRaw() const;
		~Color() = default;
	private:
		glm::vec4 col;
	};
}
