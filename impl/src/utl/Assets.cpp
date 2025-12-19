#include <cstdlib>

#include <glad/glad.h>

#include "Assets.hpp"
#include "rdr/Shader.hpp"

#define VXT_ASSETS_DIR "VXT_ASSETS_DIR"
#define SHADERS_DIRNAME "shaders"
#define IMAGES_DIRNAME "images"

using namespace vxt;
using namespace utl;
using namespace rdr;

using shader_it = std::map<std::string, Shader*>::iterator;
using tex_it = std::map<std::string, Texture*>::iterator;

std::map<std::string, Shader*> Assets::m_shaders;
std::map<std::string, Texture*> Assets::m_textures;
Texture::Configuration Assets::m_defaultTextureConfig{
	GL_TEXTURE_2D, 0, 0, 0, 0, 0, 0, 0,
	{
		{GL_TEXTURE_WRAP_S, GL_REPEAT},
		{GL_TEXTURE_WRAP_T, GL_REPEAT},
		{GL_TEXTURE_MIN_FILTER, GL_NEAREST},
		{GL_TEXTURE_MAG_FILTER, GL_NEAREST}
	},
	"", false
};

Shader* Assets::getShader(const std::string &name)
{
	const std::string path{toPath(name, SHADERS_DIRNAME)};
	const shader_it iter{m_shaders.find(path)};

	if (iter != m_shaders.end()) {
		return iter->second;
	} else {
		Shader *shader = new Shader{path};
		std::pair<shader_it, bool> result;
		shader->compile();
		result = m_shaders.emplace(path, shader);
		UFW_ASSERT((result.second) && ("failed to emplace shader"));
		return result.first->second;
	}
}

Texture* Assets::getTexture(const std::string &name)
{
	return getTexture(name, m_defaultTextureConfig);
}

Texture* Assets::getTexture(const std::string &name, Texture::Configuration config)
{
	const std::string path{toPath(name, IMAGES_DIRNAME)};
	const tex_it iter{m_textures.find(path)};

	if (iter != m_textures.end()) {
		return iter->second;
	} else {
		Texture *texture = NULL;
		std::pair<tex_it, bool> result;
		config.path = path;
		texture = new Texture{config};
		texture->init();
		result = m_textures.emplace(path, texture);
		UFW_ASSERT((result.second) && ("failed to emplace texture"));
		return result.first->second;
	}
}

void Assets::setTexture(const std::string &name, Texture *texture)
{
	const std::string path{toPath(name, IMAGES_DIRNAME)};
	const tex_it iter{m_textures.find(path)};

	if (iter != m_textures.end()) {
		delete iter->second;
		iter->second = texture;
	} else {
		std::pair<tex_it, bool> result;
		result = m_textures.emplace(path, texture);
		UFW_ASSERT((result.second) && ("failed to emplace texture"));
	}
}

std::string Assets::toPath(const std::string &name, const std::string &type)
{
	static const char *env = getenv(VXT_ASSETS_DIR);
	UFW_ASSERT((env != NULL) && ("VXT_ASSETS_DIR is not set"));
	return ufw::fs::join_path(env, {type, name});
}

void Assets::destroy(void)
{
	for (auto &pair : m_shaders) {
		delete pair.second;
		pair.second = NULL;
	}
	for (auto &pair : m_textures) {
		delete pair.second;
		pair.second = NULL;
	}
	m_shaders.clear();
	m_textures.clear();
}
