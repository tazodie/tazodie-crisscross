all:
	make -C contrib/fastdep-0.15
	make -C source

clean:
	make -C source clean
	
distclean:
	make -C contrib/fastdep-0.15 distclean
	make -C source clean
