# CrissCross makefile

include ../common.mk

all: cpuid-e genprime-e sortbenchmark-e emptyproject-e

cpuid-e:
	+$(MAKE) -C CPUID precomp
	+$(MAKE) -C CPUID

emptyproject-e:
	+$(MAKE) -C EmptyProject precomp
	+$(MAKE) -C EmptyProject

genprime-e:
	+$(MAKE) -C GenPrime precomp
	+$(MAKE) -C GenPrime

sortbenchmark-e:
	+$(MAKE) -C SortBenchmark precomp
	+$(MAKE) -C SortBenchmark

clean:
	$(MAKE) -C CPUID clean
	$(MAKE) -C GenPrime clean
	$(MAKE) -C SortBenchmark clean
	$(MAKE) -C EmptyProject clean

distclean: clean
