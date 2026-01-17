#include <algorithm>

#include "rdr/BatchRenderer.hpp"

using namespace vxt;
using namespace rdr;
using namespace utl;
using namespace ecs;
using namespace cmp;

std::vector<Renderer*> BatchRenderer::m_batches;
std::deque<Line2BatchRenderer> BatchRenderer::m_line2Batches;
std::deque<Line3BatchRenderer> BatchRenderer::m_line3Batches;
std::deque<SpriteBatchRenderer> BatchRenderer::m_spriteBatches;
std::deque<Vertex2BatchRenderer> BatchRenderer::m_vertex2Batches;
std::deque<Vertex3BatchRenderer> BatchRenderer::m_vertex3Batches;

void BatchRenderer::drawLine2(const Line2 &line)
{
	// try to find an existing batch
	for (auto &batch : m_line2Batches) {
		if (batch.add(line)) {
			// line was added into an existing batch
			return;
		}
	}
	{
		// create a new batch
		Line2BatchRenderer *batch;
		m_line2Batches.push_back(Line2BatchRenderer{line.zIndex, line.width});
		batch = &(m_line2Batches.back());
		m_batches.push_back(batch);

		batch->init();
		batch->add(line);
	}
}

void BatchRenderer::drawLine3(const Line3 &line)
{
	// try to find an existing batch
	for (auto &batch : m_line3Batches) {
		if (batch.add(line)) {
			// line was added into an existing batch
			return;
		}
	}
	{
		// create a new batch
		Line3BatchRenderer *batch;
		m_line3Batches.push_back(Line3BatchRenderer{line.width});
		batch = &(m_line3Batches.back());
		m_batches.push_back(batch);

		batch->init();
		batch->add(line);
	}
}

void BatchRenderer::drawVertex2(const Vertex2 &vertex)
{
	// try to find an existing batch
	for (auto &batch : m_vertex2Batches) {
		if (batch.add(vertex)) {
			// vertex was added into an existing batch
			return;
		}
	}
	{
		// create a new batch
		Vertex2BatchRenderer *batch;
		m_vertex2Batches.push_back(Vertex2BatchRenderer{vertex.zIndex, vertex.blend});
		batch = &(m_vertex2Batches.back());
		m_batches.push_back(batch);

		batch->init();
		batch->add(vertex);
	}
}

void BatchRenderer::drawVertex3(const Vertex3 &vertex)
{
	// try to find an existing batch
	for (auto &batch : m_vertex3Batches) {
		if (batch.add(vertex)) {
			// vertex was added into an existing batch
			return;
		}
	}
	{
		// create a new batch
		Vertex3BatchRenderer *batch;
		m_vertex3Batches.push_back(Vertex3BatchRenderer{});
		batch = &(m_vertex3Batches.back());
		m_batches.push_back(batch);

		batch->init();
		batch->add(vertex);
	}
}

void BatchRenderer::addSpr(SpriteRender *spr)
{
	// try to find an existing batch
	for (auto &batch : m_spriteBatches) {
		if (batch.add(spr)) {
			// spr was added into an existing batch
			return;
		}
	}
	{
		// create a new batch
		SpriteBatchRenderer *batch;
		m_spriteBatches.push_back(SpriteBatchRenderer{});
		batch = &(m_spriteBatches.back());
		m_batches.push_back(batch);

		batch->init();
		batch->add(spr);
	}
}

void BatchRenderer::drawBox2(const Box2 &box)
{
	const glm::vec2 min = box.pos - (box.size * 0.5f);
	const glm::vec2 max = box.pos + (box.size * 0.5f);
	glm::vec2 v[4] = {
		{ min.x, min.y },
		{ min.x, max.y },
		{ max.x, max.y },
		{ max.x, min.y }
	};

	if (box.rotation != 0.0f) {
		for (glm::vec2 &vertex : v) {
			ufw::math::rotate(vertex, box.rotation, box.pos);
		}
	}

	drawLine2({v[0], v[1], box.zIndex, box.color, box.width});
	drawLine2({v[0], v[3], box.zIndex, box.color, box.width});
	drawLine2({v[1], v[2], box.zIndex, box.color, box.width});
	drawLine2({v[2], v[3], box.zIndex, box.color, box.width});
}

