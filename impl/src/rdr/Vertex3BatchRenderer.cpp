#include <glad/glad.h>

#include "Camera.hpp"
#include "utl/Assets.hpp"
#include "rdr/Shader.hpp"
#include "rdr/RenderUtil.hpp"
#include "rdr/Vertex3BatchRenderer.hpp"

#define SHADER_NAME "vertex3.glsl"

using namespace vxt;
using namespace rdr;
using namespace utl;

static const int32_t texSlots[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

Vertex3BatchRenderer::Vertex3BatchRenderer()
	: m_vaoId(NO_ID)
	, m_vboId(NO_ID)
	, m_size(0)
	, m_data()
	, m_textures(ARRAY_SIZE(texSlots))
	, m_shader(Assets::getShader(SHADER_NAME))
{
}

void Vertex3BatchRenderer::init(void)
{
	// generate and bind a Vertex Array Object
	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);

	// allocate space for vertices
	glGenBuffers(1, &m_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_data), NULL, GL_DYNAMIC_DRAW);

	// enable the buffer attribute pointers
	setVertexAttributes({
		{ 3, GL_FLOAT, sizeof(GL_Vertex3), (void*)0 },
		{ 3, GL_FLOAT, sizeof(GL_Vertex3), (void*)offsetof(Vertex2, color) },
		{ 2, GL_FLOAT, sizeof(GL_Vertex3), (void*)offsetof(Vertex2, uv) },
		{ 1, GL_INT,   sizeof(GL_Vertex3), (void*)offsetof(Vertex2, texId) }
	});
}

void Vertex3BatchRenderer::render(const Camera &camera)
{
	uint32_t index = 0;

	// bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	// upload the vertex data to the GPU
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GL_Vertex3) * m_size, m_data);

	// draw the uploaded buffer
	m_shader->attach();
	m_shader->uploadMat4(SHADER_U_VIEW, camera.getViewMatrix());
	m_shader->uploadMat4(SHADER_U_PROJECTION, camera.getProjectionMatrix());
	m_textures.forEach([&index](const int32_t &texId) {
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, texId);
		++index;
	});
	m_shader->uploadIntArray(SHADER_U_TEXTURES, texSlots, ARRAY_SIZE(texSlots));

	// issue draw call
	glBindVertexArray(m_vaoId);
	glDrawArrays(GL_TRIANGLES, 0, m_size);
	glBindVertexArray(NO_ID);

	// reset batch for use on the next draw call
	m_size = 0;
	glBindTexture(GL_TEXTURE_2D, 0);
	m_shader->detach();
}

void Vertex3BatchRenderer::destroy(void)
{
	glDeleteBuffers(1, &m_vboId);
	glDeleteVertexArrays(1, &m_vaoId);
}

bool Vertex3BatchRenderer::add(const Vertex3 &vertex)
{
	if (atCapacity(vertex) == true) {
		return false;
	} else {
		m_data[m_size] = { vertex.pos, vertex.color, vertex.uv, m_textures.find(vertex.texId) };
		++m_size;
		return true;
	}
}

bool Vertex3BatchRenderer::atCapacity(const Vertex3 &vertex)
{
	return ((size() >= maxBatchSize) || (atTexCapacity(vertex.texId) == true));
}

bool Vertex3BatchRenderer::atTexCapacity(int32_t texId)
{
	return ((texId >= 0) && (m_textures.add(texId) == false));
}

std::size_t Vertex3BatchRenderer::size(void) const
{
	return m_size;
}
