#include <glad/glad.h>

#include "Camera.hpp"
#include "utl/Assets.hpp"
#include "rdr/Shader.hpp"
#include "rdr/RenderUtil.hpp"
#include "rdr/Line3BatchRenderer.hpp"

using namespace vxt;
using namespace rdr;
using namespace utl;

#define SHADER_NAME "line3.glsl"

Line3BatchRenderer::Line3BatchRenderer(uint32_t width)
	: m_vaoId(NO_ID)
	, m_vboId(NO_ID)
	, m_size(0)
	, m_data()
	, m_shader(Assets::getShader(SHADER_NAME))
	, m_width(width)
{
}

void Line3BatchRenderer::init(void)
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
		{ 3, GL_FLOAT, sizeof(GL_Line3), (void*)0 },
		{ 3, GL_FLOAT, sizeof(GL_Line3), (void*)offsetof(GL_Line2, color) }
	});
}

void Line3BatchRenderer::render(const Camera &camera)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GL_Line3) * m_size, m_data);

	m_shader->attach();
	m_shader->uploadMat4(SHADER_U_VIEW, camera.getViewMatrix());
	m_shader->uploadMat4(SHADER_U_PROJECTION, camera.getProjectionMatrix());

	glLineWidth(m_width);

	glBindVertexArray(m_vaoId);
	glDrawArrays(GL_LINES, 0, m_size);
	glBindVertexArray(NO_ID);

	// reset batch for use on the next draw call
	m_size = 0;
	m_shader->detach();
}

void Line3BatchRenderer::destroy(void)
{
	glDeleteBuffers(1, &m_vboId);
	glDeleteVertexArrays(1, &m_vaoId);
}

bool Line3BatchRenderer::add(const Line3 &line)
{
	if ((size() <= (maxBatchSize - 2)) && (line.width == m_width)) {
		for (uint32_t i = 0; i < 2; ++i) {
			m_data[m_size].pos = (i == 0) ? line.start : line.end;
			m_data[m_size].color = line.color;
			++m_size;
		}
		return true;
	}
	return false;
}

std::size_t Line3BatchRenderer::size(void) const
{
	return m_size;
}
