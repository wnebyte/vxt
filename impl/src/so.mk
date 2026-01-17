IMPL_DIR := ..

include $(IMPL_DIR)/../defines.mk

DIST_DIR := $(IMPL_DIR)/../dist
OS       ?= Linux
PF       := $(OS)/$(ARCH)
CXX      := g++
CXXFLAGS := -g -Wall -std=gnu++11
LIBS     := -lGL -lglfw -lX11 -lXrandr -lufw -lpthread

LIBDIR   := $(DIST_DIR)/lib/$(PF)
LIBNAME  := libvxt
SOEXT    := so
ARCHIVES := $(shell find $(LIBDIR) -type f -name "*.a")

MAJOR_VERSION := $(shell grep 'VXT_MAJOR_VERSION' $(IMPL_DIR)/src/utl/Version.hpp | cut -d' ' -f3)
MINOR_VERSION := $(shell grep 'VXT_MINOR_VERSION' $(IMPL_DIR)/src/utl/Version.hpp | cut -d' ' -f3)

SONAME     := $(LIBNAME).$(SOEXT).$(MAJOR_VERSION)
SOREALNAME := $(LIBNAME).$(SOEXT).$(MAJOR_VERSION).$(MINOR_VERSION)

ifeq ($(OS),Windows)
CXX        := x86_64-w64-mingw32-g++-posix
AR         := x86_64-w64-mingw32-gcc-ar-posix
LIBS       := -lglfw3 -lgdi32 -lufw -lpthread
CPPFLAGS   := -D_WIN32 -D_POSIX
SOEXT      := dll
SONAME     := $(LIBNAME)_$(MAJOR_VERSION).$(SOEXT)
SOREALNAME := $(LIBNAME)_$(MAJOR_VERSION)_$(MINOR_VERSION).$(SOEXT)
endif

SO := $(LIBDIR)/$(SOREALNAME)

.PHONY: all
all: $(SO)

$(SO): $(ARCHIVES)
	-mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -fPIC -shared -Wl,-soname,$(SONAME) -Wl,--whole-archive -o $@ $^ -Wl,--no-whole-archive $(LIBS)
	(cd $(LIBDIR); ln -sf $(SOREALNAME) $(SONAME); ln -sf $(SONAME) $(LIBNAME).$(SOEXT))

.PHONY: clean
clean: ;

.PHONY: clean_bin
clean_bin:
	@$(RM) $(LIBDIR)/*.$(SOEXT)*
