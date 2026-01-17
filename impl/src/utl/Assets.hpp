#ifndef VXT_ASSETS_HPP
#define VXT_ASSETS_HPP

#include <map>

#include "Types.hpp"
#include "rdr/Texture.hpp"
#include "rdr/Shaderfwd.hpp"

namespace vxt {
namespace utl
{
class Assets {
public:
	enum Type {
		IMAGES,
		SHADERS,
		SIZE
	};

public:
	static rdr::Shader* getShader(const std::string &name);
	static rdr::Texture* getTexture(const std::string &name);
	static rdr::Texture* getTexture(const std::string &name, rdr::Texture::Configuration config);
	static void setTexture(const std::string &name, rdr::Texture *texture);
	static void destroy(void);
	static std::string getPath(const std::string &name, const std::string &type);
	static std::string getPath(const std::string &name, Type type);
	static std::string getName(Type type);

private:
	static std::map<std::string, rdr::Shader*>  m_shaders;
	static std::map<std::string, rdr::Texture*> m_textures;
	static const rdr::Texture::Configuration m_defaultTextureConfig;
	static const std::string m_types[SIZE];
};
} // namespace utl
} // namespace vxt

#endif // VXT_ASSETS_HPP
