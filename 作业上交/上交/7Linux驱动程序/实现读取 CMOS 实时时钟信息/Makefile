
ifneq	($(KERNELRELEASE),)
obj-m	:= cmos.o 

else
KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)
default:	
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	rm -r -f .tmp_versions *.mod.c .*.cmd *.o *.symvers 

endif

