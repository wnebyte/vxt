#ifndef VXT_SKYBOX_HPP
#define VXT_SKYBOX_HPP

#include "Types.hpp"
#include "Camera.hpp"

namespace vxt {
namespace rdr
{
class Skybox {
public:
	static void init(void);
	static void render(const Camera &camera);
};
} // namespace rdr
} // namespace vxt

#endif // VXT_SKYBOX_HPP
