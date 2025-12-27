#ifndef VXT_WINDOW_HPP
#define VXT_WINDOW_HPP

#include <memory>

#include "Types.hpp"
#include "Scenefwd.hpp"

class GLFWwindow;

namespace vxt {
struct Viewport {
	glm::vec2 pos;
	glm::vec2 size;
};

class Window {
public:
	static const uint32_t defaultWidth  = 1920;
	static const uint32_t defaultHeight = 1080;
	static const uint32_t maxWidth = 0;
	static const uint32_t maxHeight = 0;

public:
	~Window();
	Window(const Window&) = delete;
  	Window& operator=(const Window&) = delete;
 	Window(Window&&) = delete;
  	Window& operator=(Window&&) = delete;

private:
	Window(const std::string &title, uint32_t width, uint32_t height);

public:
	void update(float dt);
	void endFrame(void);
	bool shouldClose(void);
	void setShouldClose(bool value);
	void swapBuffers(void);
	void pollEvents(float dt);
	void setInputMode(int mode, int value);
	void setCursorMode(int value);
	void setCursorPos(double xPos, double yPos);
	void setTitle(const std::string &title);

	/// @brief Set the size of the Window content area.
	/// @details This function sets the size in screen coordinates of the content area of the Window.
	/// @param [in] width The desired width in screen coordinates of the Window content area
	/// @param [in] height The desired height in screen coordinates of the Window content area
	void setSize(uint32_t width, uint32_t height);

	std::string getTitle(void) const;
	uint32_t getWidth(void) const;
	uint32_t getHeight(void) const;
	Viewport getViewport(void) const;
	float getAspectRatio(void) const;
	Scene* getScene(void);
	void setScene(std::unique_ptr<Scene> &&scene);
	static Window* create(const std::string &title, uint32_t width = maxWidth, uint32_t height = maxHeight);

private:
	void init(void);
	void windowSizeCallback(GLFWwindow *window, int width, int height);
	void framebufferSizeCallback(GLFWwindow *window, int width, int height);

private:
	GLFWwindow            *m_glfwWindow;
	std::string            m_title;
	uint32_t               m_width;
	uint32_t               m_height;
	Viewport               m_viewport; // NOT the OpenGL viewport
	std::unique_ptr<Scene> m_scene;
	static Window         *m_window;
};

} // namespace vxt

#endif // VXT_WINDOW_HPP
