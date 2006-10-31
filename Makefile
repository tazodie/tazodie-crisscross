all:
	+make -C contrib/fastdep-0.15
	+make -C source
	+make -C Application

install:
	make -C source install

clean:
	make -C source clean
	make -C Application clean
	
distclean: clean
	make -C contrib/fastdep-0.15 distclean
