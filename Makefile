# CrissCross makefile

include common.mk

all: main

main:
	+$(MAKE) -C source precomp
	+$(MAKE) -C source
	
pretty:
	+$(MAKE) -C source pretty
	+$(MAKE) -C examples pretty
	+$(MAKE) -C TestSuite pretty

example: main
	+$(MAKE) -C examples

testsuite: main
	+$(MAKE) -C TestSuite precomp
	+$(MAKE) -C TestSuite

check: test

test: testsuite
	$(MAKE) -C TestSuite test

memcheck: testsuite
	$(MAKE) -C TestSuite memcheck

install:
	$(MAKE) -C source install

clean:
	$(MAKE) -C source clean
	$(MAKE) -C examples clean
	$(MAKE) -C TestSuite clean

distclean: clean

info:
	@echo "Will compile with GCC v$(GCC_MAJOR).$(GCC_MINOR)."
	@echo "CFLAGS=$(CFLAGS)"
	@echo "CXXFLAGS=$(CXXFLAGS)"

	@echo -n "Processor supports MMX: "
ifeq ($(GCC_HAS_MMX),yes)
	@echo "YES"
else
	@echo "NO"
endif

	@echo -n "Processor supports SSE: "
ifeq ($(GCC_HAS_SSE),yes)
	@echo "YES"
else
	@echo "NO"
endif

	@echo -n "Processor supports SSE2: "
ifeq ($(GCC_HAS_SSE2),yes)
	@echo "YES"
else
	@echo "NO"
endif
