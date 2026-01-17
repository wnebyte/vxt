#ifndef VXT_ORTHO_CAMERA_HPP
#define VXT_ORTHO_CAMERA_HPP

#include "Types.hpp"
#include "Camera.hpp"

namespace vxt {
class OrthoCamera : public Camera {
public:
	OrthoCamera(const glm::vec3 &position,
				float zNear,
				float zFar,
				float aspectRatio,
				float projectionWidth,
				float projectionHeight,
				const glm::vec3 &forward = VXT_CAMERA_DEFAULT_FORWARD,
				const glm::vec3 &up = VXT_CAMERA_DEFAULT_UP,
				const glm::vec3 &right = VXT_CAMERA_DEFAULT_RIGHT);
	virtual ~OrthoCamera() noexcept = default;

public:
	float getProjectionWidth(void) const;
	void setProjectionWidth(float projectionWidth);
	float getProjectionHeight(void) const;
	void setProjectionHeight(float projectionHeight);
	const glm::vec2& getProjectionSize(void) const;
	glm::vec2 getProjectionSize(void);

protected:
	void adjustProjection(void) override;
	void adjustView(void) override;

protected:
	glm::vec2 m_projectionSize;
};
} // namespace vxt

#endif // VXT_ORTHO_CAMERA_HPP
