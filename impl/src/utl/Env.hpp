#ifndef VXT_ENV_HPP
#define VXT_ENV_HPP

#include <cstdlib>
#include <type_traits>

#include "Types.hpp"

#define VXT_MOVEMENT_SPEED 7.5f
#define VXT_MOUSE_SENSITIVITY 1.0f

#define VXT_YAW_WEIGHT 0.005f
#define VXT_PITCH_WEIGHT 0.0005f

#define VXT_MIN_PITCH -2.0f // -90.0f
#define VXT_MAX_PITCH 2.0f  // 90.0f

#define VXT_MIN_ZOOM 1.0f
#define VXT_MAX_ZOOM 90.0f

#define GETENV(env) (vxt::utl::getenv(#env, env))

namespace vxt {
namespace utl
{
template<typename T>
T getenv(const char *name, T defaultValue)
{
	const char *value;
	T rv;

	UFW_STATIC_ASSERT(std::is_arithmetic<T>::value, "Arithmetic type is required");
	value = std::getenv(name);

	if (value != NULL) {
		if (std::is_integral<T>::value) {
			// T is an integer type
			if (std::is_signed<T>::value) {
				// T is a signed integer type
				rv = std::atoi(value);
			} else {
				// T is an unsigned integer type
				rv = std::strtoul(value, NULL, 0);
			}
		} else {
			// T is a floating-point type
			rv = std::stof(value);
		}
	} else {
		rv = defaultValue;
	}

	return rv;
}
} // namespace utl
} // namespace vxt

#endif // VXT_ENV_HPP
