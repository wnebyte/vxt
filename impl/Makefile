CXX         := g++
CXXFLAGS    := -g -Wall -std=gnu++11
LIBS        := -lGL -lGLU -lglfw -lX11 -lXrandr -lstb -lpthread -lufw
CXX_SOURCES := $(shell find src -type f -name "*.cpp")
C_SOURCES   := $(shell find src -type f -name "*.c")
OBJECTS     := $(patsubst %.cpp, %.o, $(CXX_SOURCES)) $(patsubst %.c, %.o, $(C_SOURCES)) 
INCLUDES    := $(shell find src -type d -printf "-I%p\n")
PRODNAME    := $(shell basename -- $(shell dirname $(CURDIR)))
LOGFILE     := ./$(PRODNAME).log
MAKE_ARGS   := --no-print-directory

MAJOR_VERSION := $(shell grep 'VXT_MAJOR_VERSION' src/Version.hpp | cut -d' ' -f3)
MINOR_VERSION := $(shell grep 'VXT_MINOR_VERSION' src/Version.hpp | cut -d' ' -f3)

LIBDIR   := ../dist/lib
LIBNAME  := libvxt.so
SONAME   := $(LIBNAME).$(MAJOR_VERSION)
REALNAME := $(LIBNAME).$(MAJOR_VERSION).$(MINOR_VERSION)
LIB      := $(LIBDIR)/$(REALNAME)

all: $(LIB)

.PHONY: build
build:
	@$(RM) $(LOGFILE)
	@bash -c "$(MAKE) $(MAKE_ARGS) clean_bin all clean print_end > >(tee -a $(LOGFILE)) 2>&1"

$(LIB): $(OBJECTS)
	-mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -fPIC -shared -Wl,-soname,$(SONAME) -o $@ $^ $(LIBS)
	(cd $(LIBDIR); ln -s $(REALNAME) $(SONAME); ln -s $(SONAME) $(LIBNAME))

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -fPIC -o $@ -c $<

src/%.o: src/%.c
	$(CXX) $(CXXFLAGS) $(INCLUDES) -fPIC -o $@ -c $<

.PHONY: clean
clean:
	$(RM) src/*.o
	$(RM) src/*/*.o

.PHONY: clean_bin
clean_bin:
	$(RM) $(LIBDIR)/*.so*

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
	@echo "The $(PRODNAME) build was successful"
	@echo "Date: $(shell date)"
