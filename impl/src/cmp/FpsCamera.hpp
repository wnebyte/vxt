#ifndef VXT_FPS_CAMERA_HPP
#define VXT_FPS_CAMERA_HPP

#include "Types.hpp"
#include "Camera.hpp"
#include "io/Events.hpp"
#include "ecs/Component.hpp"

namespace vxt {
namespace cmp
{
class FpsCamera : public ecs::Component, public ufw::event_handler {
public:
	FpsCamera();
	~FpsCamera();

public: // event handler implementation
	void handle_event(uint event, std::shared_ptr<void> data);
	std::set<uint> get_events(void) const;

private:
	Camera* getCamera(void);
	void updateZoom(float yOffset);
	void updatePosition(Camera::Direction dir, float dt);
	void updateOrientation(float xOffset, float yOffset);
	Camera::Direction keyEventToDirection(const io::KeyEvent *event) const;
};
} // namespace cmp
} // namespace vxt

#endif // VXT_FPS_CAMERA_HPP
