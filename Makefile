include ./defines.mk

PRODNAME := vxt
LOGFILE  := $(PRODNAME).log

.PHONY: all
all:
	@$(MAKE) $(MAKE_ARGS) -C impl build
	@$(MAKE) $(MAKE_ARGS) OS=Windows -C impl build
	@$(MAKE) $(MAKE_ARGS) -C test build
	@$(MAKE) $(MAKE_ARGS) OS=Windows -C test build

.PHONY: build
build:
	@$(RM) $(LOGFILE)
	@bash -c "$(MAKE) $(MAKE_ARGS) print_start clean clean_bin all print_end > >(tee -a $(LOGFILE)) 2>&1"

.PHONY: linux
linux:
	@$(MAKE) $(MAKE_ARGS) -C impl build
	@$(MAKE) $(MAKE_ARGS) -C test build

.PHONY: windows
windows:
	@$(MAKE) $(MAKE_ARGS) OS=Windows -C impl build
	@$(MAKE) $(MAKE_ARGS) OS=Windows -C test build

.PHONY: clean clean_bin
clean clean_bin:
	$(MAKE) $(MAKE_ARGS) -C impl $@
	$(MAKE) $(MAKE_ARGS) OS=Windows -C impl $@
	$(MAKE) $(MAKE_ARGS) -C test $@
	$(MAKE) $(MAKE_ARGS) OS=Windows -C test $@

.PHONY: help
help:
	@echo "USAGE: $(MAKE) <COMMAND>"
	@echo ""
	@echo "COMMANDS:"
	@echo "  build            Logs the output, cleans up and rebuilds the products impl and test for Linux and Windows"
	@echo "  all              Builds all products for Linux and Windows"
	@echo "  linux            Builds all products for Linux"
	@echo "  windows          Builds all products for Windows"
	@echo "  clean            Removes all temporary files"
	@echo "  clean_bin        Removes all generated binary files"
	@echo "  help             Writes this help information"

.PHONY: print_start
print_start:
	@echo "Building $(PRODNAME)"
	@echo ""

.PHONY: print_end
print_end:
	@echo ""
	@echo "The $(PRODNAME) build was successful"
	@echo "Date: $(shell date)"
	@echo ""
