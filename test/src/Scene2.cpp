#include "vxt/Window.hpp"
#include "vxt/Application.hpp"

#include "vxt/OrthoCamera.hpp"

#include "vxt/rdr/Shapes.hpp"
#include "vxt/rdr/BatchRenderer.hpp"

#include "vxt/utl/Assets.hpp"

#include "vxt/cmp/Transform.hpp"
#include "vxt/cmp/GridLines.hpp"
#include "vxt/cmp/EditorCamera.hpp"
#include "vxt/cmp/SpriteRender.hpp"

#include "Scene2.hpp"

#define TEXTURE_NAME "blocks/dark_oak_log.png"

using namespace vxt;
using namespace rdr;
using namespace utl;
using namespace ecs;
using namespace cmp;
using namespace test;

static const glm::vec3 position{0.0f, 0.0f, 20.0f};
static const float zNear = 0.0f;
static const float zFar = 100.0f;
static const float projectionWidth = 6.0f;
static const float projectionHeight = 3.0f;
static Quad2 quad;

Scene2::Scene2(Window *window)
	: Scene(window, std::make_unique<OrthoCamera>(position, zNear, zFar, window->getAspectRatio(), projectionWidth, projectionHeight))
{
}

void Scene2::init(void)
{
	Entity         entity;
	ShapeBuilder   builder;

	entity.addComponent(std::make_shared<GridLines>());
	entity.addComponent(std::make_shared<EditorCamera>());
	addEntity(entity);

	quad = builder.setPos({0.0f, 0.0f})
		.setZIndex(10)
		.setSize({1.0f, 1.0f})
		.setScale(1.0f)
		.setColor({1.0f, 1.0f, 1.0f})
		.setTexId(Assets::getTexture(TEXTURE_NAME)->getId())
		.setBlend(false)
		.build<Quad2>();

	// components need to have been initialized when spr batches are added
	Scene::init();
}

void Scene2::update(float dt)
{
	BatchRenderer::drawQuad2(quad);
	Scene::update(dt);
	BatchRenderer::render(*getCamera());
}
