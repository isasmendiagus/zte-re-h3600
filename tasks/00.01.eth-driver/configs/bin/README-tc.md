# tc — modern static iproute2 for the device (Phase 6 tc-flower + Phase 5 QoS)

The on-device stock `tc` is iproute2-ss120521 (2012) — no `flower` filter. busybox has no
usable `tc` either. So we cross-built a modern static `tc` (flower built IN, no dlopen .so, no
libc deps), staged at configs/bin/tc and copied to the initramfs /sbin/tc by stage_userland.sh.

## Build recipe (host, ~2 min)
```sh
cd /tmp && curl -sL -o ip2.tar.xz \
  https://mirrors.edge.kernel.org/pub/linux/utils/net/iproute2/iproute2-6.1.0.tar.xz
tar xf ip2.tar.xz && cd iproute2-6.1.0
CC=arm-linux-gnueabi-gcc ./configure --libbpf_force off
# drop host-lib probes (they linked x86 libelf/libmnl/libselinux):
sed -i -E '/HAVE_SELINUX:=y/d;/LDLIBS \+= -lselinux/d;/-DHAVE_SELINUX/d;/HAVE_ELF:=y/d;/-DHAVE_ELF/d;/LDLIBS \+=  -lelf/d;/HAVE_MNL:=y/d;/LDLIBS \+= -lmnl/d;/-DHAVE_LIBMNL/d' config.mk
# SHARED_LIBS=n => filters (f_flower etc.) compiled INTO tc (a static binary can't dlopen):
make CC=arm-linux-gnueabi-gcc LDFLAGS="-static" SHARED_LIBS=n -j4
arm-linux-gnueabi-strip tc/tc
cp tc/tc <repo>/tasks/00.01.eth-driver/configs/bin/tc
```
Result: ELF ARM EABI5, statically linked, soft-float (gnueabi), ~1.17 MB, `flower` built-in.
Verified on device: `tc -V` = iproute2-6.1.0; `tc filter add dev lan1 ingress protocol ip flower
ip_proto tcp dst_ip X action mirred egress redirect dev lan2` → fires our cls_flower_add.
GOTCHA: flower needs `protocol ip` BEFORE `flower` or `ip_proto`/`dst_ip` are "Illegal".
