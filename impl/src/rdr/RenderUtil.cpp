#include <glad/glad.h>

#include "rdr/RenderUtil.hpp"

namespace vxt {
namespace rdr
{
void setVertexAttributes(const std::initializer_list<VertexAttribute> &attrs)
{
	uint32_t index = 0;

	for (const VertexAttribute &attr : attrs) {
		switch (attr.type) {
			case GL_FLOAT:
				glVertexAttribPointer(index, attr.size, GL_FLOAT, false, attr.stride, attr.offset);
				break;
			case GL_INT:
				glVertexAttribIPointer(index, attr.size, GL_INT, attr.stride, attr.offset);
				break;
			default:
				break;
		}
		glEnableVertexAttribArray(index);
		++index;
	}
}

void genIndices(uint32_t *elements, std::size_t size)
{
	static const uint32_t indices[6] = {0, 1, 3, 1, 2, 3};

	for (uint32_t i = 0; i < size; ++i) {
		elements[i] = indices[(i % 6)] + ((i / 6) * 4);
	}
}
} // namespace rdr
} // namespace vxt
