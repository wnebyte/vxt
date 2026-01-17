#ifndef VXT_STD_HPP
#define VXT_STD_HPP

#include <memory>

namespace std _GLIBCXX_VISIBILITY(default)
{
#if __cpluscplus < 201402L // C++14
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
	return std::unique_ptr<T>{new T{std::forward<Args>(args)...}};
}
#endif
} // namespace std

#endif // VXT_STD_HPP
