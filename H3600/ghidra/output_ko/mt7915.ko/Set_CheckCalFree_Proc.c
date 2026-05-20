// module: mt7915.ko
// function: Set_CheckCalFree_Proc @ 0x128804
// size: 176 bytes
//

undefined4 Set_CheckCalFree_Proc(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x94) == (code *)0x0) {
    if (DebugLevel < 1) {
      return 0;
    }
    printk("Not Support CalFree Merge Check!\n");
    return 0;
  }
  iVar1 = (**(code **)(iVar1 + 0x94))(param_1);
  if (iVar1 == 0) {
    if (0 < DebugLevel) {
      printk("CalFree data has not been merged!!\n");
      return 1;
    }
  }
  else if (0 < DebugLevel) {
    printk("CalFree data has been merged!!\n");
    return 1;
  }
  return 1;
}

