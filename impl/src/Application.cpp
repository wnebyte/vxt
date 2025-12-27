#include "Window.hpp"
#include "Application.hpp"

using namespace vxt;
using namespace rdr;

Application* Application::m_app = NULL;

Application::Application()
	: m_dt(0)
	, m_window(NULL)
	, m_framebuffer()
{
}

void Application::launch(Application *app)
{
	Configuration config;

	m_app = app;
	app->init(config);
	app->run();
}

void Application::init(Configuration &config)
{
	// virtual
}

void Application::run(void)
{
	// virtual
}

float Application::dt(void)
{
	return m_app->m_dt;
}

Window* Application::getWindow(void)
{
	return m_app->m_window;
}

Framebuffer& Application::getFramebuffer(void)
{
	return m_app->m_framebuffer;
}
