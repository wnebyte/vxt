#include "anim/ScaleAnimation.hpp"

using namespace vxt;
using namespace anim;

ScaleAnimation::ScaleAnimation(glm::vec3 *size, const glm::vec3 &delta)
	: Animation()
	, m_size(size)
	, m_origin(*size)
	, m_delta(delta)
	, m_iterations(0)
{
}

void ScaleAnimation::update(float dt)
{
	if ((isRunning()) && (m_timeLeft > 0.0f)) {
		const float interpolant = ufw::math::clamp(dt / m_timeLeft, 0.0f, 1.0f);

		// linearly interpolate the size and decrement the animation time
		*m_size = glm::mix(*m_size, m_origin + m_delta, interpolant);
		m_timeLeft -= dt;

		// animation time has elapsed
		if (m_timeLeft <= 0.0f) {
			++m_iterations;

			if (((m_iterations - 1) < getRepeatCount()) && (getRepeatMode() != 0)) {
				// reset the animation
				m_timeLeft = getDuration();
				m_origin = *m_size;
				m_delta = (m_repeatMode == REVERSE) ? -m_delta : m_delta;
			} else {
				// end of the animation
				cancel();
			}
		}
	}
}
