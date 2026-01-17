#include "Application.hpp"

#include "rdr/Shader.hpp"
#include "rdr/RenderUtil.hpp"
#include "rdr/Framebuffer.hpp"
#include "rdr/ChunkRenderer.hpp"
#include "rdr/ScreenRenderer.hpp"

#include "utl/Assets.hpp"
#include "utl/Constants.hpp"

#define VERTEX_CAPACITY 10000

#define TEXTURE_NAME "texture3"
#define OPAQUE_SHADER_NAME "opaque.glsl"
#define TRANSPARENT_SHADER_NAME "transparent.glsl"
#define BLENDABLE_SHADER_NAME "blendable.glsl"
#define COMPOSITE_SHADER_NAME "composite.glsl"

using namespace vxt;
using namespace rdr;
using namespace utl;

ChunkRenderer::ChunkRenderer()
	: m_vaoId(NO_ID)
	, m_vboId(NO_ID)
	, m_ccboId(NO_ID)
	, m_texture(Assets::getTexture(TEXTURE_NAME))
	, m_opaqueShader(Assets::getShader(OPAQUE_SHADER_NAME))
	, m_transparentShader(Assets::getShader(TRANSPARENT_SHADER_NAME))
	, m_blendableShader(Assets::getShader(BLENDABLE_SHADER_NAME))
	, m_opaqueDrawCommands()
	, m_transparentDrawCommands()
	, m_blendableDrawCommands()
	, m_chunkCoords()
{
}

void ChunkRenderer::init(void)
{
	GLsizeiptr     size;
	GLsizeiptr     subchunkSize;
	GLbitfield     flags;
	uint8_t       *buffer;

	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);

	glGenBuffers(1, &m_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);

	setVertexAttributes({
		{ 1, GL_UNSIGNED_INT, sizeof(GLuint), (void*)0 }
	});

	size = SUBCHUNK_CAPACITY * (VERTEX_CAPACITY * sizeof(GLuint));
	subchunkSize = size / SUBCHUNK_CAPACITY;
	flags = GL_MAP_PERSISTENT_BIT | GL_MAP_WRITE_BIT | GL_MAP_COHERENT_BIT;

	glBufferStorage(GL_ARRAY_BUFFER, size, NULL, flags);
	buffer = static_cast<uint8_t*>( glMapBufferRange(GL_ARRAY_BUFFER, 0, size, flags) );

	for (uint offset = 0, i = 0; (offset <= (size - subchunkSize)) && (i < SUBCHUNK_CAPACITY); offset += subchunkSize, ++i) {
		uint8_t *subBuffer = &(buffer[offset]);
		// init subchunk
	}

	// generate and allocate space for chunk coordinate buffer object
	glGenBuffers(1, &m_ccboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_ccboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_chunkCoords), NULL, GL_DYNAMIC_DRAW);

	setVertexAttributes({
		{ 2, GL_INT, sizeof(glm::ivec2), (void*)0 }
	});
	glVertexAttribDivisor(1, 1);
}

void ChunkRenderer::draw(const Camera &camera, Shader *shader, DrawCommandVec *drawCommands)
{
	// buffer chunk coordinates
	glBindBuffer(GL_ARRAY_BUFFER, m_ccboId);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(m_chunkCoords), m_chunkCoords);

	// upload matrices
	shader->attach();
	shader->uploadMat4(SHADER_U_VIEW, camera.getViewMatrix());
	shader->uploadMat4(SHADER_U_PROJECTION, camera.getProjectionMatrix());

	// upload texture
	glActiveTexture(GL_TEXTURE0);
	m_texture->bind();
	shader->uploadTexture(SHADER_U_TEXTURE, 0);

	// issue draw call
	glBindVertexArray(m_vaoId);
	glMultiDrawArraysIndirect(GL_TRIANGLES, drawCommands->data(), drawCommands->size(), sizeof(DrawArraysIndirectCommand));
	glBindVertexArray(NO_ID);

	m_texture->unbind();
	shader->detach();
}

void ChunkRenderer::render(const Camera &camera)
{
	Shader *shader = NULL;
	DrawCommandVec *drawCommands = NULL;
	bool compose = false;

	if (shouldDraw(OPAQUE, shader, drawCommands)) {
		// set render states
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);

		// draw geometry
		draw(camera, shader, drawCommands);
		compose = true;
	}

	if (shouldDraw(TRANSPARENT, shader, drawCommands)) {
		// set render states
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);

		// draw geometry
		draw(camera, shader, drawCommands);
		compose = true;
	}

	if (shouldDraw(BLENDALBE, shader, drawCommands)) {
		// set render states
		glDisable(GL_CULL_FACE);
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunci(1, GL_ONE, GL_ONE); // accumulation blend target
		glBlendFunci(2, GL_ZERO, GL_ONE_MINUS_SRC_COLOR); // revealage blend target
		glBlendEquation(GL_FUNC_ADD);

		// configure draw buffers
		glDrawBuffers(3, BUFS_NONE_ONE_TWO);
		glClearBufferfv(GL_COLOR, 1, ZERO_FILLER_VEC);
		glClearBufferfv(GL_COLOR, 2, ONE_FILLER_VEC);

		// draw geometry
		draw(camera, shader, drawCommands);
		compose = true;
	}

	if (compose) {
		Framebuffer &framebuffer = Application::getFramebuffer();
		shader = Assets::getShader(COMPOSITE_SHADER_NAME);

		// set render states
		glDepthFunc(GL_ALWAYS);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// configure draw buffers
		glDrawBuffers(3, BUFS_ZERO_NONE_NONE);

		shader->attach();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, framebuffer.getColorAttachment(1)->getId());
		shader->uploadTexture(SHADER_U_ACCUM, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, framebuffer.getColorAttachment(2)->getId());
		shader->uploadTexture(SHADER_U_REVEAL, 1);
		ScreenRenderer::render();
		shader->detach();

		// reset render states
		glDepthFunc(GL_LESS);
	}
 }
