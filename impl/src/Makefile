include ../../defines.mk

MODULES := anim cmp core ecs io rdr utl vendor

.DEFAULT:
	@$(MAKE) $(MAKE_ARGS) MAKE_TARGET=$@

.PHONY: all
all: so

.PHONY: $(MODULES)
$(MODULES):
	$(MAKE) $(MAKE_ARGS) -C $@ $(MAKE_TARGET)

.PHONY: so
so: $(MODULES)
	$(MAKE) $(MAKE_ARGS) -f so.mk $(MAKE_TARGET)
