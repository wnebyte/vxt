#include "Scene.hpp"
#include "ecs/Component.hpp"

using namespace vxt;
using namespace ecs;

void Component::init(Scene *scene)
{
	m_scene = scene;
}

void Component::update(float dt)
{
	// virtual
}

void Component::destroy(void)
{
	// virtual
}
