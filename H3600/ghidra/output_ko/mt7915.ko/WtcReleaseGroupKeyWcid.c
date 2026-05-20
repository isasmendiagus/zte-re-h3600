// module: mt7915.ko
// function: WtcReleaseGroupKeyWcid @ 0xadb9c
// size: 248 bytes
//

uint WtcReleaseGroupKeyWcid(int param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(*(int *)(param_1 + 0x4328) + 0xa797a0));
  if (uVar2 <= param_3) {
    if (-1 < DebugLevel) {
      printk("%s: idx:%d > WTBL_MAX_NUM\n","WtcReleaseGroupKeyWcid",param_3,DebugLevel,param_4);
    }
    return param_3;
  }
  _raw_spin_lock_bh(param_1 + 0x2c30);
  iVar1 = param_3 * 0x10;
  iVar3 = param_1 + 0x1000 + iVar1;
  if (*(char *)(iVar3 + 0xa36) == '\x02') {
    if (*(char *)(iVar3 + 0xa30) == '\0') {
      if (-1 < DebugLevel) {
        printk("%s: try to release non-occupied idx:%d, something wrong?\n","WtcReleaseGroupKeyWcid"
               ,param_3,DebugLevel,param_4);
      }
    }
    else {
      param_3 = 0xffff;
      os_zero_mem(param_1 + iVar1 + 0x1a30,0x10);
      *(undefined1 *)(iVar3 + 0xa30) = 0;
      *(undefined1 *)(iVar3 + 0xa36) = 0;
    }
  }
  _raw_spin_unlock_bh(param_1 + 0x2c30);
  return param_3;
}

