#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "Application.hpp"

#include "io/Mouse.hpp"

#include "utl/Env.hpp"
#include "utl/Constants.hpp"

#include "cmp/EditorCamera.hpp"

#define TRACE
#define MIN_ZOOM 1.0f
#define MAX_ZOOM 90.0f
#define DRAG_SENSITIVITY 30.0f
#define CAMERA_POSITION_STEP 0.25f
#define SCROLL_SENSITIVITY 0.1f

using namespace vxt;
using namespace cmp;
using namespace utl;
using namespace io;

static float dragDebounce = 0.032f;
static glm::vec2 origin{0.0f, 0.0f};
static float lerpTime = 0.0f;

/// @brief Transforms Mouse position from Screen Space to World Space coordinates.
/// @param camera [in] The camera
/// @return Mouse position in World Space coordinates
static glm::vec2 toWorldCoordinates(const Camera *camera)
{
	glm::vec4 tmp;
	float x = Mouse::getX();
	float y = Mouse::getY();

	// screen space to ndc
	x = ((x / Application::getWindow()->getWidth()) * 2.0f) - 1.0f;
	y = -(((y / Application::getWindow()->getHeight()) * 2.0f) - 1.0f);
	// ndc to view space to world space
	tmp = glm::vec4{x, y, 0.0f, 1.0f};
	tmp = tmp * (camera->getInverseViewMatrix() * camera->getInverseProjectionMatrix());

	return glm::vec2{tmp};
}

EditorCamera::EditorCamera()
{
	ufw::add_event_handler(this);
}

EditorCamera::~EditorCamera()
{
	ufw::remove_event_handler(this);
}

void EditorCamera::init(Scene *scene)
{
	Component::init(scene);
}

void EditorCamera::update(float dt)
{
	Camera *camera = getCamera();
	const glm::vec3 prevPos{camera->getPosition()};

	if (Mouse::isButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
		if (dragDebounce > 0.0f) {
			origin = toWorldCoordinates(camera);
			dragDebounce -= dt;
		} else {
			const glm::vec2 pos{toWorldCoordinates(camera)};
			const glm::vec2 delta = (pos - origin);

			camera->sub((delta * dt) * GETENV(DRAG_SENSITIVITY));
			origin = glm::mix(origin, pos, dt);
		}
	} else if (dragDebounce <= 0.0f) {
		dragDebounce = 0.1f;
	}
#ifdef TRACE
	if (camera->m_position != prevPos) {
		std::printf("[Position] x=%.2f y=%.2f\n",
			camera->m_position.x, camera->m_position.y);
	}
#endif
}

void EditorCamera::handle_event(uint event, std::shared_ptr<void> data)
{
	if (m_scene != NULL) {
		Camera *camera = getCamera();

		switch (event) {
			case VXT_EVENT_KEY:
				handleKeyEvent(camera, (const io::KeyEvent*)data.get());
				break;
			case VXT_EVENT_SCROLL:
				handleScrollEvent(camera, (const io::ScrollEvent*)data.get());
				break;
			default:
				break;
		}
	}
}

std::set<uint> EditorCamera::get_events(void) const
{
	return std::set<uint>{VXT_EVENT_KEY, VXT_EVENT_SCROLL};
}

void EditorCamera::handleKeyEvent(Camera *camera, const io::KeyEvent *event)
{
	if (event->action == GLFW_PRESS) {
		const Camera::Direction dir = keyEventToDirection(event);

		if (dir != Camera::UNKNOWN) {
			updatePosition(camera, dir);
		}

		if (event->keyCode == GLFW_KEY_KP_DECIMAL) {
			resetPosition(camera);
		}
	}
}

void EditorCamera::handleScrollEvent(Camera *camera, const io::ScrollEvent *event)
{
	if (event->yOffset != 0.0f) {
		float zoom = camera->getZoom();
		zoom = ufw::math::clamp(zoom - event->yOffset, GETENV(MIN_ZOOM), GETENV(MAX_ZOOM));
		camera->setZoom(zoom);
#ifdef TRACE
		std::printf("[Zoom] %.2f\n", zoom);
#endif
	}
}

void EditorCamera::updatePosition(Camera *camera, Camera::Direction dir)
{
	const glm::vec3 prevPos{camera->getPosition()};

	switch (dir) {
		case Camera::RIGHT:
			camera->m_position.x += GETENV(CAMERA_POSITION_STEP);
			break;
		case Camera::LEFT:
			camera->m_position.x -= GETENV(CAMERA_POSITION_STEP);
			break;
		case Camera::UP:
			camera->m_position.y += GETENV(CAMERA_POSITION_STEP);
			break;
		case Camera::DOWN:
			camera->m_position.y -= GETENV(CAMERA_POSITION_STEP);
			break;
		default:
			break;
		}

#ifdef TRACE
	if (camera->m_position != prevPos) {
		std::printf("[Position] x=%.2f y=%.2f\n",
			camera->m_position.x, camera->m_position.y);
	}
#endif
}

void EditorCamera::resetPosition(Camera *camera)
{
	const float dt = Application::dt();
	const glm::vec2 pos{glm::mix(glm::vec2{camera->getPosition()}, {0.0f, 0.0f}, lerpTime)};
	const glm::vec3 prevPos{camera->getPosition()};

	if ((std::abs(pos.x) <= 5.0f) && (std::abs(pos.y) <= 5.0f)) {
		lerpTime = 0.0f;
		camera->setPosition({0.0f, 0.0f});
	} else {
		lerpTime += 0.1f * dt;
		camera->setPosition(pos);
	}

#ifdef TRACE
	if (camera->m_position != prevPos) {
		std::printf("[Position] x=%.2f y=%.2f\n",
			camera->m_position.x, camera->m_position.y);
	}
#endif
}

Camera::Direction EditorCamera::keyEventToDirection(const io::KeyEvent *event) const
{
	if (event->action == GLFW_PRESS) {
		switch (event->keyCode) {
			case GLFW_KEY_UP:
			case GLFW_KEY_W:	
				return Camera::UP;
			case GLFW_KEY_DOWN:
			case GLFW_KEY_S:
				return Camera::DOWN;
			case GLFW_KEY_LEFT:
			case GLFW_KEY_A:
				return Camera::LEFT;
			case GLFW_KEY_RIGHT:
			case GLFW_KEY_D:
				return Camera::RIGHT;
			default:
				return Camera::UNKNOWN;
		}
	}
	return Camera::UNKNOWN;
}

Camera* EditorCamera::getCamera(void)
{
	Camera *camera = NULL;

	UFW_ASSERT((m_scene != NULL) && ("scene is NULL"));
	camera = m_scene->getCamera();
	UFW_ASSERT((camera != NULL) && ("camera is NULL"));

	return camera;
}
