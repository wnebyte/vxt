MAKE_ARGS := --no-print-directory

.PHONY: all build
all build:
	$(MAKE) $(MAKE_ARGS) -C impl build
	$(MAKE) $(MAKE_ARGS) OS=Windows -C impl build
	$(MAKE) $(MAKE_ARGS) -C test build
	$(MAKE) $(MAKE_ARGS) OS=Windows -C test build

.PHONY: linux
linux:
	$(MAKE) $(MAKE_ARGS) -C impl build
	$(MAKE) $(MAKE_ARGS) -C test build

.PHONY: windows
windows:
	$(MAKE) $(MAKE_ARGS) OS=Windows -C impl build
	$(MAKE) $(MAKE_ARGS) OS=Windows -C test build

.PHONY: clean
clean:
	$(MAKE) $(MAKE_ARGS) -C impl clean
	$(MAKE) $(MAKE_ARGS) OS=Windows -C impl clean
	$(MAKE) $(MAKE_ARGS) -C test clean
	$(MAKE) $(MAKE_ARGS) OS=Windows -C test clean

.PHONY: clean_bin
clean_bin:
	$(MAKE) $(MAKE_ARGS) -C impl clean_bin
	$(MAKE) $(MAKE_ARGS) OS=Windows -C impl clean_bin
	$(MAKE) $(MAKE_ARGS) -C test clean_bin
	$(MAKE) $(MAKE_ARGS) OS=Windows -C test clean_bin

.PHONY: help
help:
	@echo "USAGE: $(MAKE) <COMMAND>"
	@echo ""
	@echo "COMMANDS:"
	@echo "  all or build     Logs the output, cleans up and rebuilds the product"
	@echo "  linux            Build the product for Linux."
	@echo "  windows          Build the product for Windows."
	@echo "  clean            Removes all temporary files"
	@echo "  clean_bin        Removes all generated binary files"
	@echo "  help             Writes this help information"
