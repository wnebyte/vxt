#include "rdr/Renderer.hpp"

using namespace vxt;
using namespace rdr;

int32_t Renderer::zIndex(void) const
{
	return 0;
}

int32_t Renderer::compareTo(const Renderer *r1, const Renderer *r2)
{
	return (r1->zIndex() - r2->zIndex());
}
