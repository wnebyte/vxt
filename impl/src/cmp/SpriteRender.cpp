#include "Scene.hpp"
#include "cmp/SpriteRender.hpp"

using namespace vxt;
using namespace rdr;
using namespace cmp;
using namespace ecs;

SpriteRender::SpriteRender()
	: m_sprite()
	, m_color()
	, m_transform()
	, m_isDirty(true)
{
}

void SpriteRender::init(Scene *scene)
{
	Component::init(scene);
	m_transform = *(getScene()->getEntity(m_entity).getComponent<Transform>());
}

void SpriteRender::update(float dt)
{
	const Transform transform = *(getScene()->getEntity(m_entity).getComponent<Transform>());

	if (m_transform != transform) {
		m_transform = transform;
		m_isDirty = true;
	}
}

Texture* SpriteRender::getTexture(void)
{
	return m_sprite.getTexture();
}

void SpriteRender::setTexture(Texture *texture)
{
	m_sprite.setTexture(texture);
}

uv_array SpriteRender::getUvs(void) const
{
	return m_sprite.getUvs();
}

glm::vec4 SpriteRender::getColor(void) const
{
	return m_color;
}

void SpriteRender::setColor(const glm::vec4 &color)
{
	m_color = color;
}

bool SpriteRender::isDirty(void) const
{
	return m_isDirty;
}

void SpriteRender::clean(void)
{
	m_isDirty = false;
}

void SpriteRender::dirty(void)
{
	m_isDirty = true;
}
