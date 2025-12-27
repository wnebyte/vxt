#include <glad/glad.h>

#include "utl/Assets.hpp"
#include "rdr/Shader.hpp"
#include "rdr/RenderUtil.hpp"
#include "rdr/ScreenRenderer.hpp"

#define SHADER_NAME "screen.glsl"

using namespace vxt;
using namespace rdr;
using namespace utl;

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

void ScreenRenderer::render(Texture *screenTexture)
{
	Shader *shader = Assets::getShader(SHADER_NAME);

	shader->attach();

	glActiveTexture(GL_TEXTURE0);
	screenTexture->bind();
	shader->uploadTexture(SHADER_U_SCREEN, 0);

	glBindVertexArray(vaoId);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(NO_ID);

	screenTexture->unbind();
	shader->detach();
}
