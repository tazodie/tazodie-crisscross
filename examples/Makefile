# CrissCross makefile

include ../common.mk

all: cpuid genprime

cpuid:
	+$(MAKE) -C CPUID precomp
	+$(MAKE) -C CPUID

genprime:
	+$(MAKE) -C GenPrime precomp
	+$(MAKE) -C GenPrime

clean:
	$(MAKE) -C CPUID clean
	$(MAKE) -C GenPrime clean

distclean: clean
