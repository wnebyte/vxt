#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene.hpp"
#include "Window.hpp"
#include "Application.hpp"

#include "io/Mouse.hpp"
#include "io/Keyboard.hpp"

#define TRACE
#define _GLFW_CONTEXT_VERSION_MAJOR 4
#define _GLFW_CONTEXT_VERSION_MINOR 0

using namespace vxt;
using namespace io;

Window* Window::m_window = NULL;

static bool getMaxResolution(uint32_t *width, uint32_t *height)
{
	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	int32_t size = 0;
	bool rv = false;

	if (monitor != NULL) {
		const GLFWvidmode *modes = glfwGetVideoModes(monitor, &size);
		if (size != 0) {
			*width  = modes[size - 1].width;
			*height = modes[size - 1].height;
			rv = true;
		}
	}

	return rv;
}

Window::Window(const std::string &title, uint32_t width, uint32_t height)
	: m_title(title)
	, m_width(width)
	, m_height(height)
	, m_viewport()
	, m_scene()
{
	init();
}

Window::~Window()
{
	try {
		glfwSetErrorCallback(NULL);
		glfwDestroyWindow(m_glfwWindow);
		glfwTerminate();
	} catch (...) {} // no throw
}

Window* Window::create(const std::string &title, uint32_t width, uint32_t height)
{
	if (!m_window) {
		m_window = new Window{title, width, height};
		return m_window;
	} else {
		throw std::exception{};
	}
}

void Window::init(void)
{
	int w, h;

	// Setup an error callback
	glfwSetErrorCallback([](int, const char *msg) { std::cerr << msg << std::endl; });

	// Initialize GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Configure GLFW
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _GLFW_CONTEXT_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _GLFW_CONTEXT_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	if ( (m_width == maxWidth) || (m_height == maxHeight) ) {
		(void)getMaxResolution(&m_width, &m_height);
	}

	// Create the window
	m_glfwWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
	if (!m_glfwWindow) {
		std::cerr << "Failed to create GLFW window." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Make OpenGL context current
	glfwMakeContextCurrent(m_glfwWindow);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Set callbacks
	glfwSetWindowSizeCallback(m_glfwWindow, [](GLFWwindow *window, int width, int height) { m_window->windowSizeCallback(window, width, height); });
	glfwSetFramebufferSizeCallback(m_glfwWindow, [](GLFWwindow *window, int width, int height) { m_window->framebufferSizeCallback(window, width, height); });
	glfwSetCursorPosCallback(m_glfwWindow, [](GLFWwindow *window, double x, double y) { Mouse::cursorPosCallback(window, x, y); });
  	glfwSetMouseButtonCallback(m_glfwWindow, [](GLFWwindow *window, int button, int action, int mod) { Mouse::buttonCallback(window, button, action, mod); });
  	glfwSetScrollCallback(m_glfwWindow, [](GLFWwindow *window, double xOffset, double yOffset) { Mouse::scrollCallback(window, xOffset, yOffset); });
  	glfwSetKeyCallback(m_glfwWindow, [](GLFWwindow *window, int keyCode, int scanCode, int action, int mods) { Keyboard::keyCallback(window, keyCode, scanCode, action, mods); });

	// Enable v-sync
	glfwSwapInterval(1);

	// Set the title
	setTitle(getTitle());

	// Make the window visible
	glfwShowWindow(m_glfwWindow);

	// Set the window size to the actual size of the window
	glfwGetWindowSize(m_glfwWindow, &w, &h);
	windowSizeCallback(m_glfwWindow, w, h);

	// Update the viewport
	glfwGetFramebufferSize(m_glfwWindow, &w, &h);
	framebufferSizeCallback(m_glfwWindow, w, h);
}

void Window::windowSizeCallback(GLFWwindow *window, int width, int height)
{
	m_width = width;
	m_height = height;
#ifdef TRACE
	std::printf("[%s] windowSizeCallback w=%d h=%d\n",
		"Window", width, height);
#endif
}

void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
	Application::getFramebuffer().resize(width, height);
#ifdef TRACE
	std::printf("[%s] framebufferSizeCallback w=%d h=%d\n",
		"Window", width, height);
#endif
}

void Window::update(float dt)
{
	if (m_scene) {
		m_scene->update(dt);
	}
}

void Window::endFrame(void)
{
	Mouse::endFrame();
	Keyboard::endFrame();
}

void Window::swapBuffers(void)
{
	glfwSwapBuffers(m_glfwWindow);
}

void Window::pollEvents(float dt)
{
	glfwPollEvents();
	ufw::notify();
}

void Window::setInputMode(int mode, int value)
{
	glfwSetInputMode(m_glfwWindow, mode, value);
}

void Window::setCursorMode(int value)
{
	setInputMode(GLFW_CURSOR, value);
}

void Window::setCursorPos(double x, double y)
{
	glfwSetCursorPos(m_glfwWindow, x, y);
}

void Window::setShouldClose(bool value)
{
	glfwSetWindowShouldClose(m_glfwWindow, value);
}

bool Window::shouldClose(void)
{
	return glfwWindowShouldClose(m_glfwWindow);
}

void Window::setSize(uint32_t width, uint32_t height)
{
	glfwSetWindowSize(m_glfwWindow, width, height);
	// no need to update the width and height members,
	// they will be updated when the window size callback is invoked by GLFW.
}

void Window::setTitle(const std::string &title)
{
	m_title = title;
	glfwSetWindowTitle(m_glfwWindow, title.c_str());
}

std::string Window::getTitle(void) const
{
	return m_title;
}

uint32_t Window::getWidth(void) const
{
	return m_width;
}

uint32_t Window::getHeight(void) const
{
	return m_height;
}

Viewport Window::getViewport(void) const
{
	return m_viewport;
}

float Window::getAspectRatio(void) const
{
	return (static_cast<float>(m_width) / static_cast<float>(m_height));
}

Scene* Window::getScene(void)
{
	return m_scene.get();
}

void Window::setScene(std::unique_ptr<Scene> &&scene)
{
	m_scene = std::move(scene);
	m_scene->init();
}
