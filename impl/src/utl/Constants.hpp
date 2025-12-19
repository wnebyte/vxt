#ifndef VXT_CONSTANTS_HPP
#define VXT_CONSTANTS_HPP

#include "Types.hpp"

#define ZERO_FILLER_VEC2 (glm::vec2{0.0f, 0.0f})

#define ZERO_FILLER_VEC3 (glm::vec3{0.0f, 0.0f, 0.0f})

#define ZERO_FILLER_VEC4 (glm::vec4{0.0f, 0.0f, 0.0f, 0.0f})

#define ONE_FILLER_VEC2  (glm::vec2{1.0f, 1.0f})

#define ONE_FILLER_VEC3  (glm::vec3{1.0f, 1.0f, 1.0f})

#define ONE_FILLER_VEC4  (glm::vec4{1.0f, 1.0f, 1.0f, 1.0f})

#define UV_TR (glm::vec2{1.0f, 1.0f})

#define UV_BR (glm::vec2{1.0f, 0.0f})

#define UV_BL (glm::vec2{0.0f, 0.0f})

#define UV_TL (glm::vec2{0.0f, 1.0f})

namespace vxt {
namespace utl
{
extern uint32_t BUFS_ZERO_NONE_NONE[3];

extern uint32_t BUFS_NONE_ONE_TWO[3];
} // namespace utl
} // namespace vxt

#endif // VXT_CONSTANTS_HPP
