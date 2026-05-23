obj-m := memlog.o regtracer.o sbrgdump.o
KDIR := /home/ubuntu/Projects/MYSELF/ZTE/H3600/linux-stockport/linux-4.1.25
all:
	$(MAKE) ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- KBUILD_HOSTCFLAGS="-fcommon" HOSTCFLAGS="-fcommon" -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -C $(KDIR) M=$(PWD) clean
