#include "Window.hpp"
#include "Camera.hpp"
#include "Application.hpp"
#include "utl/Transformation.hpp"

namespace vxt {
namespace utl
{
glm::vec2 viewSpaceToWorldSpace(const Camera *camera, const glm::vec2 &pos)
{
	glm::vec4 tmp{pos.x, pos.y, 0.0f, 1.0f};

	tmp = tmp * camera->getInverseViewMatrix();

	return glm::vec2{tmp};
}

glm::vec2 ndcToViewSpace(const Camera *camera, const glm::vec2 &pos)
{
	glm::vec4 tmp{pos.x, pos.y, 0.0f, 1.0f};

	tmp = tmp * camera->getInverseProjectionMatrix();

	return glm::vec2{tmp};
}

glm::vec2 screenSpaceToNdc(const Camera *camera, const glm::vec2 &pos)
{
	float x;
	float y;

	// screen space to ndc
	x = ((pos.x / Application::getWindow()->getWidth()) * 2.0f) - 1.0f;
	y = -(((pos.y / Application::getWindow()->getHeight()) * 2.0f) - 1.0f);

	return glm::vec2{x, y};
}
} // namespace utl
} // namespace vxt
