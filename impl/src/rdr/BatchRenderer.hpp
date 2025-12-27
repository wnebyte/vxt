#ifndef VXT_BATCH_RENDERER_HPP
#define VXT_BATCH_RENDERER_HPP

#include <deque>
#include <vector>

#include "Types.hpp"
#include "Camerafwd.hpp"
#include "ecs/Entity.hpp"
#include "rdr/Shapes.hpp"
#include "rdr/Renderer.hpp"
#include "cmp/SpriteRender.hpp"
#include "rdr/Line2BatchRenderer.hpp"
#include "rdr/Line3BatchRenderer.hpp"
#include "rdr/SpriteBatchRenderer.hpp"
#include "rdr/Vertex2BatchRenderer.hpp"
#include "rdr/Vertex3BatchRenderer.hpp"

namespace vxt {
namespace rdr
{
class BatchRenderer {
public:
	static void drawLine2(const Line2 &line);
	static void drawLine3(const Line3 &line);

	static void drawVertex2(const Vertex2 &vertex);
	static void drawVertex3(const Vertex3 &vertex);

	static void drawBox2(const Box2 &box);
	static void drawBox3(const Box3 &box);

	static void drawQuad2(const Quad2 &quad);

	static void drawCube3(const Cube3 &cube);

	static void drawCrossHair(const CrossHair &ch);

	static void add(ecs::Entity &entity);

	static void render(const Camera &camera);
	static void destroy(void);

private:
	static void addSpr(cmp::SpriteRender *spr);

private:
	static std::vector<Renderer*> m_batches;
	static std::deque<Line2BatchRenderer> m_line2Batches;
	static std::deque<Line3BatchRenderer> m_line3Batches;
	static std::deque<SpriteBatchRenderer> m_spriteBatches;
	static std::deque<Vertex2BatchRenderer> m_vertex2Batches;
	static std::deque<Vertex3BatchRenderer> m_vertex3Batches;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_BATCH_RENDERER_HPP
