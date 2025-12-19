#include <cstring>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "io/Events.hpp"
#include "io/Keyboard.hpp"

using namespace vxt;
using namespace io;

bool Keyboard::m_keysDown[Keyboard::numOfKeys];
bool Keyboard::m_keysPressed[Keyboard::numOfKeys];

void Keyboard::endFrame(void)
{
	memset(m_keysPressed, 0, sizeof(m_keysPressed));
}

void Keyboard::keyCallback(GLFWwindow *window, int keyCode, int scanCode, int action, int mods)
{
	switch (action) {
		case GLFW_PRESS:
			if (keyCode < numOfKeys) {
				m_keysDown[keyCode] = true;
				m_keysPressed[keyCode] = true;
			}
			break;
		case GLFW_RELEASE:
			if (keyCode < numOfKeys) {
				m_keysDown[keyCode] = false;
				m_keysPressed[keyCode] = false;
			}
			break;
		default:
			break;
	}

	{
		std::shared_ptr<KeyEvent> event{new KeyEvent{}};
		event->keyCode = keyCode;
		event->scanCode = scanCode;
		event->action = action;
		event->mods = mods;
		ufw::add_event(VXT_EVENT_KEY, event);
	}
}

bool Keyboard::isKeyDown(int keyCode)
{
	return (keyCode < numOfKeys) ? m_keysDown[keyCode] : false;
}

bool Keyboard::iskeyPressed(int keyCode)
{
	return (keyCode < numOfKeys) ? m_keysPressed[keyCode] : false;
}
