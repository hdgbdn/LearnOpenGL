#ifndef _VAO_H_
#define _VAO_H_
#include <vector>

namespace hdgbdn
{
	class VAO
	{
	public:
		VAO(std::initializer_list<int>);
		VAO(const VAO&);
		VAO(VAO&&);
		VAO& operator=(const VAO&) = delete;
		VAO& operator=(VAO&&) = delete;
		~VAO();
		static void SetAttrPointer(const VAO&);
		static void Bind(const VAO&);
		static void UnBind();
	private:
		unsigned int id;
		std::vector<int> attribStride;
	};
}

#endif