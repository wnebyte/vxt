#ifndef VXT_SUBCHUNK_HPP
#define VXT_SUBCHUNK_HPP

#include "Types.hpp"
#include "rdr/VertexBuffer.hpp"

namespace vxt {
namespace rdr
{
struct Subchunk {
	VertexBuffer buffer;
	glm::ivec2 chunkCoords;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_SUBCHUNK_HPP
