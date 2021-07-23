#include "VAO.h"
#include "glad/glad.h"

using namespace hdgbdn;

void VAO::Bind(const VAO& vao)
{
	glBindVertexArray(vao.id);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
}

void VAO::SetAttrPointer(const VAO& vao)
{
	int count = 0;
	int attriCount = 0;
	for (auto count : vao.attribStride)
	{
		attriCount += count;
	}
	for (int i = 0; i < vao.attribStride.size(); ++i)
	{
		glVertexAttribPointer(i, vao.attribStride[i], GL_FLOAT, GL_FALSE, attriCount * sizeof(float), (void*)(count * sizeof(float)));
		glEnableVertexAttribArray(i);
		count += vao.attribStride[i];
	}
}

VAO::VAO(const VAO& rhs): id(0), attribStride(rhs.attribStride)
{
	glGenVertexArrays(1, &id);
}

VAO::VAO(VAO&& rhs)
{
	id = rhs.id;
	attribStride = std::move(rhs.attribStride);
}

VAO::VAO(std::initializer_list<int> stride) : id(0), attribStride(stride)
{
	glGenVertexArrays(1, &id);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &id);
}

