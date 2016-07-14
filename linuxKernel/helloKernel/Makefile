KERNELDIR := /usr/src/linux-source-3.13.0/

PWD := $(shell pwd)

obj-m := hello.o

default:
	make -C $(KERNELDIR) M=$(PWD) modules
clean:
	rm -rf *.o *.mod.c .tmp_versions *.cmd *.ko 

