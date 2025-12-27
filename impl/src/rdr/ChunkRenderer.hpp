#ifndef VXT_CHUNK_RENDERER_HPP
#define VXT_CHUNK_RENDERER_HPP

#include "Types.hpp"
#include "Camera.hpp"

namespace vxt {
namespace rdr
{
class ChunkRenderer {
public:
	static void render(const Camera &camera);
};
} // namespace rdr
} // namespace vxt

#endif // VXT_CHUNK_RENDERER_HPP
