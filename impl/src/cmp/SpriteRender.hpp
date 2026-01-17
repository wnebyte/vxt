#ifndef VXT_SPRITE_RENDER_HPP
#define VXT_SPRITE_RENDER_HPP

#include <array>

#include "Types.hpp"
#include "Scenefwd.hpp"
#include "rdr/Sprite.hpp"
#include "rdr/Texture.hpp"
#include "ecs/Component.hpp"
#include "cmp/Transform.hpp"

namespace vxt {
namespace cmp
{
class SpriteRender : public ecs::Component {
public:
	SpriteRender();
	~SpriteRender() noexcept = default;

public:
	void init(Scene *scene) override;
	void update(float dt) override;
	rdr::Texture* getTexture(void);
	void setTexture(rdr::Texture *texture);
	uv_array getUvs(void) const;
	glm::vec4 getColor(void) const;
	void setColor(const glm::vec4 &color);
	bool isDirty(void) const;
	void clean(void);
	void dirty(void);

private:
	rdr::Sprite m_sprite;
	glm::vec4 m_color;
	Transform m_transform;
	bool m_isDirty;
};
} // namespace cmp
} // namespace vxt

#endif // VXT_SPRITE_RENDER_HPP