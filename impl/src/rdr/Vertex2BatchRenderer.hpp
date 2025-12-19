#ifndef VXT_VERTEX2_BATCH_RENDERER_HPP
#define VXT_VERTEX2_BATCH_RENDERER_HPP

#include "Types.hpp"
#include "Camerafwd.hpp"
#include "rdr/Shapes.hpp"
#include "rdr/Renderer.hpp"
#include "rdr/Shaderfwd.hpp"
#include "utl/CapacitySet.hpp"

namespace vxt {
namespace rdr
{
class Vertex2BatchRenderer : public Renderer {
public:
	static const uint32_t maxBatchSize = 4000;

public:
	Vertex2BatchRenderer(int32_t zIndex, bool blend);
	virtual ~Vertex2BatchRenderer() noexcept = default;

public:
	void init(void);
	bool add(const Vertex2 &vertex);
	void render(const Camera &camera) override;
	void destroy(void) override;
	int32_t zIndex(void) const override;
	std::size_t size(void) const;

private:
	bool atCapacity(const Vertex2 &vertex);
	bool atTexCapacity(int32_t texId);

private:
	uint32_t m_vaoId;
	uint32_t m_vboId;
	std::size_t m_size;
	GL_Vertex2 m_data[maxBatchSize];
	utl::CapacitySet<int32_t> m_textures;
	Shader *m_shader;
	int32_t m_zIndex;
	bool m_blend;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_VERTEX2_BATCH_RENDERER_HPP
