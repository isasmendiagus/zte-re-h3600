// module: mt7915.ko
// function: traversal_func_dump_entry_psm_by_aid @ 0x14c864
// size: 472 bytes
//

undefined4 traversal_func_dump_entry_psm_by_aid(int param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0xc);
  iVar2 = hc_get_chip_dbg(*(undefined4 *)(iVar4 + 0xa797a0));
  iVar1 = jiffies;
  if (*param_2 != (uint)*(ushort *)(param_1 + 0xf8)) {
    return 0;
  }
  if (DebugLevel < 1) goto LAB_0014c8c8;
  printk("dump PSM info for AID:%d\n");
  if (DebugLevel < 1) {
LAB_0014c9c0:
    if ((DebugLevel < 1) || (printk(&_LC106,*(undefined1 *)(param_1 + 0xaf8)), DebugLevel < 1))
    goto LAB_0014c8c8;
    printk("\t%-9d",*(undefined4 *)(param_1 + 0xae8));
  }
  else {
    printk("\n%-19s\t%s\t%s\t%s\t%-9s\t%s\n",&_LC76,&_LC77,&_LC78,&_LC79,"NoRxData",
           "SLEEP TIME(msec)");
    if (DebugLevel < 1) goto LAB_0014c8c8;
    printk("%02x:%02x:%02x:%02x:%02x:%02x  ",*(undefined1 *)(param_1 + 0xec),
           *(undefined1 *)(param_1 + 0xed),*(undefined1 *)(param_1 + 0xee),
           *(undefined1 *)(param_1 + 0xef),*(undefined1 *)(param_1 + 0xf0),
           *(undefined1 *)(param_1 + 0xf1));
    if (0 < DebugLevel) {
      printk(&_LC106,*(undefined2 *)(param_1 + 0xe0));
      if (DebugLevel < 1) goto LAB_0014c8c8;
      printk(&_LC106,*(undefined1 *)(param_1 + 0xe4));
      goto LAB_0014c9c0;
    }
  }
  if (0 < DebugLevel) {
    uVar3 = 0;
    if (*(char *)(param_1 + 0xaf8) != '\0') {
      uVar3 = jiffies_to_msecs(iVar1 - *(int *)(param_1 + 0xaec));
    }
    printk(&_LC108,uVar3);
  }
LAB_0014c8c8:
  if (*(code **)(iVar2 + 0x24) == (code *)0x0) {
    return 1;
  }
  (**(code **)(iVar2 + 0x24))(*(undefined4 *)(iVar4 + 0xa797a0),*(undefined2 *)(param_1 + 0xe0));
  return 1;
}

