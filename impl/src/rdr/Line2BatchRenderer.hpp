#ifndef VXT_LINE2_BATCH_RENDERER_HPP
#define VXT_LINE2_BATCH_RENDERER_HPP

#include "Types.hpp"
#include "Camerafwd.hpp"
#include "rdr/Shapes.hpp"
#include "rdr/Renderer.hpp"
#include "rdr/Shaderfwd.hpp"

namespace vxt {
namespace rdr
{
class Line2BatchRenderer : public Renderer {
public:
	static const uint32_t maxBatchSize = 1000;

public:
	Line2BatchRenderer(int32_t zIndex, uint32_t width);
	virtual ~Line2BatchRenderer() noexcept = default;

public:
	void init(void);
	bool add(const Line2 &line);
	void render(const Camera &camera) override;
	void destroy(void) override;
	int32_t zIndex(void) const override;
	std::size_t size(void) const;

private:
	uint32_t    m_vaoId;
	uint32_t    m_vboId;
	std::size_t m_size;
	GL_Line2    m_data[maxBatchSize];
	Shader     *m_shader;
	int32_t     m_zIndex;
	uint32_t    m_width;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_LINE2_BATCH_RENDERER_HPP
