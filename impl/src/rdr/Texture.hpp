#ifndef VXT_TEXTURE_HPP
#define VXT_TEXTURE_HPP

#include <vector>

#include <glad/glad.h>

#include "Types.hpp"
#include "rdr/Image.hpp"

namespace vxt {
namespace rdr
{
class Texture {
public:
	struct Parameter {
		GLenum name;
		GLint  value;
	};

	struct Configuration {
		GLenum  target;
		GLint   level;
		GLint   internalFormat;
		GLsizei width;
		GLsizei height;
		GLint   border;
		GLenum  format;
		GLenum  type;
		std::vector<Parameter> parameters;
		std::vector<Image> images;
		std::string path;
		bool flip;
	};

public:
	Texture(const Configuration &config);
	~Texture() noexcept = default;

public:
	void init(bool create = true);
	void bind(void);
	void unbind(void);
	int32_t getId(void) const;
	GLenum getTarget(void) const;
	uint32_t getWidth(void) const;
	uint32_t getHeight(void) const;
	std::string getPath(void) const;
	void resize(uint32_t width, uint32_t height);

private:
	GLuint         m_id;
	GLenum         m_target;
	std::string    m_path;
	uint32_t       m_width;
	uint32_t       m_height;
	Configuration  m_config;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_TEXTURE_HPP
