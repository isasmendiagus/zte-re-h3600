# Out-of-tree build for the ZTE H3600 device kernel (4.1.25 ARMv7).
# The kernel tree is shared with tasks/99.01.linux-stockport/ — we don't
# rebuild the kernel here, we just compile modules against its headers.

obj-m := hello.o kotrace.o

# Defaults — override at the command line if you need to:
#   make KDIR=/some/other/tree ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
KDIR          ?= $(CURDIR)/../../99.01.linux-stockport/linux-4.1.25
ARCH          ?= arm
CROSS_COMPILE ?= arm-linux-gnueabi-

all:
	$(MAKE) -C $(KDIR) M=$(CURDIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) clean

.PHONY: all clean
