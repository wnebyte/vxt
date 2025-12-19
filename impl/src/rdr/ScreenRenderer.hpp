#ifndef VXT_SCREEN_RENDERER_HPP
#define VXT_SCREEN_RENDERER_HPP

#include "Types.hpp"
#include "rdr/Texture.hpp"

namespace vxt {
namespace rdr
{
class ScreenRenderer {
public:
	static void init(void);
	static void render(Texture *screenTexture);
};
} // namespace rdr
} // namespace vxt

#endif // VXT_SCREEN_RENDERER_HPP
