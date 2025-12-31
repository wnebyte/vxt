#include "anim/Animation.hpp"

using namespace vxt;
using namespace anim;

Animation::Animation()
	: m_duration(0.0f)
	, m_timeLeft(0.0f)
	, m_repeatCount(0)
	, m_repeatMode(0)
	, m_startOffset(0)
	, m_startTime(START_ON_FIRST_FRAME)
	, m_started(false)
	, m_ended(false)
{
}

void Animation::cancel(void)
{
	m_ended = true;
}

void Animation::start(void)
{
	m_started = true;
	m_timeLeft = getDuration();
}

void Animation::update(float dt)
{
	// virtual
}

float Animation::getDuration(void) const
{
	return m_duration;
}

void Animation::setDuration(float duration)
{
	m_duration = duration;
}

float Animation::getTimeLeft(void) const
{
	return m_timeLeft;
}

uint64_t Animation::getRepeatCount(void) const
{
	return m_repeatCount;
}

void Animation::setRepeatCount(uint64_t repeatCount)
{
	m_repeatCount = repeatCount;
}

uint32_t Animation::getRepeatMode(void) const
{
	return m_repeatMode;
}

void Animation::setRepeatMode(uint32_t repeatMode)
{
	m_repeatMode = repeatMode;
}

uint64_t Animation::getStartOffset(void) const
{
	return m_startOffset;
}

void Animation::setStartOffset(uint64_t startOffset)
{
	m_startOffset = startOffset;
}

uint64_t Animation::getStartTime(void) const
{
	return m_startTime;
}

void Animation::setStartTime(uint64_t startTime)
{
	m_startTime = startTime;
}

bool Animation::hasEnded(void) const
{
	return m_ended;
}

bool Animation::hasStarted(void) const
{
	return m_started;
}

bool Animation::isRunning(void) const
{
	return hasStarted() && !hasEnded();
}
