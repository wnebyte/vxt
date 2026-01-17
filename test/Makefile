include ../defines.mk

PRODNAME := vxt_test
LOGFILE  := $(PRODNAME).log

.PHONY: all clean clean_bin
all clean clean_bin:
	@$(MAKE) $(MAKE_ARGS) -C src $@

.PHONY: build
build:
	@$(RM) $(LOGFILE)
	@bash -c "$(MAKE) $(MAKE_ARGS) print_start all print_end > >(tee -a $(LOGFILE)) 2>&1"

.PHONY: help
help:
	@echo "USAGE: $(MAKE) <COMMAND>"
	@echo ""
	@echo "COMMANDS:"
	@echo "  build            Logs the output, builds the product"
	@echo "  all              Builds the product"
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
