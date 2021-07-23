#ifndef _GLBUFFER_H_
#define _GLBUFFER_H_
#include <vector>

namespace hdgbdn
{
	template<typename T>
	class GLBuffer
	{
	public:
		GLBuffer(const std::vector<T>&);
		GLBuffer(std::initializer_list<T>);
		GLBuffer(const GLBuffer&) = delete;
		GLBuffer& operator=(const GLBuffer&) = delete;
		virtual void BufferData() = 0;
		virtual void Draw() = 0;
		virtual ~GLBuffer();
	protected:
		unsigned int id;
		int count;
		T* data;
		static bool CheckGLADInit();
	};
}

#include "GLBuffer_imp.h"

#endif