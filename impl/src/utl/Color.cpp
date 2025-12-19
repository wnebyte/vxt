#include "utl/Color.hpp"
#include "Color.hpp"

using namespace vxt;
using namespace utl;

static uint32_t asInt(const glm::vec4 &rgba)
{
	const uint32_t r = static_cast<uint32_t>(rgba.x);
	const uint32_t g = static_cast<uint32_t>(rgba.y);
	const uint32_t b = static_cast<uint32_t>(rgba.z);
	const uint32_t a = static_cast<uint32_t>(rgba.x);

	return ((r & 0xFF) << 24) |
		   ((g & 0xFF) << 16) |
		   ((b & 0xFF) << 8)  |
		   ((a & 0xFF) << 0); /// TODO: fix
}

static glm::vec4 asVec4(uint32_t rgba)
{
	const float r = static_cast<float>( (rgba >> 24) & 0xFF );
	const float g = static_cast<float>( (rgba >> 16) & 0xFF );
	const float b = static_cast<float>( (rgba >> 8)  & 0xFF );
	const float a = static_cast<float>( (rgba >> 0)  & 0xFF ) / 255.0f;

	return glm::vec4{r, g, b, a};
}

Color::Color()
	: m_value(0.0f, 0.0f, 0.0f, 1.0f)
{
}

Color::Color(float r, float g, float b, float a)
	: m_value(r, g, b, a)
{
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	: m_value(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f)
{
}

Color::Color(uint32_t rgba)
	: m_value(asVec4(rgba))
{
}

Color::Color(const glm::vec3 &color)
	: m_value(color, 1.0f)
{
}

Color::Color(const glm::vec4 &color)
	: m_value(color)
{
}

Color::operator uint32_t(void) const
{
	return toInt();
}

Color::operator glm::vec3(void) const
{
	return toVec3();
}

Color::operator glm::vec4(void) const
{
	return toVec4();
}

uint32_t Color::toInt(void) const
{
	return asInt(m_value);
}

glm::vec3 Color::toVec3(void) const
{
	return glm::vec3{m_value};
}

glm::vec4 Color::toVec4(void) const
{
	return m_value;
}
