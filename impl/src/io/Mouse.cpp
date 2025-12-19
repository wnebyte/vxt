#include <cstring>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "io/Mouse.hpp"
#include "io/Events.hpp"

using namespace vxt;
using namespace io;

float Mouse::m_xPos = 0.0f;
float Mouse::m_yPos = 0.0f;
double Mouse::m_xScroll = 0.0;
double Mouse::m_yScroll = 0.0;
bool Mouse::m_buttonsDown[Mouse::numOfButtons];
bool Mouse::m_buttonsPressed[Mouse::numOfButtons];
bool Mouse::m_isDragging = false;
uint32_t Mouse::m_numOfButtonsDown = 0;
bool Mouse::m_isFirstMouseEvent = true;

void Mouse::endFrame(void)
{
	memset(m_buttonsPressed, 0, sizeof(m_buttonsPressed));
}

void Mouse::cursorPosCallback(GLFWwindow *window, double x, double y)
{
	float xOffset;
	float yOffset;

	if (m_isFirstMouseEvent) {
		m_xPos = x;
		m_yPos = y;
		m_isFirstMouseEvent = false;
	}

	m_isDragging = (m_numOfButtonsDown > 0);
	xOffset = x - m_xPos;
	yOffset = m_yPos - y; // reveresed since y-coordinates go from bottom to top
	m_xPos = x;
	m_yPos = y;

	if (xOffset > 0.0f || yOffset > 0.0f) {
		// handle mouse movement
		std::shared_ptr<CursorEvent> event{new CursorEvent{}};
		event->xOffset = xOffset;
		event->yOffset = yOffset;
		ufw::add_event(VXT_EVENT_CURSOR, event);
	}
}

void Mouse::buttonCallback(GLFWwindow *window, int button, int action, int mod)
{
	switch (action) {
		case GLFW_PRESS:
			++m_numOfButtonsDown;
			if (button < numOfButtons) {
				m_buttonsDown[button] = true;
				m_buttonsPressed[button] = true;
			}
			break;
		case GLFW_RELEASE:
			--m_numOfButtonsDown;
			if (button < numOfButtons) {
				m_buttonsDown[button] = false;
				m_buttonsPressed[button] = false;
				m_isDragging = false;
			}
			break;
		default:
			break;
	}

	{
		std::shared_ptr<MouseButtonEvent> event{new MouseButtonEvent{}};
		event->button = button;
		event->action = action;
		event->mod = mod;
		ufw::add_event(VXT_EVENT_MOUSE_BUTTON, event);
	}
}

void Mouse::scrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
	m_xScroll += xOffset;
	m_yScroll += yOffset;

	if (yOffset != 0.0f) {
		std::shared_ptr<ScrollEvent> event{new ScrollEvent{}};
		event->yScroll = m_yScroll;
		event->xScroll = m_xScroll;
		event->yOffset = yOffset;
		event->xOffset = xOffset;
		ufw::add_event(VXT_EVENT_SCROLL, event);
	}
}

bool Mouse::isButtonDown(int button)
{
	return (button < numOfButtons) ? m_buttonsDown[button] : false;
}

bool Mouse::isButtonPressed(int button)
{
	return (button < numOfButtons) ? m_buttonsPressed[button] : false;
}

bool Mouse::isDragging(void)
{
	return m_isDragging;
}

float Mouse::getX(void)
{
	return m_xPos;
}

float Mouse::getY(void)
{
	return m_yPos;
}

glm::vec2 Mouse::getPosition(void)
{
	return glm::vec2{m_xPos, m_yPos};
}

float Mouse::getScrollX(void)
{
	return m_xScroll;
}

float Mouse::getScrollY(void)
{
	return m_yScroll;
}
