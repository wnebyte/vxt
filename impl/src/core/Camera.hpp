#ifndef VXT_CAMERA_HPP
#define VXT_CAMERA_HPP

#include "Types.hpp"

#define VXT_CAMERA_DEFAULT_FORWARD (glm::vec3{0.0f, 0.0f, -1.0f})
#define VXT_CAMERA_DEFAULT_UP      (glm::vec3{0.0f, 1.0f, 0.0f})
#define VXT_CAMERA_DEFAULT_RIGHT   (glm::vec3{1.0f, 0.0f, 0.0f})
#define VXT_CAMERA_DEFAULT_ZOOM    (1.0f)

namespace vxt {
class Camera {
public:
	enum Hints {
		USE_HALF_PROJECTION      = (1 << 0),
		NO_ZOOM                  = (1 << 1),
		CALC_PROJECTION_IDENTITY = (1 << 2),
		CALC_VIEW_IDENTITY       = (1 << 3)
	};

    enum Direction {
		UNKNOWN,
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

public:
	Camera(const glm::vec3 &position,
		   float zNear,
		   float zFar,
		   float aspectRatio,
		   const glm::vec3 &forward = VXT_CAMERA_DEFAULT_FORWARD,
		   const glm::vec3 &up = VXT_CAMERA_DEFAULT_UP,
		   const glm::vec3 &right = VXT_CAMERA_DEFAULT_RIGHT);
	virtual ~Camera() noexcept = default;

public:
	virtual void update(float dt);
	float getZNear(void) const;
	void setZNear(float zNear);
	float getZFar(void) const;
	void setZFar(float zFar);
	float getAspectRatio(void) const;
	void setAspectRatio(float aspectRatio);
	float getZoom(void) const;
	void setZoom(float zoom);
	const glm::vec3& getForward(void) const;
	glm::vec3 getForward(void);
	void setForward(const glm::vec3 &forward);
	const glm::vec3& getUp(void) const;
	glm::vec3 getUp(void);
	void setUp(const glm::vec3 &up);
	const glm::vec3& getRight(void) const;
	glm::vec3 getRight(void);
	void setRight(const glm::vec3 &right);
	const glm::mat4& getProjectionMatrix() const;
	glm::mat4 getProjectionMatrix();
    const glm::mat4& getInverseProjectionMatrix() const;
	glm::mat4 getInverseProjectionMatrix();
    const glm::mat4& getViewMatrix() const;
    glm::mat4 getViewMatrix();
    const glm::mat4& getInverseViewMatrix() const;
    glm::mat4 getInverseViewMatrix();
	const glm::vec3& getPosition(void) const;
	glm::vec3 getPosition(void);
	void setPosition(const glm::vec3 &position);
	void setPosition(const glm::vec2 &position);
	void add(const glm::vec3 &position);
	void add(const glm::vec2 &position);
	void sub(const glm::vec3 &position);
	void sub(const glm::vec2 &position);
	void mul(const glm::vec3 &position);
	void mul(const glm::vec2 &position);
	void div(const glm::vec3 &position);
	void div(const glm::vec2 &position);
	void setHints(uint32_t hints);

protected:
	virtual void adjustView(void);
	virtual void adjustProjection(void);

public:
	glm::vec3 m_position;

protected:
	float     m_zNear;
    float     m_zFar;
    float     m_aspectRatio;
    float     m_zoom;
    glm::vec3 m_forward;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_inverseProjectionMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_inverseViewMatrix;
	uint32_t  m_hints;
};
} // namespace vxt

#endif // VXT_CAMERA_HPP
