/*
 * Phase A1 sanity module — verifies our cross-compile toolchain produces
 * a .ko with the right vermagic for this device's kernel (4.1.25 SMP
 * mod_unload ARMv7). Once this loads + prints + unloads cleanly via
 * insmod/rmmod, we know the build env is good enough to invest in
 * kotrace.ko (the actual loader-notifier).
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init hello_init(void)
{
	pr_info("hello: loaded — build env OK\n");
	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("hello: unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ZTE H3600 RE — agus@quecomere");
MODULE_DESCRIPTION("Phase A1 sanity .ko");
