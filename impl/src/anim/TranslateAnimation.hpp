#ifndef VXT_TRANSLATE_ANIMATION_HPP
#define VXT_TRANSLATE_ANIMATION_HPP

#include "Types.hpp"
#include "anim/Animation.hpp"

namespace vxt {
namespace anim
{
class TranslateAnimation : public Animation {
public:
	TranslateAnimation(glm::vec3 *pos, const glm::vec3 &delta);
	~TranslateAnimation() noexcept = default;

public:
	void update(float dt) override;

private:
	glm::vec3 *m_pos;
	glm::vec3  m_origin;
	glm::vec3  m_delta;
	uint64_t   m_iterations;
};
} // namespace anim
} // namespace vxt

#endif // VXT_TRANSLATE_ANIMATION_HPP
