// module: mt7915.ko
// function: twt_ctrl_release_twt_node @ 0x16a9e4
// size: 332 bytes
//

undefined4 twt_ctrl_release_twt_node(int param_1,int param_2,int param_3)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (param_2 != 0 && (param_1 != -0x1360 && param_1 != -0x2c38)) {
    _raw_spin_lock_bh(param_1 + 0x30d0);
    if (*(char *)(param_3 + 8) == '\0') {
      uVar4 = 0;
      if (-1 < DebugLevel) {
        printk("%s: try to release non-occupied tbl_i=%d, please check\n",
               "twt_ctrl_release_twt_node",*(undefined1 *)(param_3 + 9));
      }
    }
    else {
      cVar1 = *(char *)(param_3 + 0x34);
      uVar2 = *(undefined1 *)(param_3 + 9);
      os_zero_mem(param_3,0x48);
      if (cVar1 == '\0') {
        *(char *)(param_1 + 0x2c39) = *(char *)(param_1 + 0x2c39) + '\x01';
      }
      else {
        *(char *)(param_1 + 0x2c3a) = *(char *)(param_1 + 0x2c3a) + '\x01';
      }
      *(undefined1 *)(param_3 + 9) = uVar2;
      iVar3 = DebugLevel;
      *(char *)(param_3 + 0x34) = cVar1;
      *(undefined1 *)(param_3 + 8) = 0;
      if (iVar3 < 3) {
        uVar4 = 1;
      }
      else {
        printk("%s: tbl_i=%d\n","twt_ctrl_release_twt_node",uVar2);
        uVar4 = 1;
      }
    }
    _raw_spin_unlock_bh(param_1 + 0x30d0);
    return uVar4;
  }
  if (-1 < DebugLevel) {
    printk("%s: unexpected NULL, please check\n","twt_ctrl_release_twt_node");
    return 0;
  }
  return 0;
}

