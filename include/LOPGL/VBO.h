#ifndef _VBO_H_
#define _VBO_H_

#include "GLBuffer.h"

namespace hdgbdn
{
	class VBO: public GLBuffer<float>
	{
	public:
		VBO(const std::vector<float>&);
		VBO(std::initializer_list<float>);
		void Draw() override;
		void BufferData() override;
	};
}

#endif
