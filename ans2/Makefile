CONFIG_SIG=n
#CONFIG_MODULE_SIG=n

	obj-m := module_prog.o
	KERNELDIR = /lib/modules/$(shell uname -r)/build
	PWD = $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

