// module: mt7915.ko
// function: ser_ctrl_task @ 0xb1e18
// size: 196 bytes
//

void ser_ctrl_task(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 local_1c [2];
  
  iVar3 = *(int *)(param_1 + 0x10);
  local_1c[0] = 0;
  if (iVar3 != 0) {
    RtmpOSTaskCustomize(param_1);
    iVar4 = iVar3 + 0x285d34;
    _raw_spin_lock_bh(iVar4);
    *(undefined4 *)(iVar3 + 0x285d2c) = 2;
    _raw_spin_unlock_bh(iVar4);
    if (param_1 != 0) {
      cVar1 = *(char *)(param_1 + 0x18);
      while ((cVar1 == '\0' && (iVar2 = RtmpOSTaskWait(iVar3,param_1,local_1c), iVar2 != 0))) {
        HwRecoveryFromError(iVar3);
        cVar1 = *(char *)(param_1 + 0x18);
      }
    }
    _raw_spin_lock_bh(iVar4);
    *(undefined4 *)(iVar3 + 0x285d2c) = 0;
    _raw_spin_unlock_bh(iVar4);
    RtmpOSTaskNotifyToExit(param_1);
  }
  return;
}

