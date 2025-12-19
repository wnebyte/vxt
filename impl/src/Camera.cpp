#include "Camera.hpp"

using namespace vxt;

Camera::Camera(const glm::vec3 &position,
			   float zNear,
			   float zFar,
			   float aspectRatio,
			   const glm::vec3 &forward,
			   const glm::vec3 &up,
			   const glm::vec3 &right)
	: m_position(position)
	, m_zNear(zNear)
	, m_zFar(zFar)
	, m_aspectRatio(aspectRatio)
	, m_zoom(VXT_CAMERA_DEFAULT_ZOOM)
	, m_forward(forward)
	, m_up(up)
	, m_right(right)
	, m_projectionMatrix()
	, m_inverseProjectionMatrix()
	, m_viewMatrix()
	, m_inverseViewMatrix()
{
}

void Camera::update(float dt)
{
	adjustProjection();
	adjustView();
}

void Camera::adjustProjection(void)
{
	// virtual
}

void Camera::adjustView(void)
{
	// virtual
}

float Camera::getZNear(void) const
{
	return m_zNear;
}

void Camera::setZNear(float zNear)
{
	m_zNear = zNear;
}

float Camera::getZFar(void) const
{
	return m_zFar;
}

void Camera::setZFar(float zFar)
{
	m_zFar = zFar;
}

float Camera::getAspectRatio(void) const
{
	return m_aspectRatio;
}

void Camera::setAspectRatio(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
}

float Camera::getZoom(void) const
{
	return m_zoom;
}

void Camera::setZoom(float zoom)
{
	m_zoom = zoom;
}

const glm::vec3& Camera::getForward(void) const
{
	return m_forward;
}

glm::vec3 Camera::getForward(void)
{
	return const_cast<glm::vec3&>(
		static_cast<const Camera*>(this)->getForward()
	);
}

void Camera::setForward(const glm::vec3 &forward)
{
	m_forward = forward;
}

const glm::vec3& Camera::getUp(void) const
{
	return m_up;
}

glm::vec3 Camera::getUp(void)
{
	return const_cast<glm::vec3&>(
		static_cast<const Camera*>(this)->getUp()
	);
}

void Camera::setUp(const glm::vec3 &up)
{
	m_up = up;
}

const glm::vec3& Camera::getRight(void) const
{
	return m_right;
}

glm::vec3 Camera::getRight(void)
{
	return const_cast<glm::vec3&>(
		static_cast<const Camera*>(this)->getRight()
	);
}

void Camera::setRight(const glm::vec3 &right)
{
	m_right = right;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
    return m_projectionMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
    return const_cast<glm::mat4&>(
		static_cast<const Camera*>(this)->getProjectionMatrix()
	);
}

const glm::mat4& Camera::getInverseProjectionMatrix() const
{
    return m_inverseProjectionMatrix;
}

glm::mat4 Camera::getInverseProjectionMatrix()
{
    return const_cast<glm::mat4&>(
		static_cast<const Camera*>(this)->getInverseProjectionMatrix()
	);
}

const glm::mat4& Camera::getViewMatrix() const
{
    return m_viewMatrix;
}

glm::mat4 Camera::getViewMatrix()
{
    return const_cast<glm::mat4&>(
		static_cast<const Camera*>(this)->getViewMatrix()
	);
}

const glm::mat4& Camera::getInverseViewMatrix() const
{
    return m_inverseViewMatrix;
}

glm::mat4 Camera::getInverseViewMatrix()
{
    return const_cast<glm::mat4&>(
		static_cast<const Camera*>(this)->getInverseViewMatrix()
	);
}

const glm::vec3& Camera::getPosition(void) const
{
	return m_position;
}

glm::vec3 Camera::getPosition(void)
{
	return const_cast<glm::vec3&>(
		static_cast<const Camera*>(this)->getPosition()
	);
}

void Camera::setPosition(const glm::vec3 &position)
{
	m_position = position;
}

void Camera::setPosition(const glm::vec2 &position)
{
	m_position = glm::vec3{position, m_position.z};
}

void Camera::add(const glm::vec3 &position)
{
	m_position += position;
}

void Camera::add(const glm::vec2 &position)
{
	m_position += glm::vec3{position, 0.0f};
}

void Camera::sub(const glm::vec3 &position)
{
	m_position -= position;
}

void Camera::sub(const glm::vec2 &position)
{
	m_position -= glm::vec3{position, 0.0f};
}

void Camera::mul(const glm::vec3 &position)
{
	m_position *= position;
}

void Camera::mul(const glm::vec2 &position)
{
	m_position *= glm::vec3{position, 0.0f};
}

void Camera::div(const glm::vec3 &position)
{
	m_position /= position;
}

void Camera::div(const glm::vec2 &position)
{
	m_position /= glm::vec3{position, 0.0f};
}

void Camera::setHints(uint32_t hints)
{
	m_hints = hints;
}
