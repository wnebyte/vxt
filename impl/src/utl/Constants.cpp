#include <glad/glad.h>

#include "utl/Constants.hpp"

using namespace vxt;

uint32_t utl::BUFS_ZERO_NONE_NONE[3] = { GL_COLOR_ATTACHMENT0, GL_NONE, GL_NONE };

uint32_t utl::BUFS_NONE_ONE_TWO[3] = { GL_NONE, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
