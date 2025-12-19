#ifndef VXT_CAPACITY_SET_HPP
#define VXT_CAPACITY_SET_HPP

#include <set>
#include <functional>

#include "Types.hpp"

namespace vxt {
namespace utl
{
template<typename T>
class CapacitySet {
public:
	typedef std::function<void(const T& t)> ForEachFn;

public:
	CapacitySet(std::size_t capacity)
		: m_data()
		, m_capacity(capacity)
	{
	}

	~CapacitySet() noexcept = default;

public:
	int32_t find(const T &t) const
	{
		int32_t index = 0;
		for (const T &element : m_data) {
			if (element == t) {
				return index;
			}
			++index;
		}
		return -1;
	}

	std::size_t size(void) const
	{
		return m_data.size();
	}

	std::size_t capacity(void) const
	{
		return m_capacity;
	}

	bool empty(void) const
	{
		return m_data.empty();
	}

	bool contains(const T& t)
	{
		return (m_data.find(t) != m_data.end());
	}

	bool add(const T& t)
	{
		if (m_data.find(t) != m_data.end()) {
			return true;
		}
		if (size() < capacity()) {
			const std::pair<typename std::set<T>::iterator, bool> result = m_data.emplace(t);
			return (result.second);
		}
		return false;
	}

	bool remove(const T& t)
	{
		typename std::set<T>::iterator iter = m_data.find(t);
		if (iter != m_data.end()) {
			return (m_data.erase(iter) != m_data.end());
		}
		return false;
	}

	void forEach(ForEachFn fkn)
	{
		for (const T &t : m_data) {
			fkn(t);
		}
	}

private:
	std::set<T> m_data;
	std::size_t m_capacity;
};
} // namespace utl
} // namespace vxt

#endif // VXT_CAPACITY_SET_HPP
