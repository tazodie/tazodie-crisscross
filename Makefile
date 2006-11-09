include common.mk

all: testapp

main: fastdep
	+$(MAKE) -C source precomp
	+$(MAKE) -C source

testapp: main
	+$(MAKE) -C Application precomp
	+$(MAKE) -C Application	

test: testapp
	cd Application; LD_LIBRARY_PATH="../source" ./crisscross-test;

toolchain:
	+$(MAKE) -C tools

install:
	$(MAKE) -C source install

clean:
	$(MAKE) -C source clean
	$(MAKE) -C Application clean

fastdep: toolchain
	+$(MAKE) -C contrib/fastdep-0.15
	
distclean: clean
	$(MAKE) -C contrib/fastdep-0.15 distclean
	$(MAKE) -C tools clean
	
