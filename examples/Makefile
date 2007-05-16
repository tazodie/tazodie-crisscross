# CrissCross makefile

include ../common.mk

all: cpuid

cpuid:
	+$(MAKE) -C CPUID precomp
	+$(MAKE) -C CPUID

clean:
	$(MAKE) -C CPUID clean

distclean: clean
