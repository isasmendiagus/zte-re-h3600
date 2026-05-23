/*
 * regtracer.ko - poll-based register tracer for ZX279128S
 *
 * Snapshots TM/NPP/PP/CLA/TOPCRM register regions, then a kthread polls
 * every poll_ms milliseconds, diffs against the previous snapshot, and
 * logs each change to /proc/regtrace via printk.
 *
 * Workflow on stock H3600:
 *   insmod memlog.ko                                       # printk capture
 *   insmod regtracer.ko                                    # tracer start
 *   echo 1 > /proc/regtrace                                # take baseline
 *   rmmod tm switch plat-zxylzb-9128S                      # re-init trigger
 *   insmod /path/plat-zxylzb-9128S.ko ; insmod switch.ko ; insmod tm.ko
 *   cat /proc/memlog > /tmp/trace.txt                      # all reg diffs
 *
 * Each diff line: "T+<ms> <region>+<offset:08x>: <old:08x> -> <new:08x>"
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>

static int poll_ms = 5;
module_param(poll_ms, int, 0644);
MODULE_PARM_DESC(poll_ms, "polling interval in ms");

static int max_regs = 0x1000;
module_param(max_regs, int, 0644);
MODULE_PARM_DESC(max_regs, "first N bytes per region (default 4096)");

struct region {
	const char *name;
	unsigned long phys;
	void __iomem *virt;
	u32 *snap;
	unsigned int size;
};

static struct region regions[] = {
	{ "topcrm", 0x94000000, NULL, NULL, 0x1000 },
	{ "tm",     0x92340000, NULL, NULL, 0x10000 },	/* extended to include BMU */
	{ "npp",    0x921c0000, NULL, NULL, 0x4000 },
	{ "pp",     0x92200000, NULL, NULL, 0x4000 },
	{ "cla",    0x92300000, NULL, NULL, 0x4000 },
	{ "sw",     0x92400000, NULL, NULL, 0x4000 },
};

static struct task_struct *poll_task;
static unsigned long start_jiffies;
static atomic_t enabled = ATOMIC_INIT(0);

/* Take baseline snapshot of all regions */
static void snap_all(void)
{
	int i;
	unsigned int off;
	for (i = 0; i < ARRAY_SIZE(regions); i++) {
		struct region *r = &regions[i];
		if (!r->virt || !r->snap) continue;
		for (off = 0; off < r->size; off += 4)
			r->snap[off/4] = readl_relaxed(r->virt + off);
	}
}

/* Diff against snapshot, log changes, update snapshot */
static unsigned int diff_all(void)
{
	int i;
	unsigned int off, changes = 0;
	unsigned long ms = jiffies_to_msecs(jiffies - start_jiffies);
	for (i = 0; i < ARRAY_SIZE(regions); i++) {
		struct region *r = &regions[i];
		u32 cur;
		if (!r->virt || !r->snap) continue;
		for (off = 0; off < r->size; off += 4) {
			cur = readl_relaxed(r->virt + off);
			if (cur != r->snap[off/4]) {
				printk(KERN_INFO "T+%lums %s+%04x: %08x -> %08x\n",
					ms, r->name, off, r->snap[off/4], cur);
				r->snap[off/4] = cur;
				changes++;
				if (changes > 200) {
					printk(KERN_WARNING "regtrace: capped at 200 diffs in one pass\n");
					return changes;
				}
			}
		}
	}
	return changes;
}

static int poll_thread(void *data)
{
	while (!kthread_should_stop()) {
		if (atomic_read(&enabled))
			diff_all();
		msleep(poll_ms);
	}
	return 0;
}

static ssize_t regtrace_proc_write(struct file *f, const char __user *ubuf,
				    size_t n, loff_t *ppos)
{
	char c;
	if (n < 1) return -EINVAL;
	if (copy_from_user(&c, ubuf, 1)) return -EFAULT;
	if (c == '1') {
		printk(KERN_INFO "regtrace: BASELINE (taking snapshot, enabling poll)\n");
		snap_all();
		start_jiffies = jiffies;
		atomic_set(&enabled, 1);
	} else if (c == '0') {
		printk(KERN_INFO "regtrace: poll DISABLED\n");
		atomic_set(&enabled, 0);
	} else if (c == 's') {
		printk(KERN_INFO "regtrace: manual snapshot/diff\n");
		diff_all();
	} else if (c == 'D') {
		/* Full dump of current register values */
		int i;
		unsigned int off;
		printk(KERN_INFO "regtrace: ==== FULL DUMP ====\n");
		for (i = 0; i < ARRAY_SIZE(regions); i++) {
			struct region *r = &regions[i];
			if (!r->virt) continue;
			for (off = 0; off < r->size; off += 4) {
				u32 v = readl_relaxed(r->virt + off);
				if (v != 0)
					printk(KERN_INFO "%s+%04x: %08x\n",
						r->name, off, v);
			}
		}
		printk(KERN_INFO "regtrace: ==== DUMP END ====\n");
	}
	return n;
}

static const struct file_operations regtrace_fops = {
	.owner = THIS_MODULE,
	.write = regtrace_proc_write,
};

static int __init regtracer_init(void)
{
	int i, j;

	if (max_regs > 0x20000) max_regs = 0x20000;
	if (max_regs < 0x100)   max_regs = 0x100;

	for (i = 0; i < ARRAY_SIZE(regions); i++) {
		struct region *r = &regions[i];
		if (r->size > max_regs) r->size = max_regs;
		r->virt = ioremap_nocache(r->phys, r->size);
		if (!r->virt) {
			printk(KERN_ERR "regtrace: ioremap %08lx FAILED\n", r->phys);
			goto cleanup;
		}
		r->snap = kzalloc(r->size, GFP_KERNEL);
		if (!r->snap) {
			printk(KERN_ERR "regtrace: kzalloc FAILED\n");
			goto cleanup;
		}
		printk(KERN_INFO "regtrace: mapped %s phys=%08lx virt=%p size=%u\n",
			r->name, r->phys, r->virt, r->size);
	}

	if (!proc_create("regtrace", 0644, NULL, &regtrace_fops)) {
		printk(KERN_ERR "regtrace: proc_create FAILED\n");
		goto cleanup;
	}

	start_jiffies = jiffies;
	poll_task = kthread_run(poll_thread, NULL, "regtracer");
	if (IS_ERR(poll_task)) {
		printk(KERN_ERR "regtrace: kthread FAILED\n");
		proc_remove(NULL); /* harmless */
		goto cleanup;
	}

	printk(KERN_INFO "regtrace: ready, write 1 to /proc/regtrace to start\n");
	return 0;

cleanup:
	for (j = 0; j < ARRAY_SIZE(regions); j++) {
		if (regions[j].virt) iounmap(regions[j].virt);
		if (regions[j].snap) kfree(regions[j].snap);
	}
	return -ENOMEM;
}

static void __exit regtracer_exit(void)
{
	int i;
	if (poll_task) kthread_stop(poll_task);
	remove_proc_entry("regtrace", NULL);
	for (i = 0; i < ARRAY_SIZE(regions); i++) {
		if (regions[i].virt) iounmap(regions[i].virt);
		if (regions[i].snap) kfree(regions[i].snap);
	}
	printk(KERN_INFO "regtrace: unloaded\n");
}

module_init(regtracer_init);
module_exit(regtracer_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ZX279128S register tracer (poll-based diff)");
