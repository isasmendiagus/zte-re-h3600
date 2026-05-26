obj-m := kotrace.o
KDIR := /home/ubuntu/Projects/MYSELF/ZTE/tasks/99.01.linux-stockport/linux-4.1.25
CROSS := arm-buildroot-linux-gnueabihf-
all:
	$(MAKE) -C $(KDIR) M=$(CURDIR) ARCH=arm CROSS_COMPILE=$(CROSS) modules
clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) ARCH=arm CROSS_COMPILE=$(CROSS) clean
