#include "cmp/Transform.hpp"

using namespace vxt;
using namespace cmp;

bool Transform::operator==(const Transform &rhs) const
{
	if (&rhs == this) {
		return true;
	} else {
		return ((pos == rhs.pos) &&
				(scale == rhs.scale) &&
				(rotation == rhs.rotation));
	}
}

bool Transform::operator!=(const Transform &rhs) const
{
	return !(*this == rhs);
}

glm::mat4 Transform::toMat4(void) const
{
	glm::mat4 mat = glm::identity<glm::mat4>();

	mat = glm::translate(mat, pos);
	mat = glm::rotate(mat, ufw::math::to_radians(rotation), {0.0f, 0.0f, 1.0f});
	mat = glm::scale(mat, scale);

	return mat;
}
