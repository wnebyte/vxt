#ifndef VXT_ANIMATION_HPP
#define VXT_ANIMATION_HPP

#include "Types.hpp"

namespace vxt {
namespace anim
{
class Animation {
public:
	enum {
		/// @brief The specified dimension is an absolute number of pixels.
		ABSOLUTE,
		/// @brief Repeat the animation indefinitely.
		INFINITE,
		/// @brief The specified dimension holds a float and should be multiplied by the height or width of the parent of the object being animated.
		RELATIVE_TO_PARENT,
		/// @brief The specified dimension holds a float and should be multiplied by the height or width of the object being animated.
		RELATIVE_TO_SELF,
		/// @brief When the animation reaches the end and the repeat count is INFINTE_REPEAT or a positive value, the animation restarts from the beginning.
		RESTART,
		/// @brief When the animation reaches the end and the repeat count is INFINTE_REPEAT or a positive value, the animation plays backward (and then forward again).
		REVERSE,
		/// @brief Can be used as the start time to indicate the start time should be the current time.
		START_ON_FIRST_FRAME
	};

public:
	Animation();
	virtual ~Animation() noexcept = default;

public:
	/// @brief Cancel the animation.
	void cancel(void);

	/// @brief Start the animation.
	virtual void start(void);

	/// @brief Update the animation.
	virtual void update(float dt);

	/// @brief How long this animation should last.
	float getDuration(void) const;

	/// @brief Sets how long this animation should last.
	void setDuration(float duration);

	/// @brief How long until this animation ends.
	float getTimeLeft(void) const;

	/// @brief Defines how many times the animation should repeat.
	uint64_t getRepeatCount(void) const;

	/// @brief Sets how many times the animation should repeat.
	void setRepeatCount(uint64_t repeatCount);

	/// @brief Defines what this animation should do when it reaches the end.
	uint32_t getRepeatMode(void) const;

	/// @brief Sets what this animation should do when it reaches the end.
	void setRepeatMode(uint32_t repeatMode);

	/// @brief When this animation should start, relative to startTime.
	uint64_t getStartOffset(void) const;

	/// @brief Sets when this animation should start, relative to startTime.
	void setStartOffset(uint64_t startOffset);

	/// @brief When this animation should start.
	uint64_t getStartTime(void) const;

	/// @brief Sets when this animation should start.
	void setStartTime(uint64_t startTime);

	/// @brief Indicates whether this animation has ended or not.
	bool hasEnded(void) const;

	/// @brief Indicates whether this animation has started or not.
	bool hasStarted(void) const;

	bool isRunning(void) const;

protected:
	float    m_duration;
	float    m_timeLeft;
	uint64_t m_repeatCount;
	uint32_t m_repeatMode;
	uint64_t m_startOffset;
	uint64_t m_startTime;
	bool     m_started;
	bool     m_ended;
};
} // namespace anim
} // namespace vxt

#endif // VXT_ANIMATION_HPP
