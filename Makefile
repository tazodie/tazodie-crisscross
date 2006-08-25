all:
	make -C contrib/fastdep-0.16
	make -C source
	
clean:
	make -C contrib/fastdep-0.16 clean
	make -C source clean
