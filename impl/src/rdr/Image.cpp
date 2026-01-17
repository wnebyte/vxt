#include <stb/stb_image.h>

#include "rdr/Image.hpp"

using namespace vxt;
using namespace rdr;

Image Image::load(const std::string &path, bool flip)
{
	Image image;
	stbi_set_flip_vertically_on_load(flip);
	image.data = stbi_load(path.c_str(), &image.width, &image.height, &image.channels, 0);
	return image;
}
