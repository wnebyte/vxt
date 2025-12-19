#ifndef VXT_MOUSE_HPP
#define VXT_MOUSE_HPP

#include "Types.hpp"

namespace vxt {
namespace io
{
class Mouse {
public:
	static const int numOfButtons = 9;

public:
	static void endFrame(void);
	static void cursorPosCallback(GLFWwindow *window, double x, double y);
	static void buttonCallback(GLFWwindow *window, int button, int action, int mod);
	static void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);
	static bool isButtonDown(int button);
	static bool isButtonPressed(int button);
	static bool isDragging(void);
	static float getX(void);
	static float getY(void);
	static glm::vec2 getPosition(void);
	static float getScrollX(void);
	static float getScrollY(void);

private:
	static float    m_xPos;
	static float    m_yPos;
	static double   m_xScroll;
	static double   m_yScroll;
	static bool     m_buttonsDown[numOfButtons];
	static bool     m_buttonsPressed[numOfButtons];
	static bool     m_isDragging;
	static uint32_t m_numOfButtonsDown;
	static bool     m_isFirstMouseEvent;
};
} // namespace io
} // namespace vxt

#endif // VXT_MOUSE_HPP
