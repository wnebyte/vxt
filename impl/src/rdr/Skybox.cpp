#include <glad/glad.h>

#include "rdr/Shader.hpp"
#include "rdr/Skybox.hpp"
#include "rdr/Cubemap.hpp"
#include "rdr/RenderUtil.hpp"

#include "utl/Assets.hpp"

#define SHADER_NAME "cubemap.glsl"

using namespace vxt;
using namespace rdr;
using namespace utl;

static std::array<std::string, 6> faces{
	"sky/day/right.png",
	"sky/day/left.png",
	"sky/day/top.png",
	"sky/day/bottom.png",
	"sky/day/back.png",
	"sky/day/front.png"
};

static Cubemap cubemap;

static GLuint vaoId = NO_ID;

static GLuint vboId = NO_ID;

static const float data[] = {
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

void Skybox::init(void)
{
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	setVertexAttributes({
		{ 3, GL_FLOAT, sizeof(glm::vec3), (void*)0 }
	});

	cubemap.init(faces);
}

void Skybox::render(const Camera &camera)
{
	Shader   *shader = Assets::getShader(SHADER_NAME);
	GLboolean depthMask;

	glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMask);

	// set render states
	glDepthMask(GL_FALSE);

	shader->attach();
	shader->uploadMat4(SHADER_U_VIEW, glm::mat4{glm::mat3{camera.getViewMatrix()}});
	shader->uploadMat4(SHADER_U_PROJECTION, camera.getProjectionMatrix());
	glActiveTexture(GL_TEXTURE0);
	cubemap.bind();
	shader->uploadTexture(SHADER_U_CUBEMAP, 0);

	glBindVertexArray(vaoId);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(NO_ID);

	cubemap.unbind();
	shader->detach();

	// reset render states
	glDepthMask(depthMask);
}
