#ifndef VXT_LINE3_BATCH_RENDERER_HPP
#define VXT_LINE3_BATCH_RENDERER_HPP

#include "Types.hpp"
#include "Camerafwd.hpp"
#include "rdr/Shapes.hpp"
#include "rdr/Renderer.hpp"
#include "rdr/Shaderfwd.hpp"

namespace vxt {
namespace rdr
{
class Line3BatchRenderer : public Renderer {
public:
	static const uint32_t maxBatchSize = 4000;

public:
	Line3BatchRenderer(uint32_t width);
	virtual ~Line3BatchRenderer() noexcept = default;

public:
	void init(void);
	bool add(const Line3 &line);
	void render(const Camera &camera) override;
	void destroy(void) override;
	std::size_t size(void) const;

private:
	uint32_t    m_vaoId;
	uint32_t    m_vboId;
	std::size_t m_size;
	GL_Line3    m_data[maxBatchSize];
	Shader     *m_shader;
	uint32_t    m_width;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_LINE3_BATCH_RENDERER_HPP
