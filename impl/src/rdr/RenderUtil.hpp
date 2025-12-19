#ifndef VXT_RENDER_UTIL_HPP
#define VXT_RENDER_UTIL_HPP

#include <initializer_list>

#include "Types.hpp"
#include "rdr/VertexAttribute.hpp"

namespace vxt {
namespace rdr
{
void setVertexAttributes(const std::initializer_list<VertexAttribute> &attrs);
void genIndices(uint32_t *elements, std::size_t size);
} // namespace rdr
} // namespace vxt

#endif // VXT_RENDER_UTIL_HPP
