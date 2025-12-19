#ifndef VXT_TRANSFORM_HPP
#define VXT_TRANSFORM_HPP

#include "Types.hpp"
#include "ecs/Component.hpp"

namespace vxt {
namespace cmp
{
struct Transform : public ecs::Component {
	bool operator==(const Transform &rhs) const;
	bool operator!=(const Transform &rhs) const;

	glm::mat4 toMat4(void) const;

	glm::vec3 pos;
	glm::vec3 scale;
	float rotation;
};
} // namespace cmp
} // namespace vxt

#endif // VXT_TRANSFORM_HPP
