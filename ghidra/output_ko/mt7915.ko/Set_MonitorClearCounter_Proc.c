// module: mt7915.ko
// function: Set_MonitorClearCounter_Proc @ 0x33ce4
// size: 156 bytes
//

undefined4
Set_MonitorClearCounter_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  int iVar1;
  int iVar2;
  
  if (0 < DebugLevel) {
    printk("--> %s()\n","Set_MonitorClearCounter_Proc",param_3,DebugLevel,param_4);
  }
  iVar1 = param_1 + 0xa3724e;
  do {
    *(undefined4 *)(iVar1 + -0x12) = 0;
    *(undefined4 *)(iVar1 + -0xe) = 0;
    *(undefined4 *)(iVar1 + -10) = 0;
    iVar2 = iVar1 + 0x44;
    *(undefined4 *)(iVar1 + -0x16) = 0;
    __memzero(iVar1,0x24);
    iVar1 = iVar2;
  } while (iVar2 != param_1 + 0xa3768e);
  if (0 < DebugLevel) {
    printk("<-- %s()\n","Set_MonitorClearCounter_Proc",extraout_r2,DebugLevel,param_4);
  }
  return 1;
}

