obj-m := zte_shim.o

KDIR := /home/ubuntu/Projects/MYSELF/ZTE/H3600/linux-stockport/linux-4.1.25
PWD  := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-buildroot-linux-gnueabihf-

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean ARCH=arm
