// module: mt7915.ko
// function: MtPwrLimitTblChProc @ 0x152438
// size: 136 bytes
//

void MtPwrLimitTblChProc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                        undefined1 param_5)

{
  char cVar1;
  
  if (*(char *)(param_1 + 0xa7863c) == '\0') {
    cVar1 = *(char *)(param_1 + 0xa7863d);
  }
  else {
    MtCmdPwrLimitTblUpdate(param_1,param_2,0,param_3,param_4,param_5);
    cVar1 = *(char *)(param_1 + 0xa7863d);
  }
  if (cVar1 == '\0') {
    return;
  }
  MtCmdPwrLimitTblUpdate(param_1,param_2,1,param_3,param_4,param_5);
  return;
}

