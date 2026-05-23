// module: mt7915.ko
// function: SetRxvEnCtrlProc @ 0xc0610
// size: 268 bytes
//

undefined4 SetRxvEnCtrlProc(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  char cVar3;
  undefined4 uVar4;
  
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: No parameters!!\n","SetRxvEnCtrlProc");
    return 0;
  }
  iVar2 = rstrtok(param_2,&_LC156);
  if (iVar2 == 0) {
    uVar4 = 1;
    uVar1 = 0;
  }
  else {
    uVar1 = 0;
    cVar3 = '\0';
    uVar4 = 1;
    do {
      if (cVar3 == '\0') {
        uVar1 = os_str_tol(iVar2,0,10);
        iVar2 = rstrtok(0,&_LC156);
        cVar3 = '\x01';
        if (iVar2 == 0) break;
      }
      uVar4 = 0;
      if (-1 < DebugLevel) {
        printk("%s: set wrong parameters\n","SetRxvEnCtrlProc");
      }
      cVar3 = cVar3 + '\x01';
      iVar2 = rstrtok(0,&_LC156);
    } while (iVar2 != 0);
  }
  RxvEnCtrl(param_1,uVar1);
  return uVar4;
}

