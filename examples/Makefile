# CrissCross makefile

include ../common.mk

all: cpuid-e genprime-e

cpuid-e:
	+$(MAKE) -C CPUID precomp
	+$(MAKE) -C CPUID

genprime-e:
	+$(MAKE) -C GenPrime precomp
	+$(MAKE) -C GenPrime

clean:
	$(MAKE) -C CPUID clean
	$(MAKE) -C GenPrime clean

distclean: clean
