include ../defines.mk

OS        ?= Linux
CXX       := g++
CXXFLAGS  := -g -Wall -std=gnu++11
EXE       := ./bin/$(OS)/$(ARCH)/test
LIBS      := -lGL -lGLU -lglfw -lX11 -lXrandr
SOURCES   := $(shell find src -type f -name "*.cpp")
INCLUDES  := $(shell find src -type d -printf "-I%p\n")
PRODNAME  := $(shell basename -- $(shell dirname $(CURDIR)))_$(shell basename -- $(CURDIR))
LOGFILE   := ./$(PRODNAME).log
MAKE_ARGS := --no-print-directory

VXT          := ..
VXT_INCLUDES := -I$(VXT)/dist/include -I$(VXT)/dist/include/vxt -I$(VXT)/dist/include/vxt/vendor
VXT_LIBS     := -L$(VXT)/dist/lib/$(OS)/$(ARCH) -lvxt -lufw -lpthread

ifeq ($(OS),Windows)
CXX  := x86_64-w64-mingw32-g++-posix
LIBS := -static -lglfw3 -lgdi32
CPPFLAGS := -D_WIN32 -D_POSIX
endif

INSTALL_DIR := /mnt/c/Users/ralle/Tmp/vxt

all: $(EXE)

.PHONY: build
build:
	@$(RM) $(LOGFILE)
	@bash -c "$(MAKE) $(MAKE_ARGS) clean_bin all clean print_end > >(tee -a $(LOGFILE)) 2>&1"

$(EXE): $(SOURCES)
	-mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) $(VXT_INCLUDES) -o $@ $^ $(LIBS) $(VXT_LIBS)

.PHONY: install
install:
	cp ./bin/Windows/x86_64/test.exe $(INSTALL_DIR)
	cp ./bin/Windows/x86_64/run.bat $(INSTALL_DIR)

.PHONY: clean
clean:
	$(RM) ./*out

.PHONY: clean_bin
clean_bin:
	$(RM) $(EXE)*

.PHONY: help
help:
	@echo "USAGE: $(MAKE) <COMMAND>"
	@echo ""
	@echo "COMMANDS:"
	@echo "  all                Builds the product"
	@echo "  build              Logs the output, cleans up and rebuilds the product"
	@echo "  install            Installs the Windows x86_64 build."
	@echo "  clean              Removes all temporary files"
	@echo "  clean_bin          Removes all generated binary files"
	@echo "  help               Writes this help information"

.PHONY: print_end
print_end:
	@echo ""
	@echo "The $(PRODNAME)_$(OS)_$(ARCH) build was successful"
	@echo "Date: $(shell date)"
	@echo ""
