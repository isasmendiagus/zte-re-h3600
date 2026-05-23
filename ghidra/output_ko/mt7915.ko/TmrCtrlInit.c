// module: mt7915.ko
// function: TmrCtrlInit @ 0x1d7f28
// size: 340 bytes
//

undefined4 TmrCtrlInit(int param_1,int param_2)

{
  undefined4 uVar1;
  int local_1c [2];
  
  uVar1 = 0;
  local_1c[0] = 0;
  if (*(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10) == 0) {
    uVar1 = os_alloc_mem(param_1,local_1c,0xc);
    if (local_1c[0] == 0) {
      if (DebugLevel < 0) {
        return uVar1;
      }
      printk("%s(): alloc TmrCtrl fail!\n","TmrCtrlInit");
      return uVar1;
    }
    *(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10) = local_1c[0];
    *(undefined1 *)(local_1c[0] + 8) = 8;
    *(undefined1 *)(*(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10) + 9) = 10;
LAB_001d7fd4:
    if (*(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10) == 0) {
      return 1;
    }
    if (param_2 == 1) {
      if (0 < DebugLevel) {
        printk("%s: enable TMR report, as Initialiter\n","TmrCtrlInit");
      }
      goto LAB_001d7f7c;
    }
  }
  else {
    if (-1 < DebugLevel) {
      printk("%s(): pTmrCtrlStruct is allocated.\n","TmrCtrlInit");
      goto LAB_001d7fd4;
    }
    uVar1 = 0;
    if (param_2 == 1) goto LAB_001d7f7c;
  }
  if (0 < DebugLevel) {
    printk("%s: enable TMR report, as Responder\n","TmrCtrlInit");
  }
LAB_001d7f7c:
  *(char *)(*(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10) + 1) = (char)param_2;
  AsicSetTmrCR(param_1,param_2,0);
  return uVar1;
}

