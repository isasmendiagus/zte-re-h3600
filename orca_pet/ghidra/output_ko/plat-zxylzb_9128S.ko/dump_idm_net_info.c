// module: plat-zxylzb_9128S.ko
// function: dump_idm_net_info @ 0x161dc
// size: 144 bytes
//

void dump_idm_net_info(uint param_1)

{
  int iVar1;
  
  if (1 < param_1) {
    printk("invalid port %d\n");
    return;
  }
  iVar1 = *(int *)((int)&idm_netdev + param_1 * 4);
  printk(&_LC55,iVar1);
  printk("irq     %u\n",*(undefined4 *)(iVar1 + 0x598));
  printk("irq_err %u\n",*(undefined4 *)(iVar1 + 0x59c));
  printk("poll    %u\n",*(undefined4 *)(iVar1 + 0x5a0));
  printk("rx int  %u\n",*(undefined4 *)(iVar1 + 0x5a4));
  printk("tx int  %u\n",*(undefined4 *)(iVar1 + 0x5a8));
  return;
}

