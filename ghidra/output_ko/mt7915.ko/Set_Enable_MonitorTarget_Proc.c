// module: mt7915.ko
// function: Set_Enable_MonitorTarget_Proc @ 0x4009c
// size: 128 bytes
//

undefined4 Set_Enable_MonitorTarget_Proc(undefined4 param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  char acStack_18 [12];
  
  iVar1 = Set_MonitorTarget_Proc();
  if (iVar1 != 0) {
    if (param_3 < 0x10) {
      sprintf(acStack_18,"%u",param_3);
      uVar2 = Set_MonitorIndex_Proc(param_1,acStack_18);
      return uVar2;
    }
    if (-1 < DebugLevel) {
      printk("The index is over the maximum limit.\n");
    }
  }
  return 0;
}

