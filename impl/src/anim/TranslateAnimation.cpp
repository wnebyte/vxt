#include "anim/TranslateAnimation.hpp"

using namespace vxt;
using namespace anim;

TranslateAnimation::TranslateAnimation(glm::vec3 *pos, const glm::vec3 &delta)
	: Animation()
	, m_pos(pos)
	, m_origin(*pos)
	, m_delta(delta)
	, m_iterations(0)
{
}

void TranslateAnimation::update(float dt)
{
	if ((isRunning()) && (m_timeLeft > 0.0f)) {
		const float interpolant = ufw::math::clamp(dt / m_timeLeft, 0.0f, 1.0f);

		// linearly interpolate the size and decrement the animation time
		*m_pos = glm::mix(*m_pos, m_origin + m_delta, interpolant);
		m_timeLeft -= dt;

		// animation time has elapsed
		if (m_timeLeft <= 0.0f) {
			++m_iterations;

			if (((m_iterations - 1) < getRepeatCount()) && (getRepeatMode() != 0)) {
				// reset the animation
				m_timeLeft = getDuration();
				m_origin = *m_pos;
				m_delta = (m_repeatMode == REVERSE) ? -m_delta : m_delta;
			} else {
				// end of the animation
				cancel();
			}
		}
	}
}
