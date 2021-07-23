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
	int cout = 0;
	for (int i = 0; i < vao.attribStride.size(); ++i)
	{
		glVertexAttribPointer(i, vao.attribStride[i], GL_FLOAT, GL_FALSE, vao.attriCount * sizeof(float), (void*)(cout * sizeof(float)));
		glEnableVertexAttribArray(i);
		cout += vao.attribStride[i];
	}
}


VAO::VAO(std::initializer_list<int> stride) : id(0), attriCount(0), attribStride(stride)
{
	glGenVertexArrays(1, &id);
	for (auto count : attribStride)
	{
		attriCount += count;
	}
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &id);
}

