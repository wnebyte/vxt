#include "utl/Misc.hpp"

using namespace vxt;
using namespace rdr;

namespace vxt {
namespace utl
{
std::vector<rdr::Image> pack3(const std::string &path)
{
	std::vector<Image> images;

	UFW_ASSERT((ufw::fs::is_dir(path)) && ("not a dir"));

	ufw::fs::for_each(path, [&images](const std::string &file) {
		Image image = Image::load(file, true);
		UFW_ASSERT((image.data != NULL) && ("image is NULL"));
		UFW_ASSERT(((image.channels == 3) || (image.channels == 4)) && ("channels is not RGB or RGBA"));
		images.push_back(image);
	}, (ufw::fs::DIRECTORY | ufw::fs::REGULAR_FILE));

	return images;
}
} // namespace utl
} // namespace vxt
