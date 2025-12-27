include ../defines.mk

OS          ?= Linux
CXX         := g++
CXXFLAGS    := -g -Wall -std=gnu++11
CPPFLAGS    :=
LIBS        := -lGL -lglfw -lX11 -lXrandr -lufw -lpthread 
CXX_SOURCES := $(shell find src -type f -name "*.cpp")
C_SOURCES   := $(shell find src -type f -name "*.c")
OBJECTS     := $(patsubst %.cpp, %.o, $(CXX_SOURCES)) $(patsubst %.c, %.o, $(C_SOURCES)) 
INCLUDES    := $(shell find src -type d -printf "-I%p\n")
PRODNAME    := $(shell basename -- $(shell dirname $(CURDIR)))
LOGFILE     := ./$(PRODNAME).log
MAKE_ARGS   := --no-print-directory

VXT_LIBDIR  := ../dist/lib/$(OS)/$(ARCH)
VXT_LIBNAME := libvxt
VXT_SOEXT   := so
VXT_AREXT   := a

VXT_MAJOR_VERSION := $(shell grep 'VXT_MAJOR_VERSION' src/Version.hpp | cut -d' ' -f3)
VXT_MINOR_VERSION := $(shell grep 'VXT_MINOR_VERSION' src/Version.hpp | cut -d' ' -f3)

VXT_SONAME     := $(VXT_LIBNAME).$(VXT_SOEXT).$(VXT_MAJOR_VERSION)
VXT_SOREALNAME := $(VXT_LIBNAME).$(VXT_SOEXT).$(VXT_MAJOR_VERSION).$(VXT_MINOR_VERSION)
VXT_ARNAME     := $(VXT_LIBNAME).$(VXT_AREXT).$(VXT_MAJOR_VERSION)
VXT_ARREALNAME := $(VXT_LIBNAME).$(VXT_AREXT).$(VXT_MAJOR_VERSION).$(VXT_MINOR_VERSION)

ifeq ($(OS),Windows)
CXX      := x86_64-w64-mingw32-g++-posix
AR       := x86_64-w64-mingw32-gcc-ar-posix
LIBS     := -lglfw3 -lgdi32 -lufw -lpthread 
CPPFLAGS := -D_WIN32 -D_POSIX
VXT_SOEXT      := dll
VXT_SONAME     := $(VXT_LIBNAME)_$(VXT_MAJOR_VERSION).$(VXT_SOEXT)
VXT_SOREALNAME := $(VXT_LIBNAME)_$(VXT_MAJOR_VERSION)_$(VXT_MINOR_VERSION).$(VXT_SOEXT)
VXT_ARNAME     := $(VXT_LIBNAME)_$(VXT_MAJOR_VERSION).$(VXT_AREXT)
VXT_ARREALNAME := $(VXT_LIBNAME)_$(VXT_MAJOR_VERSION)_$(VXT_MINOR_VERSION).$(VXT_AREXT)
endif

VXT_SO := $(VXT_LIBDIR)/$(VXT_SOREALNAME)
VXT_AR := $(VXT_LIBDIR)/$(VXT_ARREALNAME)

all: $(VXT_AR) $(VXT_SO)

.PHONY: build
build:
	@$(RM) $(LOGFILE)
	@bash -c "$(MAKE) $(MAKE_ARGS) clean_bin all clean print_end > >(tee -a $(LOGFILE)) 2>&1"

$(VXT_SO): $(OBJECTS)
	-mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -fPIC -shared -Wl,-soname,$(VXT_SONAME) -o $@ $^ $(LIBS)
	(cd $(VXT_LIBDIR); ln -s $(VXT_SOREALNAME) $(VXT_SONAME); ln -s $(VXT_SONAME) $(VXT_LIBNAME).$(VXT_SOEXT))

$(VXT_AR): $(OBJECTS)
	-mkdir -p $(@D)
	$(AR) rcs $@ $^
	(cd $(VXT_LIBDIR); ln -s $(VXT_ARREALNAME) $(VXT_ARNAME); ln -s $(VXT_ARNAME) $(VXT_LIBNAME).$(VXT_AREXT))

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -fPIC -o $@ -c $<

src/%.o: src/%.c
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -fPIC -o $@ -c $<

.PHONY: clean
clean:
	$(RM) src/*.o
	$(RM) src/*/*.o
	$(RM) src/*/*/*.o

.PHONY: clean_bin
clean_bin:
	$(RM) $(VXT_LIBDIR)/*.a
	$(RM) $(VXT_LIBDIR)/*.dll*
	$(RM) $(VXT_LIBDIR)/*.so*

.PHONY: help
help:
	@echo "USAGE: $(MAKE) <COMMAND>"
	@echo ""
	@echo "COMMANDS:"
	@echo "  all                Builds the product"
	@echo "  build              Logs the output, cleans up and rebuilds the product"
	@echo "  clean              Removes all temporary files"
	@echo "  clean_bin          Removes all generated binary files"
	@echo "  help               Writes this help information"

.PHONY: print_end
print_end:
	@echo ""
	@echo "The $(PRODNAME)_$(OS)_$(ARCH) build was successful"
	@echo "Date: $(shell date)"
	@echo ""
