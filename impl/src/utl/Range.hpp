#ifndef VXT_RANGE_HPP
#define VXT_RANGE_HPP

#include <set>
#include <vector>

#include "Types.hpp"

namespace vxt {
namespace utl
{
enum BoundPolicy {
	INCLUSIVE,
	EXCLUSIVE
};

template<typename T>
struct Bound {
	Bound(const T &_val, BoundPolicy _policy = INCLUSIVE)
		: val(_val)
		, policy(_policy)
	{
	}

	T val;
	BoundPolicy policy;
};

template<typename T>
struct Range {
	Range(const Bound<T> &_lower, const Bound<T> &_upper)
	 : lower(_lower)
	 , upper(_upper)
	 {
		UFW_ASSERT((lower.val < upper.val) && ("lower bound is not less than upper bound"));
	 }

	inline std::vector<T> toVector(void) const
	{
		std::vector<T> v;

		for (T value = lower.val; value <= upper.val; ++value) {
			if (((lower.policy == EXCLUSIVE) && (value == lower.val)) ||
				((upper.policy == EXCLUSIVE) && (value == upper.val))) {
				// do nothing
			} else {
				v.push_back(value);
			}
		}

		return v;
	}

	inline std::set<T> toSet(void) const
	{
		const std::vector<T> v{toVector()};
		return std::set<T>{v.begin(), v.end()};
	}

	static Range<T> from(const T &from, const T &to)
	{
		return Range<T>{Bound<T>{from}, Bound<T>{to}};
	}

	Bound<T> lower;
	Bound<T> upper;
};
} // namespace utl
} // namespace vxt

#endif // VXT_RANGE_HPP
