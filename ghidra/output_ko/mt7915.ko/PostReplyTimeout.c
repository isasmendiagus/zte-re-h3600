// module: mt7915.ko
// function: PostReplyTimeout @ 0x22c514
// size: 412 bytes
//

void PostReplyTimeout(undefined4 param_1,int *param_2)

{
  byte bVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  undefined1 auStack_21 [5];
  
  if (2 < DebugLevel) {
    printk(&_LC1,"PostReplyTimeout");
  }
  if (param_2 == (int *)0x0) {
    if (0 < DebugLevel) {
      printk("%s: GASPeerEntry is NULL\n","PostReplyTimeout");
    }
  }
  else {
    iVar5 = param_2[6];
    if ((*(uint *)(iVar5 + 0xa39f84) & 0x40) == 0) {
      bVar1 = *(byte *)(param_2 + 3);
      *(undefined1 *)(param_2 + 0x14) = 0;
      _raw_spin_lock_bh("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" +
                        (uint)bVar1 * 0x5834 + iVar5 + 0x24);
      piVar6 = param_2 + 0x42;
      piVar4 = *(int **)*piVar6;
      piVar3 = (int *)*piVar6;
      while (piVar2 = piVar4, piVar3 != piVar6) {
        if (piVar2 != (int *)0x0) {
          piVar2[1] = piVar3[1];
        }
        if ((int *)piVar3[1] != (int *)0x0) {
          *(int *)piVar3[1] = *piVar3;
        }
        *piVar3 = 0;
        piVar3[1] = 0;
        os_free_mem(piVar3[3]);
        os_free_mem(piVar3);
        piVar4 = (int *)*piVar2;
        piVar3 = piVar2;
      }
      if (*param_2 != 0) {
        *(int *)(*param_2 + 4) = param_2[1];
      }
      if ((int *)param_2[1] != (int *)0x0) {
        *(int *)param_2[1] = *param_2;
      }
      param_2[0x42] = (int)piVar6;
      *param_2 = 0;
      param_2[1] = 0;
      param_2[0x43] = (int)piVar6;
      _raw_spin_unlock_bh("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" +
                          (uint)bVar1 * 0x5834 + iVar5 + 0x24);
      RTMPReleaseTimer(param_2 + 7,auStack_21);
      param_2[0x40] = param_2[0x40] + 1;
      RTMPReleaseTimer(param_2 + 0x15,auStack_21);
      param_2[0x40] = param_2[0x40] + 2;
      os_free_mem(param_2);
      return;
    }
    if (0 < DebugLevel) {
      printk("%s: fRTMP_ADAPTER_HALT_IN_PROGRESS\n","PostReplyTimeout");
    }
  }
  return;
}

