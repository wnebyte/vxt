#ifndef VXT_COLOR_HPP
#define VXT_COLOR_HPP

#include "Types.hpp"

namespace vxt {
namespace utl
{
class Color {
public:
	Color();
	Color(float r, float g, float b, float a = 1.0f);
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF);
	Color(uint32_t rgba);
	Color(const glm::vec3 &color);
	Color(const glm::vec4 &color);
	~Color() noexcept = default;

public:
	operator uint32_t() const;
	operator glm::vec3() const;
	operator glm::vec4() const;

public:
	uint32_t toInt(void) const;
	glm::vec3 toVec3(void) const;
	glm::vec4 toVec4(void) const;

private:
	glm::vec4 m_value;
};
} // namespace utl
} // namespace vxt

#endif // VXT_COLOR_HPP
