#ifndef VXT_SCENE_HPP
#define VXT_SCENE_HPP

#include <memory>
#include <vector>

#include "Types.hpp"
#include "Camera.hpp"
#include "Windowfwd.hpp"
#include "ecs/Entity.hpp"

namespace vxt {
class Scene {
private:
	using entity_it  = std::vector<ecs::Entity>::iterator;
	using entity_cit = std::vector<ecs::Entity>::const_iterator;

public:
	Scene();
	Scene(Window *window);
	Scene(Window *window, std::unique_ptr<Camera> &&camera);
	virtual ~Scene() noexcept = default;
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator=(Scene&&) = delete;

public:
	virtual void init(void);
	virtual void update(float dt);
	const Camera* getCamera(void) const;
	Camera* getCamera(void);
	void setCamera(std::unique_ptr<Camera> &&camera);

public:
	const ecs::Entity& getEntity(uint32_t id) const;
	ecs::Entity& getEntity(uint32_t id);
	const ecs::Entity& getEntity(const std::string &name) const;
	ecs::Entity& getEntity(const std::string &name);
	bool hasEntity(uint32_t id) const;
	bool hasEntity(const std::string &name) const;
	bool removeEntity(uint32_t id);
	bool removeEntity(const std::string &name);
	bool addEntity(const ecs::Entity &entity);

private:
	entity_cit findEntity(uint32_t id) const;
	entity_cit findEntity(const std::string &name) const;

protected:
	Window *m_window;
	std::unique_ptr<Camera> m_camera;
	std::vector<ecs::Entity> m_entities;
};
} // namespace vxt

#endif // VXT_SCENE_HPP
