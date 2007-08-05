# CrissCross makefile

include ../common.mk

all: cpuid-e genprime-e sortingbenchmark-e

cpuid-e:
	+$(MAKE) -C CPUID precomp
	+$(MAKE) -C CPUID

genprime-e:
	+$(MAKE) -C GenPrime precomp
	+$(MAKE) -C GenPrime

sortingbenchmark-e:
	+$(MAKE) -C SortingBenchmark precomp
	+$(MAKE) -C SortingBenchmark

clean:
	$(MAKE) -C CPUID clean
	$(MAKE) -C GenPrime clean
	$(MAKE) -C SortingBenchmark clean

distclean: clean
