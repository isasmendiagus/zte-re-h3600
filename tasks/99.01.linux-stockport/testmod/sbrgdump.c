/* Dump SBRG indirect RAM via ioremap. Walks ram 0..15, addr 0..1023.
 * Output to printk (read via cat /proc/kmsg).
 * Stock SBRG cmd: tm[0x8014] = addr | (ram<<22) | (read<<27)
 *      ready: tm[0x8018] bit 0
 *      data: tm[0x801C], tm[0x8020], tm[0x8024]
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/delay.h>

static int max_ram = 16;
module_param(max_ram, int, 0);
static int max_addr = 1024;
module_param(max_addr, int, 0);
static unsigned long phys_base = 0x92340000;
module_param(phys_base, ulong, 0);

#define CMD_OFF     0x8014
#define READY_OFF   0x8018
#define DATA0_OFF   0x801C
#define DATA1_OFF   0x8020
#define DATA2_OFF   0x8024

static int __init sbrgdump_init(void) {
    void __iomem *p = ioremap(phys_base, 0x10000);
    int ram, addr, total = 0;
    if (!p) { printk("sbrgdump: ioremap fail\n"); return -ENOMEM; }
    printk("sbrgdump: ioremap %lx OK\n", phys_base);

    for (ram = 0; ram < max_ram; ram++) {
        for (addr = 0; addr < max_addr; addr++) {
            int t = 100;
            u32 v0, v1, v2;
            while (t-- && !(readl(p + READY_OFF) & 1)) udelay(2);
            if (t < 0) continue;
            writel(addr | (ram << 22) | (1u << 27), p + CMD_OFF);
            t = 100;
            while (t-- && !(readl(p + READY_OFF) & 1)) udelay(2);
            if (t < 0) continue;
            v0 = readl(p + DATA0_OFF);
            v1 = readl(p + DATA1_OFF);
            v2 = readl(p + DATA2_OFF);
            if (v0 || v1 || v2) {
                printk("sbrg ram=%d addr=%4d: %08x %08x %08x\n", ram, addr, v0, v1, v2);
                total++;
                if (total > 200) { iounmap(p); printk("sbrgdump: stopped at 200 entries\n"); return 0; }
            }
        }
    }
    printk("sbrgdump: TOTAL %d non-zero entries\n", total);
    iounmap(p);
    return 0;
}

static void __exit sbrgdump_exit(void) {}
module_init(sbrgdump_init);
module_exit(sbrgdump_exit);
MODULE_LICENSE("GPL");
