#include "OrthoCamera.hpp"

using namespace vxt;

OrthoCamera::OrthoCamera(const glm::vec3 &position,
						 float zNear,
						 float zFar,
						 float aspectRatio,
						 float projectionWidth,
						 float projectionHeight,
						 const glm::vec3 &foward,
						 const glm::vec3 &up,
						 const glm::vec3 &right)
	: Camera(position, zNear, zFar, aspectRatio, foward, up, right)
	, m_projectionSize(projectionWidth, projectionHeight)
{
}

void OrthoCamera::adjustProjection(void)
{
	m_projectionMatrix = glm::ortho(0.0f, m_projectionSize.x * m_zoom, 0.0f, m_projectionSize.y * m_zoom, m_zNear, m_zFar);
	m_inverseProjectionMatrix = glm::inverse(m_projectionMatrix);
}

void OrthoCamera::adjustView(void)
{
	m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
	m_inverseViewMatrix = glm::inverse(m_viewMatrix);
}

float OrthoCamera::getProjectionWidth(void) const
{
	return m_projectionSize.x;;
}

void OrthoCamera::setProjectionWidth(float projectionWidth)
{
	m_projectionSize.x = projectionWidth;
}

float OrthoCamera::getProjectionHeight(void) const
{
	return m_projectionSize.y;
}

void OrthoCamera::setProjectionHeight(float projectionHeight)
{
	m_projectionSize.y = projectionHeight;
}

const glm::vec2& OrthoCamera::getProjectionSize(void) const
{
	return m_projectionSize;
}

glm::vec2 OrthoCamera::getProjectionSize(void)
{
	return const_cast<glm::vec2&>(
		static_cast<const OrthoCamera*>(this)->getProjectionSize()
	);
}
