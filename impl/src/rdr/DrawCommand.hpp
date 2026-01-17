#ifndef VXT_DRAW_COMMAND_HPP
#define VXT_DRAW_COMMAND_HPP

#include "Types.hpp"

namespace vxt {
namespace rdr
{
struct DrawArraysIndirectCommand {
	uint vertexCount; // count
	uint instanceCount; // primCount
	uint first;
	uint baseInstance;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_DRAW_COMMAND_HPP
