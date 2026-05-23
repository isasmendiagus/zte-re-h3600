// module: mt7915.ko
// function: get_scan_ctrl_by_wdev @ 0x14a8c0
// size: 140 bytes
//

int get_scan_ctrl_by_wdev(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_2 == 0) {
    printk(&_LC49,0x8e4,param_3,param_4,param_4);
    dump_stack();
    if (iRam00000abc != 0) goto LAB_0014a938;
  }
  else if (*(int *)(param_2 + 0xabc) != 0) {
    iVar1 = HcGetBandByWdev(param_2);
    return iVar1 * 0xaf5d8 + param_1 + 0x829270;
  }
  printk(&_LC48,0x8e5);
  dump_stack();
LAB_0014a938:
  return param_1 + 0x829270;
}

