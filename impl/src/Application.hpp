#ifndef VXT_APPLICATION_HPP
#define VXT_APPLICATION_HPP

#include "Types.hpp"
#include "Windowfwd.hpp"
#include "rdr/Framebuffer.hpp"

namespace vxt {
class Application {
public:
	struct Configuration {};

public:
	Application();
	~Application() noexcept = default;

public:
	static float dt(void);
	static Window* getWindow(void);
	static rdr::Framebuffer& getFramebuffer(void);
	static void launch(Application *app);

protected:
	virtual void init(Configuration &config);
	virtual void run(void);

protected:
	float m_dt;
	Window *m_window;
	rdr::Framebuffer m_framebuffer;
	static Application* m_app;
};
} // namespace vxt

#endif // VXT_APPLICATION_HPP
