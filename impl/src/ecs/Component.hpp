#ifndef VXT_COMPONENT_HPP
#define VXT_COMPONENT_HPP

#include "Types.hpp"
#include "Scenefwd.hpp"

namespace vxt {
namespace ecs
{
class Component {
public:
	virtual ~Component() noexcept = default;

public:
	virtual void init(Scene *scene);
	virtual void update(float dt);
	virtual void destroy(void);

protected:
	inline Scene* getScene(void)
	{
		UFW_ASSERT((m_scene != NULL) && ("scene is NULL"));
		return m_scene;
	}

public:
	uint32_t m_entity;
	Scene *m_scene;
};
} // namespace ecs
} // namespace vxt

#endif // VXT_COMPONENT_HPP
