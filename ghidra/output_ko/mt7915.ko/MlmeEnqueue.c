// module: mt7915.ko
// function: MlmeEnqueue @ 0x12d5f4
// size: 380 bytes
//

undefined4
MlmeEnqueue(int param_1,undefined4 param_2,undefined4 param_3,uint param_4,void *param_5,
           undefined4 param_6)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if ((*(uint *)(param_1 + 0xa39f84) & 0x140) == 0) {
    if (param_4 < 0x901) {
      iVar2 = MlmeQueueFull(param_1 + 0x7960f8,1);
      if (iVar2 == 0) {
        iVar5 = param_1 + 0x796104;
        _raw_spin_lock_bh(iVar5);
        iVar2 = *(int *)(param_1 + 0x796100);
        iVar3 = iVar2 * 0x930 + param_1;
        if (*(char *)(iVar3 + 0x796a2a) == '\0') {
          *(int *)(param_1 + 0x796100) = iVar2 + 1;
          if (iVar2 + 1 == 0x100) {
            *(undefined4 *)(param_1 + 0x796100) = 0;
          }
          *(int *)(param_1 + 0x7960f8) = *(int *)(param_1 + 0x7960f8) + 1;
          uVar1 = hc_get_chip_wtbl_no_matched_idx(*(undefined4 *)(param_1 + 0xa797a0));
          *(undefined1 *)(iVar3 + 0x796a2a) = 1;
          *(undefined2 *)(iVar3 + 0x796a28) = uVar1;
          iVar4 = param_1 + 0x796000 + iVar2 * 0x930;
          *(undefined4 *)(iVar4 + 0xa08) = param_2;
          *(undefined4 *)(iVar4 + 0xa0c) = param_3;
          *(uint *)(iVar4 + 0xa10) = param_4;
          *(undefined4 *)(iVar3 + 0x796a2c) = param_6;
          *(undefined4 *)(iVar4 + 0xa34) = 0;
          if (param_5 != (void *)0x0) {
            memmove((void *)(param_1 + 0x7960f8 + iVar2 * 0x930 + 0x10),param_5,param_4);
          }
          _raw_spin_unlock_bh(iVar5);
          return 1;
        }
        _raw_spin_unlock_bh(iVar5);
        return 0;
      }
    }
    else if (-1 < DebugLevel) {
      printk("MlmeEnqueue: msg too large, size = %ld\n",param_4);
      return 0;
    }
  }
  return 0;
}

