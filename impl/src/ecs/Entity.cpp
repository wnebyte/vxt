#include "Scene.hpp"
#include "ecs/Entity.hpp"

using namespace vxt;
using namespace ecs;

static uint32_t nextId = 0U;

Entity::Entity()
	: Entity("Entity_" + std::to_string(nextId))
{
}

Entity::Entity(const std::string &name)
	: m_id(nextId++)
	, m_name(name)
	, m_components()
{
}

void Entity::init(Scene *scene)
{
	for (uint i = 0; i < m_components.size(); ++i) {
		m_components[i]->init(scene);
	}
}

void Entity::update(float dt)
{
	for (uint i = 0; i < m_components.size(); ++i) {
		m_components[i]->update(dt);
	}
}

void Entity::destroy(void)
{
	for (uint i = 0; i < m_components.size(); ++i) {
		m_components[i]->destroy();
	}
}

const std::vector<std::shared_ptr<Component>>& Entity::getComponents(void) const
{
	return m_components;
}

std::vector<std::shared_ptr<Component>>& Entity::getComponents(void)
{
	return const_cast<std::vector<std::shared_ptr<Component>>&>(
		static_cast<const Entity*>(this)->getComponents()
	);
}

uint32_t Entity::getId(void) const
{
	return m_id;
}

std::string Entity::getName(void) const
{
	return m_name;
}
