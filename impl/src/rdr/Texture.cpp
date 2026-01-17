#include <glad/glad.h>

#include <stb/stb_image.h>

#include "rdr/Texture.hpp"

#define TRACE

using namespace vxt;
using namespace rdr;

Texture::Texture(const Configuration &config)
	: m_id(NO_ID)
	, m_target(config.target)
	, m_path(config.path)
	, m_width(config.width)
	, m_height(config.height)
	, m_config(config)
{
}

void Texture::init(bool create)
{
	if (create) {
		glGenTextures(1, &m_id);
	}

	bind();

	for (const Parameter &param : m_config.parameters) {
		glTexParameteri(m_target, param.name, param.value);
	}

	if (m_target == GL_TEXTURE_2D_ARRAY) {
		GLenum format;
		GLsizei imageCount;
		const std::vector<Image> &images = m_config.images;

		UFW_ASSERT((images.size() > 0) && ("images is empty"));

		imageCount = images.size();
		format     = (images[0].channels == 3) ? GL_RGB : GL_RGBA;
		m_width    = images[0].width;
		m_height   = images[0].height;

		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, format, m_width, m_height,
			imageCount, 0, format, GL_UNSIGNED_BYTE, NULL);

		for (int i = 0; i < imageCount; ++i) {
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
				0, 0, i, m_width, m_height, 1,
				format, GL_UNSIGNED_BYTE, images[i].data);
			delete images[i].data;
		}

		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
	} else if (ufw::fs::exists(m_path)) {
		int channels;
		uint8_t *image = NULL;

		// load the image
		stbi_set_flip_vertically_on_load(m_config.flip);
		image = stbi_load(m_path.c_str(), (int*)&m_width, (int*)&m_height, &channels, 0);
		UFW_ASSERT((image != NULL) && ("image is NULL"));
		UFW_ASSERT(((channels == 3) || (channels == 4)) && ("channels is not RGB or RGBA"));

		channels = (channels == 3) ? GL_RGB : GL_RGBA;
		glTexImage2D(m_target, m_config.level, channels, m_width, m_height,
			m_config.border, channels, GL_UNSIGNED_BYTE, image);

		// free the image
		stbi_image_free(image);
	} else {
		glTexImage2D(m_target, m_config.level, m_config.internalFormat, m_width, m_height,
			m_config.border, m_config.format, m_config.type, NULL);
	}
}

void Texture::resize(uint32_t width, uint32_t height)
{
	m_width = width;
	m_height = height;
	init(false);
}

void Texture::bind(void)
{
	glBindTexture(m_target, m_id);
}

void Texture::unbind(void)
{
	glBindTexture(m_target, NO_ID);
}

int32_t Texture::getId(void) const
{
	return (m_id != NO_ID) ? m_id : NO_TEX_ID;
}

GLenum Texture::getTarget(void) const
{
	return m_target;
}

uint32_t Texture::getWidth(void) const
{
	return m_width;
}

uint32_t Texture::getHeight(void) const
{
	return m_height;
}

std::string Texture::getPath(void) const
{
	return m_path;
}
