// module: mt7915.ko
// function: HwCtrlThread @ 0xb2184
// size: 372 bytes
//

undefined4 HwCtrlThread(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 local_1c [2];
  
  iVar3 = *(int *)(param_1 + 0x10);
  local_1c[0] = 0;
  if (iVar3 != 0) {
    iVar5 = iVar3 + 0x285ca8;
    RtmpOSTaskCustomize();
    _raw_spin_lock_bh(iVar5);
    *(undefined4 *)(iVar3 + 0x285ca4) = 2;
    _raw_spin_unlock_bh(iVar5);
    iVar2 = *(int *)(iVar3 + 0x285ca4);
    while (iVar2 == 2) {
      iVar2 = RtmpOSTaskWait(iVar3,param_1,local_1c);
      if (iVar2 == 0) {
        *(uint *)(iVar3 + 0xa39f84) = *(uint *)(iVar3 + 0xa39f84) | 0x40;
        break;
      }
      if (*(int *)(iVar3 + 0x285ca4) == 4) break;
      FUN_000b1f24(iVar3);
      iVar2 = *(int *)(iVar3 + 0x285ca4);
      *(int *)(iVar3 + 0x285cdc) = *(int *)(iVar3 + 0x285cdc) + 1;
    }
    _raw_spin_lock_bh(iVar5);
    *(undefined4 *)(iVar3 + 0x285ca4) = 4;
    iVar2 = *(int *)(iVar3 + 0x285c98);
    while (iVar2 != 0) {
      while (iVar4 = *(int *)(iVar3 + 0x285c9c), iVar4 != 0) {
        uVar1 = *(undefined4 *)(iVar4 + 0x3c);
        *(int *)(iVar3 + 0x285c98) = iVar2 + -1;
        if (iVar2 + -1 == 0) {
          *(undefined4 *)(iVar3 + 0x285ca0) = 0;
        }
        *(undefined4 *)(iVar3 + 0x285c9c) = uVar1;
        if (*(char *)(iVar4 + 0x10) != '\0') {
          complete(iVar4 + 0x14);
        }
        os_kref_put(iVar4 + 0x38,free_hwcmd);
        iVar2 = *(int *)(iVar3 + 0x285c98);
        if (iVar2 == 0) goto LAB_000b22a4;
      }
    }
LAB_000b22a4:
    _raw_spin_unlock_bh(iVar5);
    if (-1 < DebugLevel) {
      printk("<---%s\n","HwCtrlThread");
    }
    RtmpOSTaskNotifyToExit(param_1);
  }
  return 0;
}

