#include "VBO.h"
#include <memory>
#include <iostream>
#include "glad/glad.h"

using namespace hdgbdn;

VBO::VBO(const std::vector<float>& vertices) :GLBuffer(vertices) {}

VBO::VBO(std::initializer_list<float> vertices) : GLBuffer(vertices) {}

void VBO::BufferData()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(*data), data, GL_STATIC_DRAW);
}

void VBO::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, count);
}
