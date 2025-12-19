#ifndef VXT_KEYBOARD_HPP
#define VXT_KEYBOARD_HPP

#include "Types.hpp"

namespace vxt {
namespace io
{
class Keyboard {
public:
	static const int numOfKeys = 350;

public:
	static void endFrame(void);
	static void keyCallback(GLFWwindow *window, int keyCode, int scanCode, int action, int mods);
	static bool isKeyDown(int keyCode);
	static bool iskeyPressed(int keyCode);

private:
	static bool m_keysDown[numOfKeys];
	static bool m_keysPressed[numOfKeys];
};
} // namespace io
} // namespace vxt

#endif // VXT_KEYBOARD_HPP
