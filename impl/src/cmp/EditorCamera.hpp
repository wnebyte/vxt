#ifndef VXT_EDITOR_CAMERA_HPP
#define VXT_EDITOR_CAMERA_HPP

#include "Types.hpp"
#include "Scenefwd.hpp"
#include "Camerafwd.hpp"
#include "io/Events.hpp"
#include "ecs/Component.hpp"

namespace vxt {
namespace cmp
{
class EditorCamera : public ecs::Component, public ufw::event_handler {
public:
	EditorCamera();
	~EditorCamera() noexcept;

public: // component implementation
	void init(Scene *scene) override;
	void update(float dt) override;

public: // event handler implementation
	void handle_event(uint event, std::shared_ptr<void> data) override;
	std::set<uint> get_events(void) const;

private:
	void handleKeyEvent(Camera *camera, const io::KeyEvent *event);
	void handleScrollEvent(Camera *camera, const io::ScrollEvent *event);

	void updatePosition(Camera *camera, Camera::Direction dir);
	void resetPosition(Camera *camera);
	Camera::Direction keyEventToDirection(const io::KeyEvent *event) const;
	Camera* getCamera(void);
};
} // namespace cmp
} // namespace vxt

#endif // VXT_EDITOR_CAMERA_HPP
