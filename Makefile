all:
	make -C contrib/fastdep-0.16
	make -C source

clean:
	make -C source clean
	
distclean:
	make -C contrib/fastdep-0.16 clean
	make -C source clean
