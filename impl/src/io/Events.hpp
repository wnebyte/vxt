#ifndef VXT_IO_EVENTS_HPP
#define VXT_IO_EVENTS_HPP

#include "Types.hpp"

#define VXT_EVENT_KEY 0
#define VXT_EVENT_CURSOR 1
#define VXT_EVENT_SCROLL 2
#define VXT_EVENT_MOUSE_BUTTON 3

namespace vxt {
namespace io
{
struct KeyEvent {
	int keyCode;
	int scanCode;
	int action;
	int mods;
};

struct CursorEvent {
	float xOffset;
	float yOffset;
};

struct ScrollEvent {
	float yScroll;
	float xScroll;
	float yOffset;
	float xOffset;
};

struct MouseButtonEvent {
	int button;
	int action;
	int mod;
};
} // namespace io 
} // namespace vxt

#endif // VXT_IO_EVENTS_HPP
