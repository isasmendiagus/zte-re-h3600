// module: plat-zxylzb_9128S.ko
// function: dump_pon_tm_net_info @ 0x1aa64
// size: 144 bytes
//

void dump_pon_tm_net_info(uint param_1)

{
  int iVar1;
  
  if (1 < param_1) {
    printk("invalid port %d\n");
    return;
  }
  iVar1 = *(int *)((int)&pon_tm_netdev + param_1 * 4);
  printk(&_LC35,iVar1);
  printk("irq     %u\n",*(undefined4 *)(iVar1 + 0x5a0));
  printk("irq_err %u\n",*(undefined4 *)(iVar1 + 0x5a4));
  printk("poll    %u\n",*(undefined4 *)(iVar1 + 0x5a8));
  printk("rx int  %u\n",*(undefined4 *)(iVar1 + 0x5ac));
  printk("tx int  %u\n",*(undefined4 *)(iVar1 + 0x5b0));
  return;
}

