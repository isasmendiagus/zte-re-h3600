// module: mt7915.ko
// function: MlmeEnqueueForWsc @ 0x12d92c
// size: 484 bytes
//

undefined4
MlmeEnqueueForWsc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,uint param_6,void *param_7,int param_8)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (2 < DebugLevel) {
    printk("-----> MlmeEnqueueForWsc\n");
  }
  if ((*(uint *)(param_1 + 0xa39f84) & 0x40) == 0) {
    if (*(char *)(param_8 + 0x28) == '\0') {
      if (-1 < DebugLevel) {
        printk("%s(): wdev(%d) state: if down!\n","MlmeEnqueueForWsc",*(undefined1 *)(param_8 + 0xc)
              );
        return 0;
      }
    }
    else if (param_6 < 0x901) {
      iVar1 = MlmeQueueFull(param_1 + 0x7960f8,1);
      if (iVar1 == 0) {
        iVar3 = param_1 + 0x796104;
        _raw_spin_lock_bh(iVar3);
        iVar4 = *(int *)(param_1 + 0x796100);
        iVar1 = iVar4 * 0x930 + param_1;
        if (*(char *)(iVar1 + 0x796a2a) != '\0') {
          _raw_spin_unlock_bh(iVar3);
          return 0;
        }
        *(int *)(param_1 + 0x796100) = iVar4 + 1;
        *(int *)(param_1 + 0x7960f8) = *(int *)(param_1 + 0x7960f8) + 1;
        if (iVar4 + 1 == 0x100) {
          *(undefined4 *)(param_1 + 0x796100) = 0;
        }
        iVar2 = param_1 + 0x796000 + iVar4 * 0x930;
        *(undefined1 *)(iVar1 + 0x796a2a) = 1;
        *(undefined4 *)(iVar2 + 0xa08) = param_4;
        *(undefined4 *)(iVar2 + 0xa18) = param_2;
        *(undefined4 *)(iVar2 + 0xa1c) = param_3;
        *(undefined4 *)(iVar2 + 0xa0c) = param_5;
        *(uint *)(iVar2 + 0xa10) = param_6;
        if (param_7 != (void *)0x0) {
          memmove((void *)(param_1 + 0x7960f8 + iVar4 * 0x930 + 0x10),param_7,param_6);
        }
        *(int *)(iVar4 * 0x930 + param_1 + 0x796a34) = param_8;
        _raw_spin_unlock_bh(iVar3);
        if (2 < DebugLevel) {
          printk("<----- MlmeEnqueueForWsc\n");
          return 1;
        }
        return 1;
      }
    }
    else if (-1 < DebugLevel) {
      printk("MlmeEnqueueForWsc: msg too large, size = %ld\n");
      return 0;
    }
  }
  return 0;
}

