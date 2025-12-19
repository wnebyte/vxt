#include "Scene.hpp"
#include "Window.hpp"

using namespace vxt;
using namespace ecs;

Scene::Scene()
	: Scene(NULL)
{
}

Scene::Scene(Window *window)
	: m_window(window)
	, m_camera()
	, m_entities()
{
}

Scene::Scene(Window *window, std::unique_ptr<Camera> &&camera)
	: m_window(window)
	, m_camera(std::move(camera))
	, m_entities()
{
}

void Scene::init(void)
{
	for (uint i = 0; i < m_entities.size(); ++i) {
		m_entities[i].init(this);
	}
}

void Scene::update(float dt)
{
	if (m_camera) {
		m_camera->setAspectRatio(m_window->getAspectRatio());
		m_camera->update(dt);
	}

	for (uint i = 0; i < m_entities.size(); ++i) {
		m_entities[i].update(dt);
	}
}

const Camera* Scene::getCamera(void) const
{
	return m_camera.get();
}

Camera* Scene::getCamera(void)
{
	return const_cast<Camera*>(
		static_cast<const Scene*>(this)->getCamera()
	);
}

void Scene::setCamera(std::unique_ptr<Camera> &&camera)
{
	m_camera = std::move(camera);
}

const Entity& Scene::getEntity(const std::string &name) const
{
	entity_cit iter = findEntity(name);

	return (iter != m_entities.cend()) ? *iter : throw std::exception{};
}

Entity& Scene::getEntity(const std::string &name)
{
	return const_cast<Entity&>(
		static_cast<const Scene*>(this)->getEntity(name)
	);
}

const Entity& Scene::getEntity(uint32_t id) const
{
	entity_cit iter{findEntity(id)};

	return (iter != m_entities.cend()) ? *iter : throw std::exception{};
}

Entity& Scene::getEntity(uint32_t id)
{
	return const_cast<Entity&>(
		static_cast<const Scene*>(this)->getEntity(id)
	);
}

bool Scene::hasEntity(uint32_t id) const
{
	return (findEntity(id) != m_entities.cend());
}

bool Scene::hasEntity(const std::string &name) const
{
	return (findEntity(name) != m_entities.cend());
}

bool Scene::addEntity(const Entity &entity)
{
	bool rv = false;

	if (!hasEntity(entity.getId())) {
		m_entities.push_back(entity);
		rv = true;
	}

	return rv;
}

bool Scene::removeEntity(uint32_t id)
{
	bool rv = false;
	entity_cit iter{findEntity(id)};

	if (iter != m_entities.cend()) {
		rv = (m_entities.erase(iter) != m_entities.end());
	}

	return rv;
}

bool Scene::removeEntity(const std::string &name)
{
	bool rv = false;
	entity_cit iter{findEntity(name)};

	if (iter != m_entities.cend()) {
		rv = (m_entities.erase(iter) != m_entities.end());
	}

	return rv;
}

Scene::entity_cit Scene::findEntity(uint32_t id) const
{
	entity_cit rv{m_entities.cend()};

	for (entity_cit iter = m_entities.cbegin(); iter != rv; ++iter) {
		if (iter->getId() == id) {
			rv = iter;
			break;
		}
	}

	return rv;
}

Scene::entity_cit Scene::findEntity(const std::string &name) const
{
	entity_cit rv{m_entities.cend()};

	for (entity_cit iter = m_entities.cbegin(); iter != rv; ++iter) {
		if (iter->getName() == name) {
			rv = iter;
			break;
		}
	}

	return rv;
}
