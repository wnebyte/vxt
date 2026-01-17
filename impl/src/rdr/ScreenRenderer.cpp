#include <glad/glad.h>

#include "rdr/RenderUtil.hpp"
#include "rdr/ScreenRenderer.hpp"

using namespace vxt;
using namespace rdr;

struct Vertex {
	glm::vec3 pos;
	glm::vec2 uv;
};

static uint32_t vaoId = NO_ID;

static uint32_t vboId = NO_ID;

static Vertex data[] = {
	{ {-1.0f, -1.0f, 0.0f }, { 0.0f,  0.0f } },
	{ { 1.0f, -1.0f, 0.0f }, { 1.0f,  0.0f } },
	{ { 1.0f,  1.0f, 0.0f }, { 1.0f,  1.0f } },
	{ { 1.0f,  1.0f, 0.0f }, { 1.0f,  1.0f } },
	{ {-1.0f,  1.0f, 0.0f }, { 0.0f,  1.0f } },
	{ {-1.0f, -1.0f, 0.0f }, { 0.0f,  0.0f } }
};

void ScreenRenderer::init(void)
{
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	setVertexAttributes({
		{ 3, GL_FLOAT, sizeof(Vertex), (void*)0 },
		{ 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, uv) }
	});
}

void ScreenRenderer::render(void)
{
	glBindVertexArray(vaoId);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(NO_ID);
}
