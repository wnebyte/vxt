#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene.hpp"
#include "Application.hpp"
#include "PerspectiveCamera.hpp"

#include "utl/Env.hpp"

#include "cmp/FpsCamera.hpp"

#define TRACE
#define TAG "FpsCamera"

using namespace vxt;
using namespace ecs;
using namespace cmp;

FpsCamera::FpsCamera()
{
	ufw::add_event_handler(this);
}

FpsCamera::~FpsCamera()
{
	ufw::remove_event_handler(this);
}

void FpsCamera::handle_event(uint event, std::shared_ptr<void> data)
{
	switch (event) {
		case VXT_EVENT_KEY:
		{
			const io::KeyEvent *event = (io::KeyEvent*)data.get();

			if ((event->action == GLFW_PRESS) || (event->action == GLFW_REPEAT)) {
				const Camera::Direction dir = keyEventToDirection(event);

				if (dir != Camera::UNKNOWN) {
					updatePosition(dir, Application::dt());
				}
			}
		}
			break;
		case VXT_EVENT_CURSOR:
		{
			const io::CursorEvent *event = (io::CursorEvent*)data.get();

			if ((event->xOffset != 0.0f) || (event->yOffset != 0.0f)) {
				updateOrientation(event->xOffset, event->yOffset);
			}
		}
			break;
		default:
			break;
	}
}

std::set<uint> FpsCamera::get_events(void) const
{
	return std::set<uint>{VXT_EVENT_KEY, VXT_EVENT_CURSOR};
}

void FpsCamera::updateZoom(float yOffset)
{
	Camera* camera = getCamera();
	float zoom = camera->getZoom();

	zoom = ufw::math::clamp(zoom - yOffset, GETENV(VXT_MIN_ZOOM), GETENV(VXT_MAX_ZOOM));

	camera->setZoom(zoom);
}

void FpsCamera::updateOrientation(float xOffset, float yOffset)
{
	PerspectiveCamera *camera = dynamic_cast<PerspectiveCamera*>( getCamera() );
	float yaw = camera->getYaw();
	float pitch = camera->getPitch();

	yaw   += GETENV(VXT_YAW_WEIGHT) * (xOffset * GETENV(VXT_MOUSE_SENSITIVITY));
	pitch += GETENV(VXT_PITCH_WEIGHT) * (yOffset * GETENV(VXT_MOUSE_SENSITIVITY));

	pitch = ufw::math::clamp(pitch, GETENV(VXT_MIN_PITCH), GETENV(VXT_MAX_PITCH));

	camera->setYaw(yaw);
	camera->setPitch(pitch);
}

void FpsCamera::updatePosition(Camera::Direction dir, float dt)
{
	const float velocity = GETENV(VXT_MOVEMENT_SPEED) * dt;
	Camera *camera = getCamera();
	const glm::vec3 prevPos{camera->getPosition()};

	switch (dir) {
		case Camera::FORWARD:
			camera->add(camera->getForward() * velocity);
			break;
		case Camera::BACKWARD:
			camera->sub(camera->getForward() * velocity);
			break;
		case Camera::RIGHT:
			camera->add(camera->getRight() * velocity);
			break;
		case Camera::LEFT:
			camera->sub(camera->getRight() * velocity);
			break;
		case Camera::UP:
			camera->add(camera->getUp() * velocity);
			break;
		case Camera::DOWN:
			camera->sub(camera->getUp() * velocity);
			break;
		case Camera::UNKNOWN:
			break;
	}

#ifdef TRACE
	if (camera->getPosition() != prevPos) {
		std::printf("[%s] x=%.2f y=%.2f z=%.2f\n", TAG,
			camera->m_position.x, camera->m_position.y, camera->m_position.z);
	}
#endif
}

Camera::Direction FpsCamera::keyEventToDirection(const io::KeyEvent *event) const
{
	switch (event->keyCode) {
		case GLFW_KEY_W:	
			return Camera::FORWARD;
		case GLFW_KEY_S:
			return Camera::BACKWARD;
		case GLFW_KEY_D:
			return Camera::RIGHT;
		case GLFW_KEY_A:
			return Camera::LEFT;
		case GLFW_KEY_UP:
			return Camera::UP;
		case GLFW_KEY_DOWN:
			return Camera::DOWN;
		default:
			return Camera::UNKNOWN;
	}

	return Camera::UNKNOWN;
}

Camera* FpsCamera::getCamera(void)
{
	Camera *camera = NULL;

	UFW_ASSERT((m_scene != NULL) && ("scene is NULL"));
	camera = m_scene->getCamera();
	UFW_ASSERT((camera != NULL) && ("camera is NULL"));

	return camera;
}
