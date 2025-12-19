#ifndef VXT_SCENE3_HPP
#define VXT_SCENE3_HPP

#include "vxt/Scene.hpp"
#include "vxt/Windowfwd.hpp"

namespace vxt {
namespace test
{
class Scene3 : public vxt::Scene {
public:
	Scene3(vxt::Window *window);
	virtual ~Scene3() noexcept = default;

public: // scene implementation
	void init(void) override;
	void update(float dt) override;
};
} // namespace test
} // namespace vxt

#endif // VXT_SCENE3_HPP
