obj-m := memlog.o regtracer.o sbrgdump.o
KDIR := /home/ubuntu/Projects/MYSELF/ZTE/tasks/99.01.linux-stockport/linux-4.1.25
CROSS := arm-buildroot-linux-gnueabihf-
all:
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS) KBUILD_HOSTCFLAGS="-fcommon" HOSTCFLAGS="-fcommon" -C $(KDIR) M=$(CURDIR) modules
clean:
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KDIR) M=$(CURDIR) clean
