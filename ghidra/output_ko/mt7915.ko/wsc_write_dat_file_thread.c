// module: mt7915.ko
// function: wsc_write_dat_file_thread @ 0x1ecb3c
// size: 384 bytes
//

undefined4 wsc_write_dat_file_thread(int param_1)

{
  char cVar1;
  undefined4 extraout_r1;
  undefined4 uVar2;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  int iVar3;
  undefined8 uVar4;
  int local_20;
  void *local_1c;
  
  iVar3 = *(int *)(param_1 + 0x10);
  local_20 = 0;
  if (iVar3 == 0) {
    return 0;
  }
  RtmpOSTaskCustomize();
  uVar2 = extraout_r1;
LAB_001ecb6c:
  if (param_1 == 0) {
    return 0;
  }
  cVar1 = *(char *)(param_1 + 0x18);
  do {
    if (cVar1 != '\0') {
LAB_001ecca8:
      RtmpOSTaskNotifyToExit(param_1);
      return 0;
    }
    RtmpusecDelay(2000,uVar2);
    uVar4 = RtmpOSTaskWait(iVar3,param_1,&local_20);
    uVar2 = (undefined4)((ulonglong)uVar4 >> 0x20);
    if ((int)uVar4 == 0) {
      *(uint *)(iVar3 + 0xa39f84) = *(uint *)(iVar3 + 0xa39f84) | 0x40;
      goto LAB_001ecca8;
    }
    if (local_20 != 0) goto LAB_001ecca8;
    if ((*(int *)(iVar3 + 0x794b20) == 0) || (*(int *)(*(int *)(iVar3 + 0x794b20) + 0x908) == 0)) {
LAB_001ecb8c:
      cVar1 = *(char *)(iVar3 + 0x794b18);
    }
    else {
      os_alloc_mem(iVar3,&local_1c,0x930);
      uVar2 = 0x930;
      if (local_1c == (void *)0x0) goto LAB_001ecb8c;
      __memzero();
      _raw_spin_lock_bh(iVar3 + 0x794b1c);
      memmove(local_1c,*(void **)(iVar3 + 0x794b20),0x930);
      *(undefined4 *)(*(int *)(iVar3 + 0x794b20) + 0x908) = 0;
      __memzero(*(undefined4 *)(iVar3 + 0x794b20),0x900);
      _raw_spin_unlock_bh(iVar3 + 0x794b1c);
      WpsSmProcess(iVar3,local_1c);
      os_free_mem(local_1c);
      cVar1 = *(char *)(iVar3 + 0x794b18);
      uVar2 = extraout_r1_00;
    }
    if (cVar1 != -1) break;
    cVar1 = *(char *)(param_1 + 0x18);
  } while( true );
  if (*(char *)(iVar3 + 0x286285) == '\0') {
    uVar2 = 2;
  }
  else {
    uVar2 = 0;
  }
  if (cVar1 != '\0') {
    uVar2 = 0;
  }
  WscWriteConfToDatFile(iVar3,uVar2);
  *(undefined1 *)(iVar3 + 0x794b18) = 0xff;
  uVar2 = extraout_r1_01;
  goto LAB_001ecb6c;
}

