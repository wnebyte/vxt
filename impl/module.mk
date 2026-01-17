include $(IMPL_DIR)/../defines.mk

DIST_DIR    := $(IMPL_DIR)/../dist
OS          ?= Linux
PF          := $(OS)/$(ARCH)
CXX         := g++
CXXFLAGS    := -g -Wall -std=gnu++11
ARFLAGS     := rcs
CXX_SOURCES := $(shell find -type f -name "*.cpp" -printf "%P\n")
C_SOURCES   := $(shell find -type f -name "*.c" -printf "%P\n")
OBJECTS     := $(patsubst %.cpp, $(PF)/%.o, $(CXX_SOURCES)) $(patsubst %.c, $(PF)/%.o, $(C_SOURCES))
DEPS        := $(patsubst %.o, %.d, $(OBJECTS))
INCLUDES    := -I. -I$(DIST_DIR)/include/vxt -I$(DIST_DIR)/include/vxt/vendor
MODNAME     := $(shell basename $(CURDIR))

LIBDIR  := $(DIST_DIR)/lib/$(PF)
LIBNAME := lib$(MODNAME)
AREXT   := a
ARCHIVE := $(LIBDIR)/$(LIBNAME).$(AREXT)

ifeq ($(OS),Windows)
CXX      := x86_64-w64-mingw32-g++-posix
AR       := x86_64-w64-mingw32-gcc-ar-posix
CPPFLAGS := -D_WIN32 -D_POSIX
endif

all: $(ARCHIVE)

$(ARCHIVE): $(OBJECTS)
	@-mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $^

$(PF)/%.o: %.cpp
	@-mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -fPIC -o $@ -c $<

$(PF)/%.o: %.c
	@-mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -fPIC -o $@ -c $<

$(PF)/%.d: %.cpp
	@-mkdir -p $(@D)
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $(INCLUDES) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(PF)/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

$(PF)/%.d: %.c
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
	@$(RM) $(ARCHIVE)