void BatchRenderer::drawBox3(const Box3 &box)
{
	const glm::vec3 min = box.pos - (box.size * 0.5f);
	const glm::vec3 max = box.pos + (box.size * 0.5f);
	glm::vec3 v[8] = {
		{ min.x, max.y, max.z },
		{ max.x, max.y, max.z },
		{ min.x, min.y, max.z },
		{ max.x, min.y, max.z },
		{ min.x, max.y, min.z },
		{ max.x, max.y, min.z },
		{ min.x, min.y, min.z },
		{ max.x, min.y, min.z }
	};

	if (box.rotation != 0.0f) {
		for (glm::vec3 &vertex : v) {
			ufw::math::rotate(vertex, box.rotation, box.pos);
		}
	}

	// FRONT
	drawLine3({v[0], v[1], box.color, box.width});
	drawLine3({v[1], v[3], box.color, box.width});
	drawLine3({v[3], v[2], box.color, box.width});
	drawLine3({v[2], v[0], box.color, box.width});
	// BACK
	drawLine3({v[4], v[5], box.color, box.width});
	drawLine3({v[5], v[7], box.color, box.width});
	drawLine3({v[7], v[6], box.color, box.width});
	drawLine3({v[6], v[4], box.color, box.width});
	// LEFT
	drawLine3({v[0], v[2], box.color, box.width});
	drawLine3({v[2], v[6], box.color, box.width});
	drawLine3({v[6], v[4], box.color, box.width});
	drawLine3({v[4], v[0], box.color, box.width});
	// RIGHT
	drawLine3({v[1], v[5], box.color, box.width});
	drawLine3({v[5], v[7], box.color, box.width});
	drawLine3({v[7], v[3], box.color, box.width});
	drawLine3({v[3], v[1], box.color, box.width});
	// TOP
	drawLine3({v[0], v[4], box.color, box.width});
	drawLine3({v[4], v[5], box.color, box.width});
	drawLine3({v[5], v[1], box.color, box.width});
	drawLine3({v[1], v[0], box.color, box.width});
	// BOTTOM
	drawLine3({v[2], v[6], box.color, box.width});
	drawLine3({v[6], v[7], box.color, box.width});
	drawLine3({v[7], v[3], box.color, box.width});
	drawLine3({v[3], v[2], box.color, box.width});
}

// v2 --------- v1    Axis orientation
// |            |     y
// |            |     |
// |            |     +--- x
// |            |  
// v3 --------- v0

void BatchRenderer::drawQuad2(const Quad2 &quad)
{
	const float x0 = quad.pos.x;
	const float y0 = quad.pos.y;
	const float x1 = quad.pos.x + (quad.size.x * quad.scale);
	const float y1 = quad.pos.y + (quad.size.y * quad.scale);
	static const glm::vec2 uvs[4] = { {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 1.0f} };
	const Vertex2 v[4] = {
		{ { x1, y0 }, quad.zIndex, quad.color, uvs[0], quad.texId, quad.blend },
		{ { x1, y1 }, quad.zIndex, quad.color, uvs[1], quad.texId, quad.blend },
		{ { x0, y1 }, quad.zIndex, quad.color, uvs[2], quad.texId, quad.blend },
		{ { x0, y0 }, quad.zIndex, quad.color, uvs[3], quad.texId, quad.blend }
	};

	for (const Vertex2 &vertex : v) {
		drawVertex2(vertex);
	}
}

//   v4 ----------- v5
//   /|            /|      Axis orientation
//  / |           / |
// v0 --------- v1  |      y
// |  |         |   |      |
// |  v6 -------|-- v7     +--- x
// | /          |  /      /
// |/           | /      z
// v2 --------- v3

void BatchRenderer::drawCube3(const Cube3 &cube)
{
	/// TODO: impl
}

void BatchRenderer::drawCrossHair(const CrossHair &ch)
{
	const glm::vec2 halfSize = ch.size * 0.5f;
	const int32_t zIndex = 0;  // TODO: add to CrossHair struct
	const uint32_t width = 4U; // TODO: add to CrossHair struct

	const Line2 v[2] = {
		{ { ch.pos.x, ch.pos.y - halfSize.y }, { ch.pos.x, ch.pos.y + halfSize.y }, zIndex, ch.color, width },
		{ { ch.pos.x - halfSize.x, ch.pos.y }, { ch.pos.x + halfSize.x, ch.pos.y }, zIndex, ch.color, width }
	};

	for (const Line2 &line : v) {
		drawLine2(line);
	}
}

void BatchRenderer::add(Entity &entity)
{
	SpriteRender *spr = entity.getComponent<SpriteRender>();

	if (spr != NULL) {
		addSpr(spr);
	}
}

void BatchRenderer::render(const Camera &camera)
{
	if (!m_batches.empty()) {
		// strange stuff happens when m_batches is sorted directly
		std::vector<Renderer*> batches{m_batches.begin(), m_batches.end()};

		std::sort(batches.begin(), batches.end(), &Renderer::compareTo);

		for (Renderer *batch : batches) {
			batch->render(camera);
		}
	}
}

void BatchRenderer::destroy(void)
{
	for (Renderer *batch : m_batches) {
		batch->destroy();
	}
	m_batches.clear();
	m_line2Batches.clear();
	m_line3Batches.clear();
	m_spriteBatches.clear();
	m_vertex2Batches.clear();
	m_vertex3Batches.clear();
}
