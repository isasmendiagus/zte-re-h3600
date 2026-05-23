// module: mt7915.ko
// function: wdev_idx_unreg @ 0x14d354
// size: 316 bytes
//

undefined4 wdev_idx_unreg(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  
  if (param_2 == 0) {
    return 0xffffffff;
  }
  piVar4 = (int *)(param_1 + 8);
  iVar2 = 0;
  _raw_spin_lock_bh(piVar4);
  piVar1 = piVar4;
  do {
    piVar1 = piVar1 + 1;
    if (*piVar1 == param_2) {
      if (1 < DebugLevel) {
        printk("unregister wdev(type:%d, idx:%d) from wdev_list\n",*(undefined4 *)(param_2 + 0x14),
               *(undefined1 *)(param_2 + 0xc));
      }
      *(undefined4 *)(param_1 + (iVar2 + 2) * 4 + 4) = 0;
      *(undefined1 *)(param_2 + 0xc) = 0x68;
      _raw_spin_unlock_bh(piVar4);
      return 0;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0x68);
  if ((-1 < DebugLevel) &&
     (printk("Cannot found wdev(%p, type:%d, idx:%d) in wdev_list\n",param_2,
             *(undefined4 *)(param_2 + 0x14),*(undefined1 *)(param_2 + 0xc)), 0 < DebugLevel)) {
    printk("Dump wdev_list:\n");
  }
  puVar3 = (undefined4 *)(param_1 + 0xc);
  iVar2 = 0;
  do {
    if (0 < DebugLevel) {
      printk("Idx %d: 0x%p\n",iVar2,*puVar3);
    }
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar2 != 0x68);
  _raw_spin_unlock_bh(piVar4);
  return 0xffffffff;
}

