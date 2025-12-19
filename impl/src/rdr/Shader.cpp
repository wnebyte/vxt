#include <regex>

#include <glad/glad.h>

#include "Shader.hpp"

using namespace vxt;
using namespace rdr;

#define INVALID_ID 0
#define NUM_OF_TYPES 2
#define VERTEX_TYPE "vertex"
#define FRAGMENT_TYPE "fragment"
#define BUF_SIZE 1024

Shader::Shader(const std::string &path)
	: m_id(INVALID_ID)
	, m_path(path)
	, m_vertexSource()
	, m_fragmentSource()
	, m_detached(true)
{
	std::string source;
	std::size_t index;
	std::size_t eol;
	std::string types[NUM_OF_TYPES];
	std::sregex_token_iterator iter;
	std::sregex_token_iterator end;
	static const std::regex rgx{"(#type)( )+([a-zA-Z]+)"};

	UFW_ASSERT((ufw::fs::read(path, source)) && ("failed to read source"));
	iter = std::sregex_token_iterator{source.begin(), source.end(), rgx, -1};

	// find the first shader type
	index = source.find("#type") + 6;
	eol = source.find("\n", index);
	types[0] = source.substr(index, (eol - index));

	// find the second shader type
	index = source.find("#type", eol) + 6;
	eol = source.find("\n", index);
	types[1] = source.substr(index, (eol - index));

	for (uint i = 0; i < NUM_OF_TYPES; ++i) {
		if (types[i] == VERTEX_TYPE) {
			m_vertexSource = *(++iter);
		} else if (types[i] == FRAGMENT_TYPE) {
			m_fragmentSource = *(++iter);
		} else {
			UFW_ASSERT((false) && ("unknown shader type"));
		}
	}
}

void Shader::compile(void)
{
	uint32_t vertexId;
	uint32_t fragmentId;
	const GLchar* vertexSrcArr[] = { m_vertexSource.c_str() };
	const GLchar* fragmentSrcArr[] = { m_fragmentSource.c_str() };
	
	// load and compile the vertex shader
	vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, vertexSrcArr, NULL);
	glCompileShader(vertexId);
	checkCompileStatus(vertexId, VERTEX_TYPE);

	// load and compile the fragment shader
	fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentId, 1, fragmentSrcArr, NULL);
	glCompileShader(fragmentId);
	checkCompileStatus(fragmentId, FRAGMENT_TYPE);

	// link the shaders
	m_id = glCreateProgram();
	glAttachShader(m_id, vertexId);
	glAttachShader(m_id, fragmentId);
	glLinkProgram(m_id);
	checkLinkStatus(m_id);

	// delete the shaders
	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

void Shader::checkCompileStatus(uint32_t shaderId, const std::string &shaderType) const
{
	int result;
	char info[BUF_SIZE];

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(shaderId, sizeof(info), NULL, info);
		std::cerr << "[Shader] compliation error for shader " << ufw::fs::basename(m_path) << " (" << shaderType << ")\n"
			<< info << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void Shader::checkLinkStatus(uint32_t shaderId) const
{
	int result;
	char info[BUF_SIZE];

	glGetProgramiv(shaderId, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderId, sizeof(info), NULL, info);
		std::cerr << "[Shader] link error for shader " << ufw::fs::basename(m_path) << '\n' << info << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void Shader::attach(void)
{
	if (m_detached) {
		glUseProgram(m_id);
		m_detached = false;
	}
}

void Shader::detach(void)
{
	glUseProgram(INVALID_ID);
	m_detached = true;
}

uint32_t Shader::getId(void) const
{
	return m_id;
}

std::string Shader::getPath(void) const
{
	return m_path;
}

void Shader::uploadInt(const std::string &varName, int32_t i)
{
	int varLocation;
    attach();
    varLocation = glGetUniformLocation(m_id, varName.c_str());
    glUniform1i(varLocation, i);
}

void Shader::uploadFloat(const std::string &varName, float f)
{
	int varLocation;
    attach();
    varLocation = glGetUniformLocation(m_id, varName.c_str());
    glUniform1f(varLocation, f);
}

void Shader::uploadBool(const std::string &varName, bool b)
{
	uploadInt(varName, b);
}

void Shader::uploadIntArray(const std::string &varName, const int32_t *array, std::size_t size)
{
	int varLocation;
    attach();
    varLocation = glGetUniformLocation(m_id, varName.c_str());
    glUniform1iv(varLocation, size, array);
}

void Shader::uploadFloatArray(const std::string &varName, const float *array, std::size_t size)
{
	int varLocation;
    attach();
    varLocation = glGetUniformLocation(m_id, varName.c_str());
    glUniform1fv(varLocation, size, array);
}

void Shader::uploadVec2(const std::string &varName, const glm::vec2 &vec)
{
	int varLocation;
    attach();
    varLocation = glGetUniformLocation(m_id, varName.c_str());
    glUniform2fv(varLocation, 2, &(vec[0]));
}

void Shader::uploadVec3(const std::string &varName, const glm::vec3 &vec)
{
	int varLocation;
    attach();
    varLocation = glGetUniformLocation(m_id, varName.c_str());
    glUniform3fv(varLocation, 3, &(vec[0]));
}

void Shader::uploadVec4(const std::string &varName, const glm::vec4 &vec)
{
	int varLocation;
    attach();
    varLocation = glGetUniformLocation(m_id, varName.c_str());
    glUniform4fv(varLocation, 4, &(vec[0]));
}

void Shader::uploadMat3(const std::string &varName, const glm::mat3 &mat)
{
	int varLocation;
    attach();
    varLocation = glGetUniformLocation(m_id, varName.c_str());
    glUniformMatrix3fv(varLocation, 1, GL_FALSE, &(mat[0][0]));
}

void Shader::uploadMat4(const std::string &varName, const glm::mat4 &mat)
{
	int varLocation;
    attach();
    varLocation = glGetUniformLocation(m_id, varName.c_str());
    glUniformMatrix4fv(varLocation, 1, GL_FALSE, &(mat[0][0]));
}

void Shader::uploadTexture(const std::string &varName, int32_t slot)
{
	uploadInt(varName, slot);
}
