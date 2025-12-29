#include <glad/glad.h>

#include "utl/Constants.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace vxt {
namespace utl
{
float ZERO_FILLER_VEC[4]      = { 0.0f, 0.0f, 0.0f, 0.0f };

float ONE_FILLER_VEC[4]       = { 1.0f, 1.0f, 1.0f, 1.0f };

GLenum BUFS_ZERO_NONE_NONE[3] = { GL_COLOR_ATTACHMENT0, GL_NONE, GL_NONE };

GLenum BUFS_NONE_ONE_TWO[3]   = { GL_NONE, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
} // namespace utl
} // namespace vxt

