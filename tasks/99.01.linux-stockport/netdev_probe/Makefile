obj-m := netdev_probe.o
KDIR := ../linux-4.1.25
PWD  := $(shell pwd)
CROSS := arm-buildroot-linux-gnueabihf-

all:
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KDIR) M=$(PWD) clean
