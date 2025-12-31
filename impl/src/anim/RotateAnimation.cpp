#include "anim/RotateAnimation.hpp"

using namespace vxt;
using namespace anim;

RotateAnimation::RotateAnimation(float *rotation, float delta)
	: Animation()
	, m_rotation(rotation)
	, m_origin(*rotation)
	, m_delta(delta)
	, m_iterations(0)
{
}

void RotateAnimation::update(float dt)
{
	if ((isRunning()) && (m_timeLeft > 0.0f)) {
		const float interpolant = ufw::math::clamp(dt / m_timeLeft, 0.0f, 1.0f);

		// linearly interpolate the size and decrement the animation time
		*m_rotation = glm::mix(*m_rotation, m_origin + m_delta, interpolant);
		m_timeLeft -= dt;

		// animation time has elapsed
		if (m_timeLeft <= 0.0f) {
			++m_iterations;

			if (((m_iterations - 1) < getRepeatCount()) && (getRepeatMode() != 0)) {
				// reset the animation
				m_timeLeft = getDuration();
				m_origin = *m_rotation;
				m_delta = (m_repeatMode == REVERSE) ? -m_delta : m_delta;
			} else {
				// end of the animation
				cancel();
			}
		}
	}
}
