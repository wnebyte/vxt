#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vxt/Window.hpp"
#include "vxt/PerspectiveCamera.hpp"

#include "vxt/rdr/Shapes.hpp"
#include "vxt/rdr/BatchRenderer.hpp"

#include "vxt/ecs/Entity.hpp"
#include "vxt/cmp/FpsCamera.hpp"

#include "Scene3.hpp"

using namespace vxt;
using namespace rdr;
using namespace ecs;
using namespace cmp;
using namespace test;

static const glm::vec3 position{0.0f, 0.0f, 0.0f};
static float zNear;
static float zFar;
static Box3 box;

Scene3::Scene3(Window *window)
	: Scene(window, std::make_unique<PerspectiveCamera>(position, zNear, zFar, window->getAspectRatio()))
{
	window->setCursorMode(GLFW_CURSOR_DISABLED);
}

void Scene3::init(void)
{
	Entity entity;

	entity.addComponent(std::make_shared<FpsCamera>());
	addEntity(entity);

	box = ShapeBuilder{}
		.setStart({0.0f, 0.0f, 0.0f})
		.setEnd({0.0f, 0.0f, 1.0f})
		.setColor({255.0f, 255.0f, 255.0f})
		.setWidth(4)
		.setRotation(0.0f)
		.build<Box3>();

	// initialize the base class
	Scene::init();
}

void Scene3::update(float dt)
{
	Scene::update(dt);
	BatchRenderer::drawBox3(box);
	BatchRenderer::render(*getCamera());
}
