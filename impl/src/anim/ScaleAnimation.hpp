#ifndef VXT_SCALE_ANIMATION_HPP
#define VXT_SCALE_ANIMATION_HPP

#include "Types.hpp"
#include "anim/Animation.hpp"

namespace vxt {
namespace anim
{
class ScaleAnimation : public Animation {
public:
	ScaleAnimation(glm::vec3 *size, const glm::vec3 &delta);
	~ScaleAnimation() noexcept = default;

public:
	void update(float dt) override;

private:
	glm::vec3 *m_size;
	glm::vec3  m_origin;
	glm::vec3  m_delta;
	uint64_t   m_iterations;
};
} // namespace anim
} // namespace vxt

#endif // VXT_SCALE_ANIMATION_HPP
