#include <cstring>

#include "rdr/Sprite.hpp"
#include "utl/Constants.hpp"

using namespace vxt;
using namespace rdr;

// 3 ---------- 0    Axis orientation
// |            |     y
// |            |     |
// |            |     +--- x
// |            |  
// 2 ---------- 1

Sprite::Sprite(Texture *texture)
	: m_texture(texture)
	, m_width(0)
	, m_height(0)
	, m_uvs({UV_TR, UV_BR, UV_BL, UV_TL})
{
}

glm::vec2 Sprite::getUv(uint32_t index) const
{
	const glm::vec2 uvs[6] = {
		m_uvs[0], // TR
		m_uvs[3], // TL
		m_uvs[2], // BL
		m_uvs[1], // BR
		m_uvs[0], // TR
		m_uvs[2]  // BL
	};

	return uvs[index];
}

uv_array Sprite::getUvs(void) const
{
	return m_uvs;
}

void Sprite::setUvs(const uv_array &uvs)
{
	m_uvs = uvs;
}

Texture* Sprite::getTexture(void)
{
	return m_texture;
}

int32_t Sprite::getTextureId(void) const
{
	return (m_texture != NULL) ? m_texture->getId() : NO_TEX_ID;
}

void Sprite::setTexture(Texture *texture)
{
	m_texture = texture;
}

float Sprite::getWidth(void) const
{
	return m_width;
}

void Sprite::setWidth(float width)
{
	m_width = width;
}

float Sprite::getHeight(void) const
{
	return m_height;
}

void Sprite::setHeight(float height)
{
	m_height = height;
}

