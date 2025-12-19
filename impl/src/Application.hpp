#ifndef VXT_APPLICATION_HPP
#define VXT_APPLICATION_HPP

#include "Types.hpp"
#include "Windowfwd.hpp"
#include "rdr/Framebuffer.hpp"

class Application {
public:
	static void launch(int argc, char *argv[]);
	static void init(void);
	static vxt::Window* getWindow(void);
	static float dt(void);

private:
	static float m_dt;
	static vxt::Window *m_window;
	static vxt::rdr::Framebuffer m_framebuffer;
};

#endif // VXT_APPLICATION_HPP
