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

			if ( (event->action == GLFW_PRESS) || (event->action == GLFW_REPEAT) ) {
				const Camera::Direction dir = keyCodeToDirection(event->keyCode);

				if (dir != Camera::UNKNOWN) {
					adjustPosition(dir, event->mods, Application::dt());
				} else if (event->keyCode == GLFW_KEY_KP_DECIMAL) {
					PerspectiveCamera *camera = dynamic_cast<PerspectiveCamera*>( getCamera() );
					camera->setYaw(VXT_CAMERA_DEFAULT_YAW);
					camera->setPitch(VXT_CAMERA_DEFAULT_PITCH);
					std::printf("[%s] yaw=%.2f pitch=%.2f\n",
						TAG, camera->getYaw(), camera->getPitch());
				}
			}
			break;
		}
		case VXT_EVENT_CURSOR:
		{
			const io::CursorEvent *event = (io::CursorEvent*)data.get();
			adjustOrientation(event->xOffset, event->yOffset);
			break;
		}
		case VXT_EVENT_SCROLL:
		{
			const io::ScrollEvent *event = (io::ScrollEvent*)data.get();
			adjustZoom(event->yOffset);
			break;
		}
		default:
			break;
	}
}

std::set<uint> FpsCamera::get_events(void) const
{
	return std::set<uint>{VXT_EVENT_KEY, VXT_EVENT_CURSOR, VXT_EVENT_SCROLL};
}

void FpsCamera::adjustZoom(float yOffset)
{
	Camera* camera = getCamera();
	float zoom = camera->getZoom();

	zoom = ufw::math::clamp(zoom - yOffset, GETENV(VXT_MIN_ZOOM), GETENV(VXT_MAX_ZOOM));

	camera->setZoom(zoom);

#ifdef TRACE
	std::printf("[%s] zoom=%.2f\n", TAG, zoom);
#endif
}

void FpsCamera::adjustOrientation(float xOffset, float yOffset)
{
	PerspectiveCamera *camera = dynamic_cast<PerspectiveCamera*>( getCamera() );
	float yaw = camera->getYaw();
	float pitch = camera->getPitch();

	yaw   += GETENV(VXT_YAW_WEIGHT) * (xOffset * GETENV(VXT_MOUSE_SENSITIVITY));
	pitch += GETENV(VXT_PITCH_WEIGHT) * (yOffset * GETENV(VXT_MOUSE_SENSITIVITY));

	pitch = ufw::math::clamp(pitch, GETENV(VXT_MIN_PITCH), GETENV(VXT_MAX_PITCH));

	camera->setYaw(yaw);
	camera->setPitch(pitch);

#ifdef TRACE
	std::printf("[%s] yaw=%.2f pitch=%.2f\n", TAG, yaw, pitch);
#endif
}

void FpsCamera::adjustPosition(Camera::Direction dir, int mods, float dt)
{
	const float weight = (mods & GLFW_MOD_SHIFT) ? 10.0f : 1.0f;
	const float velocity = (GETENV(VXT_MOVEMENT_SPEED) * dt) * weight;
	Camera *camera = getCamera();

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
		default:
		case Camera::UNKNOWN:
			break;
	}

#ifdef TRACE
	std::printf("[%s] x=%.2f y=%.2f z=%.2f\n", TAG,
		camera->m_position.x, camera->m_position.y, camera->m_position.z);
#endif
}

Camera::Direction FpsCamera::keyCodeToDirection(int keyCode) const
{
	switch (keyCode) {
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
}

Camera* FpsCamera::getCamera(void)
{
	Camera *camera = getScene()->getCamera();
	UFW_ASSERT((camera != NULL) && ("camera is NULL"));
	return camera;
}
