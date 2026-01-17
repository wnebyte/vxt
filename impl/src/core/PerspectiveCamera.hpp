#ifndef VXT_PERSPECTIVE_CAMERA_HPP
#define VXT_PERSPECTIVE_CAMERA_HPP

#include "Types.hpp"
#include "Camera.hpp"

#define VXT_CAMERA_DEFAULT_YAW   (-90.0f)
#define VXT_CAMERA_DEFAULT_PITCH (0.0f)

namespace vxt {
class PerspectiveCamera : public Camera {
public:
	PerspectiveCamera(const glm::vec3 &position,
					  float zNear,
					  float zFar,
					  float aspectRatio,
					  float yaw = VXT_CAMERA_DEFAULT_YAW,
					  float pitch = VXT_CAMERA_DEFAULT_PITCH,
					  const glm::vec3 &foward = VXT_CAMERA_DEFAULT_FORWARD,
					  const glm::vec3 &up = VXT_CAMERA_DEFAULT_UP,
					  const glm::vec3 &right = VXT_CAMERA_DEFAULT_RIGHT);
	~PerspectiveCamera() noexcept = default;

public:
	void update(float dt) override;
	float getYaw(void) const;
	void setYaw(float yaw);
	float getPitch(void) const;
	void setPitch(float pitch);

protected:
	void adjustProjection(void) override;
	void adjustView(void) override;

private:
	void updateCameraVectors(void);

protected:
	glm::vec3 m_wUp;
	float     m_yaw;
	float     m_pitch;
};
} // namespace vxt

#endif // VXT_PERSPECTIVE_CAMERA_HPP
