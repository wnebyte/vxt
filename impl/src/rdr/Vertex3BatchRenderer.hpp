#ifndef VXT_VERTEX3_BATCH_RENDERER_HPP
#define VXT_VERTEX3_BATCH_RENDERER_HPP

#include "Types.hpp"
#include "Camerafwd.hpp"
#include "rdr/Shapes.hpp"
#include "rdr/Renderer.hpp"
#include "rdr/Shaderfwd.hpp"
#include "utl/CapacitySet.hpp"

namespace vxt {
namespace rdr
{
class Vertex3BatchRenderer : public Renderer {
public:
	static const uint32_t maxBatchSize = 4000;

public:
	Vertex3BatchRenderer();
	virtual ~Vertex3BatchRenderer() noexcept = default;

public:
	void init(void);
	bool add(const Vertex3 &vertex);
	void render(const Camera &camera) override;
	void destroy(void) override;
	std::size_t size(void) const;

private:
	bool atCapacity(const Vertex3 &vertex);
	bool atTexCapacity(int32_t texId);

private:
	uint32_t m_vaoId;
	uint32_t m_vboId;
	std::size_t m_size;
	GL_Vertex3 m_data[maxBatchSize];
	utl::CapacitySet<int32_t> m_textures;
	Shader *m_shader;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_VERTEX3_BATCH_RENDERER_HPP
