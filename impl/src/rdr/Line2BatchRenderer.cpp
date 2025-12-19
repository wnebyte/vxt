#include <glad/glad.h>

#include "Camera.hpp"
#include "utl/Assets.hpp"
#include "rdr/Shader.hpp"
#include "rdr/RenderUtil.hpp"
#include "rdr/Line2BatchRenderer.hpp"

using namespace vxt;
using namespace rdr;
using namespace utl;

#define SHADER_NAME "line2.glsl"

Line2BatchRenderer::Line2BatchRenderer(int32_t zIndex, uint32_t width)
	: m_vaoId(NO_ID)
	, m_vboId(NO_ID)
	, m_size(0)
	, m_data()
	, m_shader(Assets::getShader(SHADER_NAME))
	, m_zIndex(zIndex)
	, m_width(width)
{
}

void Line2BatchRenderer::init(void)
{
	// generate and bind a Vertex Array Object
	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);

	// allocate space for lines
	glGenBuffers(1, &m_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_data), NULL, GL_DYNAMIC_DRAW);

	// enable the buffer attribute pointers
	setVertexAttributes({
		{ 2, GL_FLOAT, sizeof(GL_Line2), (void*)0 },
		{ 3, GL_FLOAT, sizeof(GL_Line2), (void*)offsetof(GL_Line2, color) }
	});
}

void Line2BatchRenderer::render(const Camera &camera)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GL_Line2) * m_size, m_data);

	m_shader->attach();
	m_shader->uploadInt(SHADER_U_ZINDEX, m_zIndex);
	m_shader->uploadBool(SHADER_U_IS_WORLD_SPACE, true);
	m_shader->uploadMat4(SHADER_U_VIEW, camera.getViewMatrix());
	m_shader->uploadMat4(SHADER_U_PROJECTION, camera.getProjectionMatrix());

	glBindVertexArray(m_vaoId);
	glDrawArrays(GL_LINES, 0, m_size);
	glBindVertexArray(NO_ID);

	// reset batch for use on the next draw call
	m_size = 0;
	m_shader->detach();
}

void Line2BatchRenderer::destroy(void)
{
	glDeleteBuffers(1, &m_vboId);
	glDeleteVertexArrays(1, &m_vaoId);
}

bool Line2BatchRenderer::add(const Line2 &line)
{
	if ((size() <= (maxBatchSize - 2)) && (line.zIndex == m_zIndex) && (line.width == m_width)) {
		for (uint32_t i = 0; i < 2; ++i) {
			m_data[m_size].pos = (i == 0) ? line.start : line.end;
			m_data[m_size].color = line.color;
			++m_size;
		}
		return true;
	}
	return false;
}

int32_t Line2BatchRenderer::zIndex(void) const
{
	return m_zIndex;
}

std::size_t Line2BatchRenderer::size(void) const
{
	return m_size;
}
