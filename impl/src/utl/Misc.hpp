#ifndef VXT_MISC_HPP
#define VXT_MISC_HPP

#include <vector>

#include "Types.hpp"
#include "rdr/Image.hpp"

namespace vxt {
namespace utl
{
std::vector<rdr::Image> pack3(const std::string &path);
} // namespace utl
} // namespace vxt

#endif // VXT_MISC_HPP
