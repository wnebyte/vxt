#include <glad/glad.h>

#include "Camera.hpp"
#include "utl/Assets.hpp"
#include "rdr/Shader.hpp"
#include "rdr/RenderUtil.hpp"
#include "rdr/Vertex2BatchRenderer.hpp"

#define TRACE
#define SHADER_NAME "vertex2.glsl"

using namespace vxt;
using namespace rdr;
using namespace utl;

// GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
static const int32_t texSlots[8] = {0, 1, 2, 3, 4, 5, 6, 7};

Vertex2BatchRenderer::Vertex2BatchRenderer(int32_t zIndex, bool blend)
	: m_vaoId(NO_ID)
	, m_vboId(NO_ID)
	, m_size(0)
	, m_data()
	, m_textures(ARRAY_SIZE(texSlots))
	, m_shader(Assets::getShader(SHADER_NAME))
	, m_zIndex(zIndex)
	, m_blend(blend)
{
}

void Vertex2BatchRenderer::init(void)
{
	uint32_t eboId;
	uint32_t indices[maxBatchSize * 3];

	// generate and bind a Vertex Array Object
	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);

	// allocate space for vertices
	glGenBuffers(1, &m_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_data), NULL, GL_DYNAMIC_DRAW);

	// create and upload the indices buffer
	glGenBuffers(1, &eboId);
	genIndices(indices, ARRAY_SIZE(indices));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// enable the buffer attribute pointers
	setVertexAttributes({
		{ 2, GL_FLOAT, sizeof(GL_Vertex2), (void*)0 },
		{ 3, GL_FLOAT, sizeof(GL_Vertex2), (void*)offsetof(GL_Vertex2, color) },
		{ 2, GL_FLOAT, sizeof(GL_Vertex2), (void*)offsetof(GL_Vertex2, uv) },
		{ 1, GL_INT,   sizeof(GL_Vertex2), (void*)offsetof(GL_Vertex2, texId) }
	});
}

void Vertex2BatchRenderer::render(const Camera &camera)
{
	uint32_t index = 0;

	// bind the vbo
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	// upload the vertex data to the GPU
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_data), m_data);

	// draw the uploaded buffer
	m_shader->attach();
	m_shader->uploadInt(SHADER_U_ZINDEX, m_zIndex);
	m_shader->uploadMat4(SHADER_U_VIEW, camera.getViewMatrix());
	m_shader->uploadMat4(SHADER_U_PROJECTION, camera.getProjectionMatrix());
	m_textures.forEach([&index](const int32_t &texId) {
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, texId);
		++index;
	});
	m_shader->uploadIntArray(SHADER_U_TEXTURES, texSlots, ARRAY_SIZE(texSlots));

	// set render states
	if (m_blend) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	// issue draw call
	glBindVertexArray(m_vaoId);
	glDrawElements(GL_TRIANGLES, m_size + (m_size / 2), GL_UNSIGNED_INT, NULL);
	glBindVertexArray(NO_ID);

	// reset render states
	if (m_blend) {
		glDisable(GL_BLEND);
	}

	// reset batch for use on the next draw call
	m_size = 0;
	glBindTexture(GL_TEXTURE_2D, 0);
	m_shader->detach();
}

void Vertex2BatchRenderer::destroy(void)
{
	glDeleteBuffers(1, &m_vboId);
	glDeleteVertexArrays(1, &m_vaoId);
}

bool Vertex2BatchRenderer::add(const Vertex2 &vertex)
{
	bool rv = false;

	if ((vertex.zIndex == m_zIndex) && (vertex.blend == m_blend) && (atCapacity(vertex) == false)) {
		m_data[m_size] = { vertex.pos, vertex.color, vertex.uv, m_textures.find(vertex.texId) };
		++m_size;
		rv = true;
	}

	return rv;
}

bool Vertex2BatchRenderer::atCapacity(const Vertex2 &vertex)
{
	return ((size() >= maxBatchSize) || (atTexCapacity(vertex.texId)));
}

bool Vertex2BatchRenderer::atTexCapacity(int32_t texId)
{
	bool rv = true;

	if (texId > NO_TEX_ID) {
		if (m_textures.add(texId)) {
			rv = false; // tex id already has been added or was successfully added
		}
	}

	return rv;
}

int32_t Vertex2BatchRenderer::zIndex(void) const
{
	return m_zIndex;
}

std::size_t Vertex2BatchRenderer::size(void) const
{
	return m_size;
}
