include common.mk

# test:
# 	@echo "EMULATED: $(GCC_ISEMULATED)"
# 	@echo "MINGW: $(GCC_MINGW)"
# 	@echo "CYGMING: $(GCC_CYGMING)"

all:
ifneq ($(GCC_ISMINGW),mingw32)
	+$(MAKE) -C contrib/fastdep-0.15
endif
	+$(MAKE) -C tools
	$(MAKE) -C source
	+$(MAKE) -C Application

install:
	$(MAKE) -C source install

clean:
	$(MAKE) -C source clean
	$(MAKE) -C Application clean

fastdep:
	make -C contrib/fastdep-0.15
	
distclean: clean
	$(MAKE) -C contrib/fastdep-0.15 distclean
	$(MAKE) -C tools clean
	
