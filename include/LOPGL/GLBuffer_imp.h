#include <memory>
#include <iostream>
#include "glad/glad.h"

using namespace hdgbdn;

template<typename T>
bool GLBuffer<T>::CheckGLADInit()
{
	if (glBindBuffer == nullptr) return false;
	return true;
}

template<typename T>
GLBuffer<T>::GLBuffer(const std::vector<T>& vertices) : id(), count(vertices.size()), data(nullptr)
{
	if (!CheckGLADInit())
	{
		std::cerr << "ERROR::GLBUFFER: GL function not loaded, can't create Buffer" << std::endl;
	}
	glGenBuffers(1, &id);
	data = new T[vertices.size()];
	std::uninitialized_copy(vertices.begin(), vertices.end(), data);
}

template<typename T>
GLBuffer<T>::GLBuffer(std::initializer_list<T> vertices) : id(), count(vertices.size()), data(nullptr)
{
	if (!CheckGLADInit())
	{
		std::cerr << "ERROR::GLBUFFER: GL function not loaded, can't create Buffer" << std::endl;
	}
	glGenBuffers(1, &id);
	data = new T[count];
	std::uninitialized_copy(vertices.begin(), vertices.end(), data);
}

template<typename T>
GLBuffer<T>::~GLBuffer()
{
	delete data;
	glDeleteBuffers(1, &id);
}