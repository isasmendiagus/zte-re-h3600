// module: mt7915.ko
// function: twt_ctrl_acquire_twt_node @ 0x16a884
// size: 352 bytes
//

int twt_ctrl_acquire_twt_node(int param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  
  if (param_2 == 0 || (param_1 == -0x1360 || param_1 == -0x2c38)) {
    if (-1 < DebugLevel) {
      printk("%s: unexpected NULL, please check\n","twt_ctrl_acquire_twt_node");
      return 0;
    }
    return 0;
  }
  iVar5 = param_1 + 0x30d0;
  _raw_spin_lock_bh(iVar5);
  if (*(char *)(param_1 + 0x2c38) != '\0') {
    if (param_1 + 0x2c40 != 0) {
      uVar2 = 0;
      iVar1 = param_1 + 0x2c88;
      iVar4 = param_1 + 0x2c40;
      do {
        iVar3 = iVar1;
        if ((*(byte *)(iVar3 + -0x14) == param_3) && (*(char *)(iVar3 + -0x40) != '\x01')) {
          *(undefined1 *)(param_1 + uVar2 * 0x48 + 0x2c48) = 1;
          if (param_3 == 0) {
            *(char *)(param_1 + 0x2c39) = *(char *)(param_1 + 0x2c39) + -1;
          }
          else {
            *(char *)(param_1 + 0x2c3a) = *(char *)(param_1 + 0x2c3a) + -1;
          }
          _raw_spin_unlock_bh(iVar5);
          return iVar4;
        }
        bVar6 = uVar2 == (byte)(*(char *)(param_1 + 0x2c38) - 1);
        uVar2 = uVar2 + 1;
        if (bVar6) goto LAB_0016a954;
        iVar1 = iVar3 + 0x48;
        iVar4 = iVar3;
      } while (iVar3 != 0);
    }
    if (-1 < DebugLevel) {
      printk("%s: unexpected NULL, please check\n","twt_ctrl_acquire_twt_node");
    }
  }
LAB_0016a954:
  _raw_spin_unlock_bh(iVar5);
  return 0;
}

