#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
static int __init testmod_init(void) { printk("testmod loaded\n"); return 0; }
static void __exit testmod_exit(void) { printk("testmod unloaded\n"); }
module_init(testmod_init);
module_exit(testmod_exit);
MODULE_LICENSE("GPL");
