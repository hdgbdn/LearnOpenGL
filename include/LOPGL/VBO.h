#ifndef _VBO_H_
#define _VBO_H_

#include "GLBuffer.h"

namespace hdgbdn
{
	class VBO: public GLBuffer<float>
	{
	public:
		VBO(const std::vector<float>&, int);
		VBO(std::initializer_list<float>, int);
		void Draw() override;
		void BufferData() override;
	private:
		int elememtCount;
	};
}

#endif
