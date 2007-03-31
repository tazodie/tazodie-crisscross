include common.mk

all: testapp

main: fastdep
	+$(MAKE) -C source precomp
	+$(MAKE) -C source

testapp: main
	+$(MAKE) -C TestSuite	

test: testapp
	cd TestSuite; LD_LIBRARY_PATH="../source" ./crisscross-test;

toolchain:
	+$(MAKE) -C tools

install:
	$(MAKE) -C source install

clean:
	$(MAKE) -C source clean
	$(MAKE) -C Application clean
	$(MAKE) -C TestSuite clean

fastdep: toolchain
	+$(MAKE) -C contrib/fastdep-0.15
	
distclean: clean
	$(MAKE) -C contrib/fastdep-0.15 distclean
	$(MAKE) -C tools clean
	
