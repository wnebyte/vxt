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
			case GL_HALF_FLOAT:
			case GL_FLOAT:
			case GL_FIXED:
			case GL_INT_2_10_10_10_REV:
			case GL_UNSIGNED_INT_2_10_10_10_REV:
			case GL_UNSIGNED_INT_10F_11F_11F_REV:
				glVertexAttribPointer(index, attr.size, attr.type, false, attr.stride, attr.offset);
				break;
			case GL_BYTE:
			case GL_UNSIGNED_BYTE:
			case GL_SHORT:
			case GL_UNSIGNED_SHORT:
			case GL_INT:
			case GL_UNSIGNED_INT:
				glVertexAttribIPointer(index, attr.size, attr.type, attr.stride, attr.offset);
				break;
			case GL_DOUBLE:
				glVertexAttribLPointer(index, attr.size, attr.type, attr.stride, attr.offset);
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
