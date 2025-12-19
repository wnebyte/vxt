#ifndef VXT_BUILDER_HPP
#define VXT_BUILDER_HPP

#include <vector>

#include "Types.hpp"
#include "rdr/Texture.hpp"
#include "rdr/Framebuffer.hpp"

namespace vxt {
namespace rdr
{
class FramebufferBuilder {
public:
	FramebufferBuilder();
	~FramebufferBuilder() noexcept = default;

public:
	FramebufferBuilder& setWidth(uint32_t width);
	FramebufferBuilder& setHeight(uint32_t height);
	FramebufferBuilder& setSize(uint32_t width, uint32_t height);

	FramebufferBuilder& setColorAttachments(const std::vector<Texture*> &colorAttachments);
	FramebufferBuilder& addColorAttachment(Texture *colorAttachment);
	FramebufferBuilder& setDepthAttachment(Texture *depthAttachment);

	Framebuffer build(void) const;

private:
	uint32_t m_width;
	uint32_t m_height;
	std::vector<Texture*> m_colorAttachments;
	Texture *m_depthAttachment;
};

class TextureBuilder {
public:
	TextureBuilder();
	~TextureBuilder() noexcept = default;

public:
	TextureBuilder& setTarget(uint32_t target);
	TextureBuilder& setLevel(uint32_t level);
	TextureBuilder& setInternalFormat(uint32_t internalFormat);
	TextureBuilder& setBorder(uint32_t border);
	TextureBuilder& setFormat(uint32_t format);
	TextureBuilder& setType(uint32_t type);

	TextureBuilder& setWidth(uint32_t width);
	TextureBuilder& setHeight(uint32_t height);
	TextureBuilder& setSize(uint32_t width, uint32_t height);

	TextureBuilder& setPath(const std::string &path);
	TextureBuilder& setFlip(bool flip);

	TextureBuilder& setParameters(const std::vector<Texture::Parameter> &params);
	TextureBuilder& addParameter(const Texture::Parameter &param);

	template<typename T>
	T build(void);

private:
	Texture::Configuration m_config;
};

template<>
inline Texture TextureBuilder::build<Texture>(void)
{
	return Texture{m_config};
}

template<>
inline Texture::Configuration TextureBuilder::build<Texture::Configuration>(void)
{
	return m_config;
}

} // namespace rdr
} // namespace vxt

#endif // VXT_BUILDER_HPP
