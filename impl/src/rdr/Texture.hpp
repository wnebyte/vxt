#ifndef VXT_TEXTURE_HPP
#define VXT_TEXTURE_HPP

#include <vector>

#include "Types.hpp"

namespace vxt {
namespace rdr
{
class Texture {
public:
	struct Parameter {
		uint32_t name;
		uint32_t value;
	};

	struct Configuration {
		uint32_t target;
		uint32_t level;
		uint32_t internalFormat;
		uint32_t width;
		uint32_t height;
		uint32_t border;
		uint32_t format;
		uint32_t type;
		std::vector<Parameter> parameters;
		std::string path;
		bool flip;
	};

public:
	Texture(const Configuration &config);
	~Texture() noexcept = default;

public:
	void init(void);
	void bind(void);
	void unbind(void);
	int32_t getId(void) const;
	uint32_t getTarget(void) const;
	uint32_t getWidth(void) const;
	uint32_t getHeight(void) const;
	std::string getPath(void) const;

private:
	uint32_t      m_id;
	uint32_t      m_target;
	std::string   m_path;
	uint32_t      m_width;
	uint32_t      m_height;
	Configuration m_config;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_TEXTURE_HPP
