#include "Color.h"

using namespace hdgbdn;

Color hdgbdn::operator*(const Color& lhs, const Color& rhs)
{
	return Color(lhs.col * rhs.col);
}


hdgbdn::Color::Color(float r, float g, float b, float a): col(r, g, b, a)
{
	
}

Color::Color(const glm::vec3& c): col(c, 1.f)
{
	
}

Color::Color(const glm::vec4& c): col(c)
{
	
}

Color::Color(glm::vec3&& c): col(std::move(glm::vec4(c, 1.f)))
{
	
}

Color::Color(glm::vec4&& c): col(std::move(c))
{
	
}

float* Color::GetRawPointer()
{
	return reinterpret_cast<float*>(&col);
}

glm::vec4 Color::GetRaw() const
{
	return col;
}

