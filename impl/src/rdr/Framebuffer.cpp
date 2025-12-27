#include <glad/glad.h>

#include "rdr/Framebuffer.hpp"

using namespace vxt;
using namespace rdr;

Framebuffer::Framebuffer()
	: Framebuffer(0, 0, {}, NULL)
{
}

Framebuffer::Framebuffer(uint32_t width, uint32_t height, const std::vector<Texture*> &colorAttachments, Texture *depthAttachment)
	: m_id(NO_ID)
	, m_width(width)
	, m_height(height)
	, m_colorAttachments(colorAttachments)
	, m_depthAttachment(depthAttachment)
{
}

void Framebuffer::init(void)
{
	glGenFramebuffers(1, &m_id);
	bind();

	if (!m_colorAttachments.empty()) {
		uint32_t i = 0;
		uint32_t bufs[m_colorAttachments.size()];

		for (const Texture *colorAttachment : m_colorAttachments) {
			const uint32_t attachment = GL_COLOR_ATTACHMENT0 + i;

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachment,
				colorAttachment->getTarget(), colorAttachment->getId(), 0);
			bufs[i++] = attachment;
		}

		glDrawBuffers(i, bufs);
	}

	if (m_depthAttachment != NULL) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
			m_depthAttachment->getTarget(), m_depthAttachment->getId(), 0);
	}

	UFW_ASSERT((glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) && ("framebuffer status is not complete"));
	unbind();
}

void Framebuffer::bind(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void Framebuffer::unbind(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, NO_ID);
}

void Framebuffer::resize(uint32_t width, uint32_t height)
{
	m_width = width;
	m_height = height;

	for (Texture *colorAttachment : m_colorAttachments) {
		colorAttachment->resize(width, height);
	}

	if (m_depthAttachment != NULL) {
		m_depthAttachment->resize(width, height);
	}
}

uint32_t Framebuffer::getId(void) const
{
	return m_id;
}

uint32_t Framebuffer::getWidth(void) const
{
	return m_width;
}

uint32_t Framebuffer::getHeight(void) const
{
	return m_height;
}

std::size_t Framebuffer::getNumOfColorAttachments(void) const
{
	return m_colorAttachments.size();
}

Texture* Framebuffer::getColorAttachment(uint32_t index)
{
	return (index < getNumOfColorAttachments()) ?
		m_colorAttachments[index] : throw std::out_of_range{"index is out of range"};
}

Texture* Framebuffer::getDepthAttachment(void)
{
	return m_depthAttachment;
}
