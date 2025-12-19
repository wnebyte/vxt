#ifndef VXT_ENTITY_HPP
#define VXT_ENTITY_HPP

#include <vector>
#include <memory>
#include <type_traits>

#include "Types.hpp"
#include "Scenefwd.hpp"
#include "ecs/Component.hpp"

namespace vxt {
namespace ecs
{
class Entity {
public:
	Entity();
	Entity(const std::string &name);
	~Entity() noexcept = default;

public:
	void init(Scene *scene);
	void update(float dt);
	void destroy(void);
	const std::vector<std::shared_ptr<Component>>& getComponents(void) const;
	std::vector<std::shared_ptr<Component>>& getComponents(void);
	uint32_t getId(void) const;
	std::string getName(void) const;

	template<typename T>
	inline void addComponent(T &component)
	{
		UFW_STATIC_ASSERT((std::is_base_of<Component, T>::value), "T needs to derive Component");
		component.m_entity = m_id;
		m_components.push_back(std::shared_ptr<T>{new T{component}});
	}

	template<typename T>
	inline void addComponent(std::shared_ptr<T> component)
	{
		UFW_STATIC_ASSERT((std::is_base_of<Component, T>::value), "T needs to derive Component");
		component.get()->m_entity = m_id;
		m_components.push_back(component);
	}

	template<typename T>
	inline const T* getComponent(void) const
	{
		const std::type_info& typeInfo = typeid(T);

		for (uint i = 0; i < m_components.size(); ++i) {
			if (typeid(*m_components[i].get()) == typeInfo) {
				return dynamic_cast<const T*>( m_components[i].get() );
			}
		}

		return NULL;
	}

	template<typename T>
	inline T* getComponent(void)
	{
		return const_cast<T*>(
			static_cast<const Entity*>(this)->getComponent<T>()
		);
	}

	template<typename T>
	inline bool hasComponent(void) const
	{
		return (getComponent<T>() != NULL);
	}

private:
	uint32_t m_id;
	std::string m_name;
	std::vector<std::shared_ptr<Component>> m_components;
};
} // namespace ecs
} // namespace vxt

#endif // VXT_ENTITY_HPP
