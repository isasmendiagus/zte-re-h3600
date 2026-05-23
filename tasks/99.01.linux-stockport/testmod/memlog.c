/*
 * memlog.ko - capture stock kernel printk into a ring buffer readable via
 *             /proc/memlog, so we can trigger sysfs dump hooks
 *             (ppBrg/v4Table, ppCla/ghashtable, nppSpa/ghashram, etc) and
 *             read the resulting printk traffic from userspace (the stock
 *             cmdline has loglevel=0 so console output is suppressed).
 *
 * Built against vanilla Linux 4.1.25 headers; vermagic stripped to match
 * stock (4.1.25 SMP mod_unload ARMv7).
 *
 * Usage on stock H3600:
 *   insmod memlog.ko
 *   cat /sys/devices/platform/tm/ppBrg/v4Table > /dev/null    # triggers printk
 *   cat /sys/devices/platform/tm/ppCla/ghashtable > /dev/null
 *   cat /proc/memlog
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/console.h>
#include <linux/kfifo.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>

#define MEMLOG_SIZE (256 * 1024)  /* 256 KB ring */

static DECLARE_KFIFO(memlog_buf, char, MEMLOG_SIZE);
static DEFINE_SPINLOCK(memlog_lock);
static struct proc_dir_entry *memlog_proc;

static void memlog_console_write(struct console *c, const char *s, unsigned int n)
{
	unsigned long flags;
	spin_lock_irqsave(&memlog_lock, flags);
	/* drop oldest if full */
	if (kfifo_avail(&memlog_buf) < n) {
		unsigned int to_drop = n - kfifo_avail(&memlog_buf);
		char tmp[64];
		while (to_drop > 0) {
			unsigned int chunk = to_drop > sizeof(tmp) ? sizeof(tmp) : to_drop;
			kfifo_out(&memlog_buf, tmp, chunk);
			to_drop -= chunk;
		}
	}
	kfifo_in(&memlog_buf, s, n);
	spin_unlock_irqrestore(&memlog_lock, flags);
}

static struct console memlog_console = {
	.name  = "memlog",
	.write = memlog_console_write,
	.flags = CON_PRINTBUFFER | CON_ENABLED | CON_ANYTIME,
	.index = -1,
};

static ssize_t memlog_proc_read(struct file *f, char __user *ubuf,
				 size_t n, loff_t *ppos)
{
	unsigned long flags;
	unsigned int copied = 0;
	int ret;

	spin_lock_irqsave(&memlog_lock, flags);
	ret = kfifo_to_user(&memlog_buf, ubuf, n, &copied);
	spin_unlock_irqrestore(&memlog_lock, flags);

	if (ret < 0)
		return ret;
	return copied;
}

static const struct file_operations memlog_proc_fops = {
	.owner = THIS_MODULE,
	.read  = memlog_proc_read,
};

static int __init memlog_init(void)
{
	INIT_KFIFO(memlog_buf);

	memlog_proc = proc_create("memlog", 0444, NULL, &memlog_proc_fops);
	if (!memlog_proc) {
		pr_err("memlog: proc_create failed\n");
		return -ENOMEM;
	}

	register_console(&memlog_console);
	pr_info("memlog: console registered, /proc/memlog ready (cap=%u)\n",
		(unsigned)MEMLOG_SIZE);
	return 0;
}

static void __exit memlog_exit(void)
{
	unregister_console(&memlog_console);
	if (memlog_proc)
		proc_remove(memlog_proc);
	pr_info("memlog: unloaded\n");
}

module_init(memlog_init);
module_exit(memlog_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Capture stock printk via custom console -> /proc/memlog");
