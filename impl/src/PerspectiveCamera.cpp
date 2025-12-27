#include "PerspectiveCamera.hpp"

using namespace vxt;

PerspectiveCamera::PerspectiveCamera(const glm::vec3 &position,
									 float zNear,
									 float zFar,
									 float aspectRatio,
									 float yaw,
									 float pitch,
									 const glm::vec3 &forward,
									 const glm::vec3 &up,
									 const glm::vec3 &right)
	: Camera(position, zNear, zFar, aspectRatio, forward, up, right)
	, m_wUp(up)
	, m_yaw(yaw)
	, m_pitch(pitch)
{
}

void PerspectiveCamera::update(float dt)
{
	updateCameraVectors();
	Camera::update(dt);
}

void PerspectiveCamera::adjustProjection(void)
{
	m_projectionMatrix = glm::perspective(glm::radians(m_zoom), m_aspectRatio, m_position.z + 0.1f, m_position.z + 10000.0f);
	m_inverseProjectionMatrix = glm::inverse(m_projectionMatrix);
}

void PerspectiveCamera::adjustView(void)
{
	m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
	m_inverseViewMatrix = glm::inverse(m_viewMatrix);
}

void PerspectiveCamera::updateCameraVectors(void)
{
	// calculate and normalize the new forward vector
	m_forward.x = glm::cos(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
	m_forward.y = glm::sin(m_pitch);
	m_forward.z = glm::sin(glm::radians(m_yaw)) * glm::cos(glm::radians(m_pitch));
	m_forward = glm::normalize(m_forward);
	// calculate and normalize the new right vector
	m_right = glm::normalize(glm::cross(m_forward, m_wUp));
	// calculate and normalize the new up vector
	m_up = glm::normalize(glm::cross(m_right, m_forward));
}

float PerspectiveCamera::getYaw(void) const
{
	return m_yaw;
}

void PerspectiveCamera::setYaw(float yaw)
{
	m_yaw = yaw;
}

float PerspectiveCamera::getPitch(void) const
{
	return m_pitch;
}

void PerspectiveCamera::setPitch(float pitch)
{
	m_pitch = pitch;
}
