#ifndef VXT_CUBEMAP_HPP
#define VXT_CUBEMAP_HPP

#include <array>

#include <glad/glad.h>

#include "Types.hpp"

namespace vxt {
namespace rdr
{
class Cubemap {
public:
	Cubemap();
	~Cubemap() noexcept = default;

public:
	/// @brief Initializes the cubemap.
	/// @details faces should be sorted in the following order:
	///          * RIGHT
	///          * LEFT
	///          * TOP
	///          * BOTTOM
	///          * BACK
	///          * FRONT
	/// @param faces Array of filepaths
	void init(const std::array<std::string, 6> &faces);
	void bind(void);
	static void unbind(void);
	GLuint getId(void) const;

private:
	GLuint m_id;
};
} // namespace rdr
} // namespace vxt

#endif // VXT_CUBEMAP_HPP
