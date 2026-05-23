// module: plat-zxylzb_9128S.ko
// function: dump_bmu_reg @ 0x18a00
// size: 444 bytes
//

void dump_bmu_reg(void)

{
  printk("bmu cfg\t\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8000));
  printk("bpp cfg\t\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8004));
  printk("sw alloc bp\t: 0x%x\n",*(undefined4 *)(tm_base + 0x800c));
  printk("sw free bp\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8010));
  printk("sw alloc cfg: 0x%x\n",*(undefined4 *)(tm_base + 0x8014));
  printk("bppi ptr\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8040));
  printk("bppe ptr\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8048));
  printk("pool size\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8058));
  printk("bppe bpcnt\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8080));
  printk("bppi bpcnt\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8088));
  printk("alloc bpcnt\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8090));
  printk("rls bpcnt\t: 0x%x\n",*(undefined4 *)(tm_base + 0x8098));
  printk("bp initsat\t: 0x%x\n",*(undefined4 *)(tm_base + 0x80a0));
  printk("bp stat\t\t: 0x%x\n",*(undefined4 *)(tm_base + 0x80dc));
  printk("bp base\t\t: 0x%x\n",*(undefined4 *)(tm_base + 0xe8));
  printk("bp buf base\t: 0x%x\n",*(undefined4 *)(tm_base + 0xf4));
  return;
}

