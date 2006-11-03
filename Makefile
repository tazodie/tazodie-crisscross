include common.mk

all: testapp

main: toolchain
	+$(MAKE) -C source

testapp: toolchain main
	+$(MAKE) -C Application	

test: testapp
	cd Application; ./crisscross-test;

toolchain: fastdep
	+$(MAKE) -C tools

install:
	$(MAKE) -C source install

clean:
	$(MAKE) -C source clean
	$(MAKE) -C Application clean

fastdep:
	+$(MAKE) -C contrib/fastdep-0.15
	
distclean: clean
	$(MAKE) -C contrib/fastdep-0.15 distclean
	$(MAKE) -C tools clean
	
