#ifndef VXT_CHUNK_RENDERER_HPP
#define VXT_CHUNK_RENDERER_HPP

#include <vector>

#include <glad/glad.h>

#include "Types.hpp"
#include "Camera.hpp"

#include "rdr/Texture.hpp"
#include "rdr/Shaderfwd.hpp"
#include "rdr/DrawCommand.hpp"

#define SUBCHUNK_CAPACITY 200

namespace vxt {
namespace rdr
{
class ChunkRenderer {
private:
	enum DrawCommand_t {
		OPAQUE      = 0,
		TRANSPARENT = 1,
		BLENDALBE   = 2
	};

	typedef std::vector<DrawArraysIndirectCommand> DrawCommandVec;

public:
	ChunkRenderer();
	~ChunkRenderer() noexcept = default;

public:
	void init(void);
	void render(const Camera &camera);

private:
	void draw(const Camera &camera, Shader *shader, DrawCommandVec *drawCommands);
	inline bool shouldDraw(DrawCommand_t type, Shader *shader, DrawCommandVec *drawCommands)
	{
		bool rv = false;

		switch (type) {
			case OPAQUE:
				if (!m_opaqueDrawCommands.empty()) {
					shader = m_opaqueShader;
					drawCommands = &m_opaqueDrawCommands;
					rv = true;
					break;
				}
				break;
			case TRANSPARENT:
				if (!m_transparentDrawCommands.empty()) {
					shader = m_transparentShader;
					drawCommands = &m_transparentDrawCommands;
					rv = true;
					break;
				}
				break;
			case BLENDALBE:
				if (!m_blendableDrawCommands.empty()) {
					shader = m_blendableShader;
					drawCommands = &m_blendableDrawCommands;
					rv = true;
					break;
				}
				break;
			default:
				break;
		}

		return rv;
	}

private:
	GLuint         m_vaoId;
	GLuint         m_vboId;
	GLuint         m_ccboId;
	Texture       *m_texture;
	Shader        *m_opaqueShader;
	Shader        *m_transparentShader;
	Shader        *m_blendableShader;
	DrawCommandVec m_opaqueDrawCommands;
	DrawCommandVec m_transparentDrawCommands;
	DrawCommandVec m_blendableDrawCommands;
	glm::ivec2     m_chunkCoords[SUBCHUNK_CAPACITY];
};
} // namespace rdr
} // namespace vxt

#endif // VXT_CHUNK_RENDERER_HPP
