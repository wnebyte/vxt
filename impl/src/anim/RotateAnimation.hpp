#ifndef VXT_ROTATE_ANIMATION_HPP
#define VXT_ROTATE_ANIMATION_HPP

#include "Types.hpp"
#include "anim/Animation.hpp"

namespace vxt {
namespace anim
{
class RotateAnimation : public Animation {
public:
	RotateAnimation(float *rotation, const float delta);
	~RotateAnimation() noexcept = default;

public:
	void update(float dt) override;

private:
	float     *m_rotation;
	float      m_origin;
	float      m_delta;
	uint64_t   m_iterations;
};
} // namespace anim
} // namespace vxt

#endif // VXT_ROTATE_ANIMATION_HPP
