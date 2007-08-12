# CrissCross makefile

include ../common.mk

all: cpuid-e genprime-e sortbenchmark-e xmlparser-e

cpuid-e:
	+$(MAKE) -C CPUID precomp
	+$(MAKE) -C CPUID

genprime-e:
	+$(MAKE) -C GenPrime precomp
	+$(MAKE) -C GenPrime

sortbenchmark-e:
	+$(MAKE) -C SortBenchmark precomp
	+$(MAKE) -C SortBenchmark

xmlparser-e:
	+$(MAKE) -C XMLParser precomp
	+$(MAKE) -C XMLParser

clean:
	$(MAKE) -C CPUID clean
	$(MAKE) -C GenPrime clean
	$(MAKE) -C SortBenchmark clean
	$(MAKE) -C XMLParser clean

distclean: clean
