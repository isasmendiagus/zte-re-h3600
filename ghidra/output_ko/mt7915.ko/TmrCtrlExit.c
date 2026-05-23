// module: mt7915.ko
// function: TmrCtrlExit @ 0x1d807c
// size: 96 bytes
//

void TmrCtrlExit(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char *pcVar1;
  int iVar2;
  
  iVar2 = *(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10);
  if (iVar2 == 0) {
    return;
  }
  if (0 < DebugLevel) {
    printk("%s: disable TMR report\n","TmrCtrlExit",iVar2,DebugLevel,param_4);
    iVar2 = *(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10);
  }
  *(undefined1 *)(iVar2 + 1) = 0;
  os_free_mem(*(undefined4 *)("Set_RBIST_Capture_Start" + param_1 + 0x10));
  pcVar1 = "Set_RBIST_Capture_Start" + param_1 + 0x10;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  return;
}

