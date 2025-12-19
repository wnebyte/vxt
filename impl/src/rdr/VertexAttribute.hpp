#ifndef VXT_VERTEX_ATTRIBUTE_HPP
#define VXT_VERTEX_ATTRIBUTE_HPP

#include "Types.hpp"

namespace vxt {
namespace rdr
{
struct VertexAttribute {
    int32_t  size;
    uint32_t type;
    int32_t  stride;
    void    *offset;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_VERTEX_ATTRIBUTE_HPP
