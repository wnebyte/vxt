#include <iostream>
#include <memory>
#include <csignal>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vxt/Window.hpp"
#include "vxt/Application.hpp"

#include "vxt/utl/Assets.hpp"
#include "vxt/utl/CmdHandler.hpp"

#include "vxt/rdr/Builder.hpp"
#include "vxt/rdr/Texture.hpp"
#include "vxt/rdr/Framebuffer.hpp"
#include "vxt/rdr/BatchRenderer.hpp"
#include "vxt/rdr/ScreenRenderer.hpp"

#include "Scene2.hpp"
#include "Scene3.hpp"

#define APPLICATION_TITLE (std::string{"untitled"})
#define FBO_OPAQUE "fbo.opaque"
#define FBO_ACCUM "fbo.accum"
#define FBO_REVEAL "fbo.reveal"
#define FBO_DEPTH "fbo.depth"

using namespace vxt;
using namespace rdr;
using namespace utl;
using namespace test;

static ufw::thread* cmdHandler = NULL;
float Application::m_dt = 0.0f;
Window* Application::m_window = NULL;
Framebuffer Application::m_framebuffer;

static void registerSigHandlers(void);
static void sigHandler(int sig);
static void shutdown(void);

int main(int argc, char* argv[])
{
	std::printf("started\n");
	registerSigHandlers();
	Application::launch(argc, argv);
	return 0;
}

static void registerSigHandlers(void)
{
	// shut the process down orderly
	signal(SIGKILL, sigHandler);
	signal(SIGINT,  sigHandler);
	signal(SIGTERM, sigHandler);
	signal(SIGQUIT, sigHandler);
	signal(SIGHUP,  sigHandler);
	signal(SIGTSTP, sigHandler);
	signal(SIGABRT, sigHandler);
}

static void sigHandler(int sig)
{
	std::fprintf(stderr, "\nSignal %d caught, will shutdown\n", sig);
	shutdown();
	std::fflush(stderr);
	std::fflush(stdout);

	// At the end terminate with the given signal
	signal(sig, SIG_DFL);
	raise(sig);

	// If not signal handler, terminate by following exit
	std::exit(sig);
}

static void shutdown(void)
{
	rdr::BatchRenderer::destroy();
	Application::getWindow()->setShouldClose(true);

	if (cmdHandler != NULL) {
		cmdHandler->interrupt();
		cmdHandler->join(1000);
		delete cmdHandler;
	}
}

void Application::init(void)
{
	uint32_t w;
	uint32_t h;
	Texture::Configuration opaque;
	Texture::Configuration accum;
	Texture::Configuration reveal;
	Texture::Configuration depth;

	// init window
	m_window = Window::create(APPLICATION_TITLE);
	w = m_window->getWidth();
	h = m_window->getHeight();

	// init framebuffer textures
	opaque = TextureBuilder{}
		.setSize(w, h)
		.setTarget(GL_TEXTURE_2D)
		.setInternalFormat(GL_RGBA16F)
		.setFormat(GL_RGBA)
		.setType(GL_HALF_FLOAT)
		.addParameter({GL_TEXTURE_MIN_FILTER, GL_LINEAR})
		.addParameter({GL_TEXTURE_MAG_FILTER, GL_LINEAR})
		.build<Texture::Configuration>();
	accum = TextureBuilder{}
		.setSize(w, h)
		.setTarget(GL_TEXTURE_2D)
		.setInternalFormat(GL_RGBA16F)
		.setFormat(GL_RGBA)
		.addParameter({GL_TEXTURE_MIN_FILTER, GL_LINEAR})
		.addParameter({GL_TEXTURE_MAG_FILTER, GL_LINEAR})
		.build<Texture::Configuration>();
	reveal = TextureBuilder{}
		.setSize(w, h)
		.setTarget(GL_TEXTURE_2D)
		.setInternalFormat(GL_R8)
		.setFormat(GL_RED)
		.setType(GL_FLOAT)
		.addParameter({GL_TEXTURE_MIN_FILTER, GL_LINEAR})
		.addParameter({GL_TEXTURE_MAG_FILTER, GL_LINEAR})
		.build<Texture::Configuration>();
	depth = TextureBuilder{}
		.setSize(w, h)
		.setTarget(GL_TEXTURE_2D)
		.setInternalFormat(GL_DEPTH_COMPONENT)
		.setFormat(GL_DEPTH_COMPONENT)
		.setType(GL_FLOAT)
		.build<Texture::Configuration>();

	// init framebuffer
	m_framebuffer = FramebufferBuilder{}
		.setSize(w, h)
		.addColorAttachment(Assets::getTexture(FBO_OPAQUE, opaque))
		.addColorAttachment(Assets::getTexture(FBO_ACCUM, accum))
		.addColorAttachment(Assets::getTexture(FBO_REVEAL, reveal))
		.setDepthAttachment(Assets::getTexture(FBO_DEPTH, depth))
		.build();
	// m_framebuffer.init();

	// init cmdHandler
	try {
		cmdHandler = new CmdHandler{};
	} catch (std::bad_alloc &ex) {
		std::cerr << "Bad alloc" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	if (!cmdHandler->start()) {
		std::cerr << "Failed to start CmdHandler" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// init ScreenRenderer
	ScreenRenderer::init();

	// set the scene
	m_window->setScene(std::make_unique<Scene3>(m_window));
}

void Application::launch(int argc, char *argv[])
{
	float currentFrame;
	float lastFrame = 0.0f;

	init();

	while (!m_window->shouldClose()) {
		currentFrame = glfwGetTime();
		m_dt = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		m_window->pollEvents(m_dt);
		m_window->update(m_dt);
		m_window->swapBuffers();
		m_window->endFrame();
	}
}

Window* Application::getWindow(void)
{
	return m_window;
}

float Application::dt(void)
{
	return m_dt;
}
