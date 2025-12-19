#ifndef VXT_RENDERER_HPP
#define VXT_RENDERER_HPP

#include "Types.hpp"
#include "Camerafwd.hpp"

namespace vxt {
namespace rdr
{
class Renderer {
public:
	virtual ~Renderer() noexcept = default;

public:
	virtual void render(const Camera &camera) = 0;
	virtual void destroy(void) = 0;
	virtual int32_t zIndex(void) const;

	static int32_t compareTo(const Renderer *r1, const Renderer *r2);
};
} // namespace rdr
} // namespace vxt

#endif // VXT_RENDERER_HPP
