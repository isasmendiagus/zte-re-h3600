// module: mt7915.ko
// function: wdev_idx_reg @ 0x14d490
// size: 348 bytes
//

uint wdev_idx_reg(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int *piVar2;
  undefined2 *puVar3;
  undefined *puVar4;
  uint uVar5;
  int *piVar6;
  
  if (param_2 == 0) {
    return 0xffffffff;
  }
  piVar6 = (int *)(param_1 + 8);
  uVar5 = 0;
  _raw_spin_lock_bh(piVar6);
  piVar2 = piVar6;
  while( true ) {
    piVar2 = piVar2 + 1;
    if (*piVar2 == param_2) {
      if (1 < DebugLevel) {
        puVar4 = &_LC5;
        if (uVar5 != *(byte *)(param_2 + 0xc)) {
          puVar4 = &_LC4;
        }
        printk("wdev(type:%d) already registered and idx(%d) %smatch\n",
               *(undefined4 *)(param_2 + 0x14),(uint)*(byte *)(param_2 + 0xc),puVar4,param_4);
      }
      goto LAB_0014d4f0;
    }
    if (*piVar2 == 0) break;
    uVar5 = uVar5 + 1;
    if (uVar5 == 0x68) {
      *(undefined1 *)(param_2 + 0xc) = 0x68;
      _raw_spin_unlock_bh(piVar6);
      return 0xffffffff;
    }
  }
  puVar3 = (undefined2 *)(param_2 + 0xac4);
  *(int *)(param_1 + uVar5 * 4 + 0xc) = param_2;
  *(undefined4 *)(param_2 + 0xad8) = 0;
  *(undefined1 *)(param_2 + 0xac4) = 0xff;
  *(undefined1 *)(param_2 + 0xac5) = 0xff;
  do {
    puVar3 = puVar3 + 1;
    *puVar3 = 0xffff;
  } while (puVar3 != (undefined2 *)(param_2 + 0xad4));
  *(undefined1 *)(param_2 + 0xad6) = 0xff;
  if (DebugLevel < 1) {
    *(char *)(param_2 + 0xc) = (char)uVar5;
  }
  else {
    printk("%s::Assign wdev_idx=%d with OmacIdx = %d\n","wdev_idx_reg",uVar5,
           *(undefined1 *)(param_2 + 0x29),param_4);
LAB_0014d4f0:
    iVar1 = DebugLevel;
    *(char *)(param_2 + 0xc) = (char)uVar5;
    if (0 < iVar1) {
      printk("Assign wdev_idx=%d\n",uVar5);
    }
  }
  _raw_spin_unlock_bh(piVar6);
  return uVar5;
}

