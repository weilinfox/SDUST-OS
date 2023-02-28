ifneq	($(KERNELRELEASE),)
obj-m	:= kello.o

else
KVERSION := $(shell uname -r)
KDIR	 := /lib/modules/$(KVERSION)/build
PWD	 := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	rm -r -f .tmp_versions *.mod.c *.cmd *.o *.symvers
endif

