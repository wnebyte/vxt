#ifndef VXT_IMAGE_HPP
#define VXT_IMAGE_HPP

#include "Types.hpp"

namespace vxt {
namespace rdr
{
struct Image {
	int32_t  width;
	int32_t  height;
	int32_t  channels;
	uint8_t *data;

	static Image load(const std::string &path, bool flip = false);
};
} // namespace rdr
} // namespace vxt

#endif // VXT_IMAGE_HPP
