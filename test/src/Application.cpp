#include <memory>
#include <csignal>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vxt/Window.hpp"
#include "vxt/Application.hpp"

#include "vxt/utl/Misc.hpp"
#include "vxt/utl/Assets.hpp"
#include "vxt/utl/Constants.hpp"
#include "vxt/utl/CmdHandler.hpp"

#include "vxt/rdr/Shader.hpp"
#include "vxt/rdr/Skybox.hpp"
#include "vxt/rdr/Builder.hpp"
#include "vxt/rdr/Texture.hpp"
#include "vxt/rdr/Framebuffer.hpp"
#include "vxt/rdr/BatchRenderer.hpp"
#include "vxt/rdr/ScreenRenderer.hpp"

#include "Scene2.hpp"
#include "Scene3.hpp"

#define APPLICATION_TITLE "untitled"
#define FBO_OPAQUE "fbo.opaque"
#define FBO_ACCUM "fbo.accum"
#define FBO_REVEAL "fbo.reveal"
#define FBO_DEPTH "fbo.depth"
#define FBO_USE
#define TEXTURE3 "texture3"
#define SCREEN_SHADER_NAME "screen.glsl"

using namespace vxt;
using namespace rdr;
using namespace utl;
using namespace test;

class MyApplication : public Application {
public:
	MyApplication()
		: Application()
	{
	}

public:
	void init(Configuration &config) override;
	void run(void) override;
};

static ufw::thread* cmdHandler = NULL;

static void sigHandler(int sig);
static void shutdown(void);

int main(int argc, char* argv[])
{
	MyApplication app;

	std::printf("started\n");

	{
		// shut the process down orderly
		signal(SIGHUP,  sigHandler);
		signal(SIGINT,  sigHandler);
		signal(SIGQUIT, sigHandler);
		signal(SIGABRT, sigHandler);
		signal(SIGKILL, sigHandler);
		signal(SIGTERM, sigHandler);
#ifndef _WIN32
		signal(SIGTSTP, sigHandler);
#endif
	}

	Application::launch(&app);

	return 0;
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

void MyApplication::init(Configuration &config)
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
		.addParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
		.addParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
		.build<Texture::Configuration>();

	accum = TextureBuilder{}
		.setSize(w, h)
		.setTarget(GL_TEXTURE_2D)
		.setInternalFormat(GL_RGBA16F)
		.setFormat(GL_RGBA)
		.setType(GL_HALF_FLOAT)
		.addParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
		.addParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
		.build<Texture::Configuration>();

	reveal = TextureBuilder{}
		.setSize(w, h)
		.setTarget(GL_TEXTURE_2D)
		.setInternalFormat(GL_R8)
		.setFormat(GL_RED)
		.setType(GL_FLOAT)
		.addParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR)
		.addParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
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
	m_framebuffer.init();

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

	// pack textures
	Assets::getTexture(TEXTURE3, TextureBuilder{}
		.setTarget(GL_TEXTURE_2D_ARRAY)
		.addParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR)
		.addParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
		.setImages(pack3(Assets::getPath("blocks", Assets::IMAGES)))
		.build<Texture::Configuration>());

	// init renderers
	Skybox::init();
	ScreenRenderer::init();

	// set the scene
	m_window->setScene(std::make_unique<Scene3>(m_window));
}

void MyApplication::run(void)
{
	float lastFrame = 0.0f;
	Shader *shader = Assets::getShader(SCREEN_SHADER_NAME);

	while (!m_window->shouldClose()) {
		m_currentFrame = glfwGetTime();
		m_dt = m_currentFrame - lastFrame;
		lastFrame = m_currentFrame;

		// poll for events
		m_window->pollEvents(m_dt);

		{
			// render window into application framebuffer

			// set application framebuffer render states
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);

			m_framebuffer.bind();
			glDrawBuffers(3, BUFS_ZERO_NONE_NONE);
			glClearBufferfv(GL_COLOR, 0, ZERO_FILLER_VEC);
			glClearBufferfv(GL_DEPTH, 0, ONE_FILLER_VEC);
			m_window->update(m_dt);
		}

		{
			// render screen quad into default framebuffer

			// set default framebuffer render states
			glDisable(GL_DEPTH_TEST);
			glDepthMask(GL_TRUE);

			Framebuffer::unbind();
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			shader->attach();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_framebuffer.getColorAttachment(0)->getId());
			shader->uploadTexture(SHADER_U_SCREEN, 0);
			ScreenRenderer::render();
			glBindTexture(GL_TEXTURE_2D, NO_ID);
			shader->detach();
		}

		// swap buffers and end frame
		m_window->swapBuffers();
		m_window->endFrame();
	}
}
