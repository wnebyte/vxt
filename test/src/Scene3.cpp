#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vxt/Window.hpp"
#include "vxt/PerspectiveCamera.hpp"

#include "vxt/io/Keyboard.hpp"

#include "vxt/rdr/Skybox.hpp"
#include "vxt/rdr/Shapes.hpp"
#include "vxt/rdr/BatchRenderer.hpp"

#include "vxt/ecs/Entity.hpp"
#include "vxt/cmp/FpsCamera.hpp"

#include "vxt/anim/ScaleAnimation.hpp"
#include "vxt/anim/RotateAnimation.hpp"
#include "vxt/anim/TranslateAnimation.hpp"

#include "Scene3.hpp"

using namespace vxt;
using namespace io;
using namespace rdr;
using namespace ecs;
using namespace cmp;
using namespace anim;
using namespace test;

static const glm::vec3 position{0.0f, 0.0f, 400.0f};
static const float zNear = 0.1f;
static const float zFar = 10000.0f;
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
		.setPos({0.5f, 0.0f, 0.0f})
		.setSize({1.0f, 1.0f, 1.0f})
		.setRotation(0.0f)
		.setColor({255.0f, 255.0f, 255.0f})
		.setWidth(4U)
		.build<Box3>();

	// initialize the base class, entities and components
	Scene::init();
}

void Scene3::update(float dt)
{
	Scene::update(dt);

	if (Keyboard::isKeyDown(GLFW_KEY_T)) {
		{
			std::shared_ptr<Animation> animation{std::make_shared<TranslateAnimation>(&box.pos, glm::vec3{0.0f, 10.0f, 0.0f})};
			animation->setDuration(5.0f);
			animation->setRepeatMode(Animation::REVERSE);
			animation->setRepeatCount(10);
			addAnimation(animation);
		}
		{
			std::shared_ptr<Animation> animation{std::make_shared<ScaleAnimation>(&box.size, glm::vec3{5.0f, 5.0f, 5.0f})};
			animation->setDuration(5.0f);
			animation->setRepeatMode(Animation::REVERSE);
			animation->setRepeatCount(10);
			addAnimation(animation);
		}
	}

	BatchRenderer::drawBox3(box);
	Skybox::render(*getCamera()); // draw skybox as first object in scene
	BatchRenderer::render(*getCamera());
}
