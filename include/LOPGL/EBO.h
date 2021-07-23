#ifndef _EBO_H_
#define _EBO_H_

#include "GLBuffer.h"

namespace hdgbdn
{
	class EBO : public GLBuffer<unsigned int>
	{
	public:
		EBO(const std::vector<unsigned int>&);
		EBO(std::initializer_list<unsigned int>);
		virtual void Draw() override;
		void BufferData() override;
	};
}


#endif
