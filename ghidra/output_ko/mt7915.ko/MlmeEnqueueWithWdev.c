// module: mt7915.ko
// function: MlmeEnqueueWithWdev @ 0x12d770
// size: 440 bytes
//

undefined4
MlmeEnqueueWithWdev(int param_1,undefined4 param_2,undefined4 param_3,uint param_4,void *param_5,
                   undefined4 param_6,int param_7)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (param_7 == 0) {
    printk(&_LC54,0x1451);
    dump_stack();
  }
  if ((*(uint *)(param_1 + 0xa39f84) & 0x140) == 0) {
    if (*(char *)(param_7 + 0x28) == '\0') {
      if (-1 < DebugLevel) {
        printk("%s(): wdev(%d) state: if down!\n","MlmeEnqueueWithWdev",
               *(undefined1 *)(param_7 + 0xc));
        return 0;
      }
    }
    else if (param_4 < 0x901) {
      iVar2 = MlmeQueueFull(param_1 + 0x7960f8,1);
      if (iVar2 == 0) {
        _raw_spin_lock_bh(param_1 + 0x796104);
        iVar3 = *(int *)(param_1 + 0x796100);
        *(int *)(param_1 + 0x7960f8) = *(int *)(param_1 + 0x7960f8) + 1;
        iVar2 = iVar3 + 1;
        *(int *)(param_1 + 0x796100) = iVar2;
        if (iVar2 == 0x100) {
          *(undefined4 *)(param_1 + 0x796100) = 0;
        }
        uVar1 = hc_get_chip_wtbl_no_matched_idx(*(undefined4 *)(param_1 + 0xa797a0));
        iVar3 = iVar3 * 0x930;
        iVar2 = param_1 + iVar3;
        iVar4 = param_1 + 0x796000 + iVar3;
        *(undefined1 *)(iVar2 + 0x796a2a) = 1;
        *(undefined2 *)(iVar2 + 0x796a28) = uVar1;
        *(undefined4 *)(iVar4 + 0xa08) = param_2;
        *(undefined4 *)(iVar4 + 0xa0c) = param_3;
        *(uint *)(iVar4 + 0xa10) = param_4;
        *(undefined4 *)(iVar2 + 0x796a2c) = param_6;
        *(int *)(iVar4 + 0xa34) = param_7;
        if (param_5 != (void *)0x0) {
          memmove((void *)(param_1 + 0x7960f8 + iVar3 + 0x10),param_5,param_4);
        }
        _raw_spin_unlock_bh(param_1 + 0x796104);
        return 1;
      }
    }
    else if (-1 < DebugLevel) {
      printk("MlmeEnqueue: msg too large, size = %ld\n",param_4);
      return 0;
    }
  }
  return 0;
}

