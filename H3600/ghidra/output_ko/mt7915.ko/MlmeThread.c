// module: mt7915.ko
// function: MlmeThread @ 0x12f22c
// size: 204 bytes
//

undefined4 MlmeThread(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_14;
  
  iVar2 = *(int *)(param_1 + 0x10);
  local_14 = 0;
  if (iVar2 != 0) {
    RtmpOSTaskCustomize();
    while( true ) {
      if (*(char *)(param_1 + 0x18) != '\0') break;
      iVar1 = RtmpOSTaskWait(iVar2,param_1,&local_14);
      if (iVar1 == 0) {
        *(uint *)(iVar2 + 0xa39f84) = *(uint *)(iVar2 + 0xa39f84) | 0x40;
        break;
      }
      if ((*(char *)(iVar2 + 0xa77c41) == '\0') && (*(char *)(iVar2 + 0x7960f1) == '\0')) {
        MlmeHandler(iVar2);
      }
    }
  }
  if (2 < DebugLevel) {
    printk("<---%s\n","MlmeThread");
  }
  RtmpOSTaskNotifyToExit(param_1);
  return 0;
}

