#include <glad/glad.h>

#include "rdr/Builder.hpp"

using namespace vxt;
using namespace rdr;

///////////////////////////////
///       Framebuffer       ///
///////////////////////////////

FramebufferBuilder::FramebufferBuilder()
	: m_width(0)
	, m_height(0)
	, m_colorAttachments()
	, m_depthAttachment(NULL)
{
}

FramebufferBuilder& FramebufferBuilder::setWidth(uint32_t width)
{
	m_width = width;
	return *this;
}

FramebufferBuilder& FramebufferBuilder::setHeight(uint32_t height)
{
	m_height = height;
	return *this;
}

FramebufferBuilder& FramebufferBuilder::setSize(uint32_t width, uint32_t height)
{
	m_width = width;
	m_height = height;
	return *this;
}

FramebufferBuilder& FramebufferBuilder::setColorAttachments(const std::vector<Texture*> &colorAttachments)
{
	m_colorAttachments = colorAttachments;
	return *this;
}

FramebufferBuilder& FramebufferBuilder::addColorAttachment(Texture *colorAttachment)
{
	m_colorAttachments.push_back(colorAttachment);
	return *this;
}

FramebufferBuilder& FramebufferBuilder::setDepthAttachment(Texture *depthAttachment)
{
	m_depthAttachment = depthAttachment;
	return *this;
}

Framebuffer FramebufferBuilder::build(void) const
{
	return Framebuffer{m_width, m_height, m_colorAttachments, m_depthAttachment};
}

///////////////////////////////
///         Texture         ///
///////////////////////////////

TextureBuilder::TextureBuilder()
	: m_config({GL_TEXTURE_2D, 0, 0, 0, 0, 0, 0, 0, {}, {}, "", false})
{
}

TextureBuilder& TextureBuilder::setTarget(uint32_t target)
{
	m_config.target = target;
	return *this;
}

TextureBuilder& TextureBuilder::setLevel(uint32_t level)
{
	m_config.level = level;
	return *this;
}

TextureBuilder& TextureBuilder::setInternalFormat(uint32_t internalFormat)
{
	m_config.internalFormat = internalFormat;
	return *this;
}

TextureBuilder& TextureBuilder::setBorder(uint32_t border)
{
	m_config.border = border;
	return *this;
}

TextureBuilder& TextureBuilder::setFormat(uint32_t format)
{
	m_config.format = format;
	return *this;
}

TextureBuilder& TextureBuilder::setType(uint32_t type)
{
	m_config.type = type;
	return *this;
}

TextureBuilder& TextureBuilder::setWidth(uint32_t width)
{
	m_config.width = width;
	return *this;
}

TextureBuilder& TextureBuilder::setHeight(uint32_t height)
{
	m_config.height = height;
	return *this;
}

TextureBuilder& TextureBuilder::setSize(uint32_t width, uint32_t height)
{
	m_config.width = width;
	m_config.height = height;
	return *this;
}

TextureBuilder& TextureBuilder::setPath(const std::string &path)
{
	m_config.path = path;
	return *this;
}

TextureBuilder& TextureBuilder::setFlip(bool flip)
{
	m_config.flip = flip;
	return *this;
}

TextureBuilder& TextureBuilder::setParameters(const std::vector<Texture::Parameter> &params)
{
	m_config.parameters = params;
	return *this;
}

TextureBuilder& TextureBuilder::addParameter(const Texture::Parameter &param)
{
	m_config.parameters.push_back(param);
	return *this;
}

TextureBuilder& TextureBuilder::addParameter(GLenum name, GLint value)
{
	return addParameter({name, value});
}

TextureBuilder& TextureBuilder::setImages(const std::vector<Image> &images)
{
	m_config.images = images;
	return *this;
}

TextureBuilder& TextureBuilder::addImage(const Image &image)
{
	m_config.images.push_back(image);
	return *this;
}
