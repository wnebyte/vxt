include ../../defines.mk

OS       ?= Linux
PF       := $(OS)/$(ARCH)
CXX      := g++
CXXFLAGS := -g -Wall -std=gnu++11
EXE      := ../bin/$(OS)/$(ARCH)/test
LIBS     := -lGL -lGLU -lglfw -lX11 -lXrandr
SOURCES  := $(shell find -type f -name "*.cpp" -printf "%P\n")
OBJECTS  := $(patsubst %.cpp, $(PF)/%.o, $(SOURCES))
DEPS     := $(patsubst %.o, %.d, $(OBJECTS))
INCLUDES := -I.

VXT          := ../..
VXT_LIBDIR   := $(VXT)/dist/lib/$(PF)
VXT_ARCHIVES := $(shell find $(VXT_LIBDIR) -type f -name "*.a" -printf "%P\n" | sed 's/^lib/-l/' | sed 's/\.a//')
VXT_INCLUDES := -I$(VXT)/dist/include -I$(VXT)/dist/include/vxt -I$(VXT)/dist/include/vxt/vendor
VXT_LIBS     := -L$(VXT_LIBDIR) -lvxt -lufw -lpthread

ifeq ($(OS),Windows)
CXX      := x86_64-w64-mingw32-g++-posix
CPPFLAGS := -D_WIN32 -D_POSIX
LIBS     := -static -lglfw3 -lgdi32
VXT_LIBS := -L$(VXT_LIBDIR) -Wl,--start-group $(VXT_ARCHIVES) -Wl,--end-group -lufw -lpthread
endif

LIBS     += $(VXT_LIBS)
INCLUDES += $(VXT_INCLUDES)

.PHONY: all
all: $(EXE)

$(EXE): $(OBJECTS)
	-mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -o $@ $^ $(LIBS)

$(PF)/%.o: %.cpp
	@-mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -fPIC -o $@ -c $<

$(PF)/%.d: %.cpp
	@-mkdir -p $(@D)
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $(INCLUDES) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(PF)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

ifneq ($(DEPS),"")
-include $(DEPS)
endif

.PHONY: clean
clean:
	@$(RM) -rf $(PF)
	@-rmdir $(OS)

.PHONY: clean_bin
clean_bin:
	@$(RM) $(EXE)*
