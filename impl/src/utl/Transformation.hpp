#ifndef VXT_TRANSFORMATION_HPP
#define VXT_TRANSFORMATION_HPP

#include <functional>

#include "Types.hpp"
#include "Camerafwd.hpp"

namespace vxt {
namespace utl
{
/// @brief Coordinate System Type.
enum CoordinateSystem {
	/// @brief Global common space for all objects in a scene.
	WORLD_SPACE  = 0,
	/// @brief Space with the camera positioned at the origin looking down the negative Z-axis. Achieved with the View Matrix.
	VIEW_SPACE   = 1,
	/// @brief (Normalized Device Coordinates) Maps the visible geometry into a cube from -1 to 1. The output of the Projection Matrix.
	CLIP_SPACE   = 2,
	/// @brief The final 2D pixel grid where coordinates map to screen pixels.
	SCREEN_SPACE = 3
};

/// @brief Transformation function Type.
typedef std::function<glm::vec2(const Camera *camera, const glm::vec2 &pos)> TransformFkn;

/// @brief Transform pos from View Space to World Space coordinates.
/// @param camera [in] The camera
/// @param pos [in] The position in View Space coordinates
/// @return The position in World Space
glm::vec2 viewSpaceToWorldSpace(const Camera *camera, const glm::vec2 &pos);

/// @brief Transform pos from Clip Space to View Space coordinates.
/// @param camera [in] The camera
/// @param pos [in] The posiiton in Clip Space coordinates
/// @return The position in View Space
glm::vec2 ndcToViewSpace(const Camera *camera, const glm::vec2 &pos);

/// @brief Transform pos from Screen Space to Clip Space.
/// @param camera [in] The camera
/// @param pos [in] The position in Screen Space coordinates
/// @return The position in Clip Space (-1, 1)
glm::vec2 screenSpaceToNdc(const Camera *camera, const glm::vec2 &pos);

/// @brief Transform pos from one coordinate system to another.  
/// @tparam from The coordinate system to transform from
/// @tparam to The coordinate system to transform to
/// @param pos [in] The position to transform
/// @return The transformed position
template<CoordinateSystem from, CoordinateSystem to>
inline glm::vec2 transform(const Camera *camera, const glm::vec2 &pos)
{
	glm::vec2 res{pos};
	static const TransformFkn fkns[3] = { &viewSpaceToWorldSpace, &ndcToViewSpace, &screenSpaceToNdc };

	UFW_STATIC_ASSERT(to < from, "to has to be smaller than from");

	for (uint i = (from - 1); i >= to; --i) {
		res = fkns[i](camera, res);
	}

	return res;
}
} // namespace utl
} // namespace vxt

#endif // VXT_TRANSFORMATION_HPP
