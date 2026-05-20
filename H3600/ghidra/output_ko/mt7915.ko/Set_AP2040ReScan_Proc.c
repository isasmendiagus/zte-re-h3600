// module: mt7915.ko
// function: Set_AP2040ReScan_Proc @ 0x333a4
// size: 100 bytes
//

undefined4
Set_AP2040ReScan_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  
  piVar1 = param_1 + *(int *)(*param_1 + 0x3c) * 0x160d;
  APOverlappingBSSScan(param_1,piVar1 + 0xadc92,0x5834,piVar1,param_4);
  SetCommonHtVht(param_1,piVar1 + 0xadc92);
  if (2 < DebugLevel) {
    printk("Set_AP2040ReScan_Proc() Trigger AP ReScan !!!\n");
  }
  return 1;
}

