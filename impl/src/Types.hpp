#ifndef VXT_TYPES_HPP
#define VXT_TYPES_HPP

// std includes
#include <string>
#include <cstdint>
#include <std.hpp>

// glm includes
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

// ufw includes
#include <ufw/ufw.hpp>

/// @brief No ID.
#define NO_ID 0

/// @brief No texture ID.
#define NO_TEX_ID -1

/// @brief Undefined zIndex.
#define UNDEFINED_ZINDEX 0x7FFFFFFF

/// @brief Macro for determining the size of an array measured in elements.
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

/// @brief uv array Type.
typedef std::array<glm::vec2, 4> uv_array;

#endif // VXT_TYPES_HPP
