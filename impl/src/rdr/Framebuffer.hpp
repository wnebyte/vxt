#ifndef VXT_FRAMEBUFFER_HPP
#define VXT_FRAMEBUFFER_HPP

#include <vector>

#include "Types.hpp"
#include "rdr/Texture.hpp"

namespace vxt {
namespace rdr
{
class Framebuffer {
public:
	Framebuffer();
	Framebuffer(uint32_t width, uint32_t height, const std::vector<Texture*> &colorAttachments, Texture *depthAttachment = NULL);
	~Framebuffer() noexcept = default;

public:
	void init(void);
	void bind(void);
	void resize(uint32_t width, uint32_t height);
	uint32_t getId(void) const;
	uint32_t getWidth(void) const;
	uint32_t getHeight(void) const;
	std::size_t getNumOfColorAttachments(void) const;
	Texture* getColorAttachment(uint32_t index);
	Texture* getDepthAttachment(void);
	static void unbind(void);

private:
	uint32_t m_id;
	uint32_t m_width;
	uint32_t m_height;
	std::vector<Texture*> m_colorAttachments;
	Texture *m_depthAttachment;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_FRAMEBUFFER_HPP

