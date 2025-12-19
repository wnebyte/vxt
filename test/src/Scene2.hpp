#ifndef VXT_SCENE2_HPP
#define VXT_SCENE2_HPP

#include "vxt/Scene.hpp"
#include "vxt/Windowfwd.hpp"

namespace vxt {
namespace test
{
class Scene2 : public vxt::Scene {
public:
	Scene2(vxt::Window *window);
	virtual ~Scene2() noexcept = default;

public: // scene implementation
	void init(void) override;
	void update(float dt) override;
};
} // namespace test
} // namespace vxt

#endif // VXT_SCENE2_HPP
