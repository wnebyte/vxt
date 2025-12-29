#include <stb/stb_image.h>

#include "rdr/Cubemap.hpp"

#include "utl/Assets.hpp"

using namespace vxt;
using namespace rdr;
using namespace utl;

using const_iterator = std::array<std::string, 6>::const_iterator;

Cubemap::Cubemap()
	: m_id(NO_ID)
{
}

void Cubemap::init(const std::array<std::string, 6> &faces)
{
	uint i = 0;

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	UFW_ASSERT((faces.size() == 6) && ("too many or too few faces"));

	for (const_iterator iter = faces.begin(); iter != faces.end(); ++iter, ++i) {
		const std::string path{Assets::toPath(*iter, "images")};
		int channels;
		int width, height;
		uint8_t *image = NULL;

		// load the image
		stbi_set_flip_vertically_on_load(false);
		image = stbi_load(path.c_str(), &width, &height, &channels, 0);
		UFW_ASSERT((image != NULL) && ("image is NULL"));
		UFW_ASSERT(((channels == 3) || (channels == 4)) && ("channels is not RGB or RGBA"));

		channels = (channels == 3) ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, channels, width, height,
			0, channels, GL_UNSIGNED_BYTE, image);

		// free the image 
		stbi_image_free(image);
	}
}

void Cubemap::bind(void)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
}

void Cubemap::unbind(void)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, NO_ID);
}

GLuint Cubemap::getId(void) const
{
	return m_id;
}
