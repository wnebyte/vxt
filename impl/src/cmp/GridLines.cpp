#include "Scene.hpp"
#include "utl/Env.hpp"
#include "OrthoCamera.hpp"
#include "cmp/GridLines.hpp"
#include "rdr/BatchRenderer.hpp"

#define GRID_WIDTH 0.25f
#define GRID_HEIGHT 0.25f

using namespace vxt;
using namespace rdr;
using namespace cmp;

GridLines::GridLines()
{
}

void GridLines::init(Scene *scene)
{
	Component::init(scene);
}

void GridLines::update(float dt)
{
	UFW_ASSERT((m_scene != NULL) && ("scene is NULL"));
	const OrthoCamera *camera = dynamic_cast<const OrthoCamera*>(m_scene->getCamera());
	const glm::vec2 pos{camera->getPosition()};
	const glm::vec2 projectionSize{camera->getProjectionSize()};
	const float zoom = camera->getZoom();
	float firstX, firstY;
	uint numVtLines, numHzLines;
	float width, height;
	static const glm::vec3 lineColor{0.2f, 0.2f, 0.2f};
	static const uint32_t lineWidth = 4U;
	static const int32_t lineZIndex = 20;

	{
		firstX = ((int)(pos.x / GRID_WIDTH)) * GRID_WIDTH;
		firstY = ((int)(pos.y / GRID_HEIGHT)) * GRID_HEIGHT;
	}

	{
		numVtLines = ((uint)((projectionSize.x * zoom) / GRID_WIDTH) + 2);
		numHzLines = ((uint)((projectionSize.y * zoom) / GRID_HEIGHT) + 2);
	}

	{
		width  = ((uint)(projectionSize.x * zoom) + (GRID_WIDTH * 5));
		height = ((uint)(projectionSize.y * zoom) + (GRID_HEIGHT * 5));
	}

	for (uint i = 0; i < std::max(numVtLines, numHzLines); ++i) {
		float x = firstX + (GRID_WIDTH * i);
		float y = firstY + (GRID_HEIGHT * i);

		if (i < numVtLines) {
			BatchRenderer::drawLine2({{x, firstY}, {x, firstY + height}, lineZIndex, lineColor, lineWidth});
		}
		if (i < numHzLines) {
			BatchRenderer::drawLine2({{firstX, y}, {firstX + width, y}, lineZIndex, lineColor, lineWidth});
		}
	}
}
