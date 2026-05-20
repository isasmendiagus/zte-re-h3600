// module: mt7915.ko
// function: RTPCICmdThread @ 0x1d822c
// size: 424 bytes
//

undefined4 RTPCICmdThread(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 local_28;
  int local_24 [2];
  
  iVar2 = *(int *)(param_1 + 0x10);
  iVar3 = (int)&DAT_00285c64 + iVar2;
  local_28 = 0;
  RtmpOSTaskCustomize();
  _raw_spin_lock_bh(iVar3);
  *(undefined4 *)(iVar2 + 0x285c60) = 2;
  _raw_spin_unlock_bh(iVar3);
  do {
    iVar1 = *(int *)(iVar2 + 0x285c60);
    do {
      if (iVar1 != 2) {
LAB_001d82c0:
        if (*(char *)(iVar2 + 0xa77c41) != '\0') goto LAB_001d82cc;
LAB_001d8314:
        local_24[0] = 0;
        _raw_spin_lock_bh(iVar3);
        *(undefined4 *)(iVar2 + 0x285c60) = 4;
        goto LAB_001d834c;
      }
      iVar1 = RtmpOSTaskWait(iVar2,param_1,&local_28);
      if (iVar1 == 0) {
        *(uint *)(iVar2 + 0xa39f84) = *(uint *)(iVar2 + 0xa39f84) | 0x40;
        if (*(char *)(iVar2 + 0xa77c41) == '\0') goto LAB_001d8314;
        goto LAB_001d82cc;
      }
      iVar1 = *(int *)(iVar2 + 0x285c60);
      if (iVar1 == 4) goto LAB_001d82c0;
    } while (*(char *)(iVar2 + 0xa77c41) != '\0');
    CMDHandler(iVar2);
  } while( true );
LAB_001d834c:
  do {
    if (*(int *)(iVar2 + 0x285c54) == 0) {
      _raw_spin_unlock_bh(iVar3);
LAB_001d82cc:
      if (2 < DebugLevel) {
        printk("<---RTPCICmdThread\n");
      }
      RtmpOSTaskNotifyToExit(param_1);
      return 0;
    }
    RTThreadDequeueCmd(iVar2 + 0x285c54,local_24);
  } while (local_24[0] == 0);
  if (*(char *)(local_24[0] + 0xc) == '\x01') {
    if (*(int *)(local_24[0] + 4) != 0) goto LAB_001d83b0;
LAB_001d839c:
    os_free_mem(local_24[0]);
    goto LAB_001d834c;
  }
  if ((*(int *)(local_24[0] + 4) == 0) || (*(int *)(local_24[0] + 8) == 0)) goto LAB_001d839c;
LAB_001d83b0:
  os_free_mem();
  os_free_mem(local_24[0]);
  goto LAB_001d834c;
}

