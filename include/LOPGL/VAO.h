#ifndef _VAO_H_
#define _VAO_H_
#include <vector>

namespace hdgbdn
{
	class VAO
	{
	public:
		VAO(std::initializer_list<int>);
		~VAO();
		static void SetAttrPointer(const VAO&);
		static void Bind(const VAO&);
		static void UnBind();
	private:
		unsigned int id;
		int attriCount;
		std::vector<int> attribStride;
	};
}

#endif