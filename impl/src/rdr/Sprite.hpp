#ifndef VXT_SPIRTE_HPP
#define VXT_SPIRTE_HPP

#include <array>

#include "Types.hpp"
#include "rdr/Texture.hpp"

namespace vxt {
namespace rdr
{
class Sprite {
public:
	Sprite(Texture *texture = NULL);
	~Sprite() noexcept = default;

public:
	glm::vec2 getUv(uint32_t index) const;
	uv_array getUvs(void) const;
	void setUvs(const uv_array &uvs);
	Texture* getTexture(void);
	int32_t getTextureId(void) const;
	void setTexture(Texture *texture);
	float getWidth(void) const;
	void setWidth(float width);
	float getHeight(void) const;
	void setHeight(float height);

private:
	Texture *m_texture;
	float    m_width;
	float    m_height;
	uv_array m_uvs;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_SPIRTE_HPP
