#ifndef VXT_GRID_LINES_HPP
#define VXT_GRID_LINES_HPP

#include "Types.hpp"
#include "Scenefwd.hpp"
#include "ecs/Component.hpp"

namespace vxt {
namespace cmp
{
class GridLines : public ecs::Component {
public:
	GridLines();
	~GridLines() noexcept = default;

public:
	void init(Scene *scene) override;
	void update(float dt) override;
};
} // namespace cmp
} // namespace vxt

#endif // VXT_GRID_LINES_HPP
