// module: mt7915.ko
// function: TmrCtrl @ 0x1d80e0
// size: 328 bytes
//

void TmrCtrl(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_2 == 0) {
    TmrCtrlExit();
  }
  else {
    TmrCtrlInit();
    if (param_2 == 1) {
      if (0 < DebugLevel) {
        printk("%s: enable TMR report, as Initialiter\n","TmrCtrl");
      }
      AsicSetTmrCR(param_1,1,0);
      if (*(char *)(param_1 + 0x79504d) == '\0') {
        return;
      }
      AsicSetTmrCR(param_1,1,1,param_4);
      return;
    }
    if (param_2 == 2) {
      if (0 < DebugLevel) {
        printk("%s: enable TMR report, as Responser\n","TmrCtrl");
      }
      AsicSetTmrCR(param_1,2,0);
      if (*(char *)(param_1 + 0x79504d) == '\0') {
        return;
      }
      AsicSetTmrCR(param_1,2,1,param_4);
      return;
    }
  }
  if (0 < DebugLevel) {
    printk("%s: disable TMR report\n","TmrCtrl");
  }
  AsicSetTmrCR(param_1,param_2,0);
  if (*(char *)(param_1 + 0x79504d) == '\0') {
    return;
  }
  AsicSetTmrCR(param_1,param_2,1,param_4);
  return;
}

