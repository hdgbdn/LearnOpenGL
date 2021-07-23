#include "EBO.h"
#include "glad/glad.h"

using namespace hdgbdn;

EBO::EBO(const std::vector<unsigned int>& vertices) :GLBuffer(vertices) {}

EBO::EBO(std::initializer_list<unsigned int> vertices) : GLBuffer(vertices) {}

void EBO::BufferData()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(*data), data, GL_STATIC_DRAW);
}

void EBO::Draw()
{
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}
