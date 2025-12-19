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
	static rdr::Shader* getShader(const std::string &name);
	static rdr::Texture* getTexture(const std::string &name);
	static rdr::Texture* getTexture(const std::string &name, rdr::Texture::Configuration config);
	static void setTexture(const std::string &name, rdr::Texture *texture);
	static void destroy(void);

private:
	static std::string toPath(const std::string &name, const std::string &type);

private:
	static std::map<std::string, rdr::Shader*>  m_shaders;
	static std::map<std::string, rdr::Texture*> m_textures;
	static rdr::Texture::Configuration m_defaultTextureConfig;
};
} // namespace utl
} // namespace vxt

#endif // VXT_ASSETS_HPP
