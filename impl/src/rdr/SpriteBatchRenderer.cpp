/// TODO:
/// * data is not buffered initially?

#include <glad/glad.h>

#include "Scene.hpp"
#include "Camera.hpp"
#include "utl/Assets.hpp"
#include "ecs/Entity.hpp"
#include "rdr/Shader.hpp"
#include "rdr/RenderUtil.hpp"
#include "rdr/BatchRenderer.hpp"
#include "rdr/SpriteBatchRenderer.hpp"

#define TRACE
#define SHADER_NAME "sprite.glsl"

using namespace vxt;
using namespace rdr;
using namespace utl;
using namespace cmp;
using namespace ecs;

static const int32_t texSlots[8] = {0, 1, 2, 3, 4, 5, 6, 7};

inline Entity& getEntity(const Component *component)
{
	UFW_ASSERT((component != NULL) && ("component is NULL"));
	UFW_ASSERT((component->m_scene != NULL) && ("scene is NULL"));
	return component->m_scene->getEntity(component->m_entity);
}

template<typename T>
inline T* getComponent(const Component *component)
{
	T *c = getEntity(component).getComponent<T>();
	UFW_ASSERT((c != NULL) && ("c is NULL"));
	return c;
}

SpriteBatchRenderer::SpriteBatchRenderer()
	: m_vaoId(NO_ID)
	, m_vboId(NO_ID)
	, m_size(0)
	, m_data()
	, m_numOfSprites(0)
	, m_sprites()
	, m_textures(ARRAY_SIZE(texSlots))
	, m_shader(Assets::getShader(SHADER_NAME))
	, m_zIndex(UNDEFINED_ZINDEX)
{
}

void SpriteBatchRenderer::init(void)
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
		{ 2, GL_FLOAT, sizeof(Spr), (void*)0 },
		{ 4, GL_FLOAT, sizeof(Spr), (void*)offsetof(Spr, color) },
		{ 2, GL_FLOAT, sizeof(Spr), (void*)offsetof(Spr, uv) },
		{ 1, GL_INT,   sizeof(Spr), (void*)offsetof(Spr, texId) },
		{ 1, GL_INT,   sizeof(Spr), (void*)offsetof(Spr, entityId) }
	});
}

void SpriteBatchRenderer::render(const Camera &camera)
{
	bool rebuffer = false;
	uint32_t index = 0;

	// loop and check for dirty sprites
	for (uint i = 0; i < m_numOfSprites; ++i) {
		SpriteRender *spr = m_sprites[i];

		if (spr->isDirty()) {
			const Transform *transform = getComponent<Transform>(spr);
			if ((transform->pos.z != m_zIndex) || (!m_textures.contains(spr->getTexture()->getId()))) {
				remove(i);
				BatchRenderer::add(getEntity(spr));
				if ( i > 0) i--;
			} else {
				setRenderData(spr, i*4);
				spr->clean();
				rebuffer = true;
			}
		}
	}

	if (rebuffer) {
		glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Spr) * m_size, m_data);
#ifdef TRACE
		std::printf("[%s] buffer data!\n", "SpriteBatchRenderer");
#endif
	}

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

	// issue draw call
	glBindVertexArray(m_vaoId);
	glDrawElements(GL_TRIANGLES, m_size + (m_size / 2), GL_UNSIGNED_INT, NULL);
	glBindVertexArray(NO_ID);

	glBindTexture(GL_TEXTURE_2D, 0);
	m_shader->detach();
}

void SpriteBatchRenderer::destroy(void)
{
	glDeleteBuffers(1, &m_vboId);
	glDeleteVertexArrays(1, &m_vaoId);
}

bool SpriteBatchRenderer::add(SpriteRender *spr)
{
	bool rv = false;
	const Transform *transform = getComponent<Transform>(spr);

	if (m_zIndex == UNDEFINED_ZINDEX) {
		// update zIndex when the first spr is added
		m_zIndex = transform->pos.z;
	}

	if ((transform->pos.z == m_zIndex) && (!atCapacity(spr))) {
		setRenderData(spr, m_size);
		m_sprites[m_numOfSprites] = spr;
		m_size++;
		m_numOfSprites++;
		rv = true;
	}

	return rv;
}

void SpriteBatchRenderer::remove(std::size_t idx)
{
	if (idx < (m_size - 1)) {
		std::memmove(&(m_sprites[idx]), &(m_sprites[idx+1]), sizeof(SpriteRender) * (m_size - (idx+1)));
		std::memmove(&(m_data[idx*4]), &(m_data[(idx+1)*4]), sizeof(Spr) * ((m_size*4) - ((idx+1)*4)));
		for (uint i = idx; i < m_size - 1; ++i) {
			m_sprites[i]->dirty();
		}
	}
	--m_size;
}

void SpriteBatchRenderer::setRenderData(SpriteRender *spr, std::size_t idx)
{
	float xAdd = 0.5f;
	float yAdd = 0.5f;
	const Transform *transform = getComponent<Transform>(spr);

	for (uint i = 0; i < 4; ++i) {
		Spr *data = &(m_data[(idx*4)+i]);

		switch (i) {
			case 1:
				yAdd = -0.5f;
				break;
			case 2:
				xAdd = -0.5f;
				break;
			case 3:
				yAdd = 0.5f;
				break;
			default:
				break;
		}

		if (transform->rotation != 0.0f) {
			data->pos = glm::vec4{xAdd, yAdd, 0.0f, 1.0f} * transform->toMat4();
		} else {
			data->pos = glm::vec4{
				transform->pos.x + (xAdd * transform->scale.x),
				transform->pos.y + (yAdd * transform->scale.y),
				0.0f, 1.0f};
		}
		data->color = spr->getColor();
		data->uv = spr->getUvs()[i];
		data->texId = spr->getTexture()->getId();
		data->entityId = spr->m_entity;
	}
}

bool SpriteBatchRenderer::atCapacity(SpriteRender *spr)
{
	bool rv = true;
	const int32_t texId = spr->getTexture()->getId();

	if ((size()*4 <= (maxBatchSize - 4)) && ((texId == NO_TEX_ID) || (!atTexCapacity(texId)))) {
		rv = false;
	}

	return rv;
}

bool SpriteBatchRenderer::atTexCapacity(int32_t texId)
{
	bool rv = true;

	if (texId > NO_TEX_ID) {
		if (m_textures.add(texId)) {
			rv = false; // tex id already has been added or was successfully added
		}
	}

	return rv;
}

int32_t SpriteBatchRenderer::zIndex(void) const
{
	return m_zIndex;
}

std::size_t SpriteBatchRenderer::size(void) const
{
	return m_size;
}
