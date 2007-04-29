include common.mk

all: main

main:
	+$(MAKE) -C source precomp
	+$(MAKE) -C source

testapp: main
	+$(MAKE) -C TestSuite precomp
	+$(MAKE) -C TestSuite

test: testapp
	cd TestSuite; LD_LIBRARY_PATH="../source" ./crisscross-test;

install:
	$(MAKE) -C source install

clean:
	$(MAKE) -C source clean
	$(MAKE) -C TestSuite clean

fastdep:
	+$(MAKE) -C contrib/fastdep-0.15
	
distclean: clean
	
