// module: mt7915.ko
// function: Set_CSPeriod_Proc @ 0x1013c0
// size: 88 bytes
//

undefined4 Set_CSPeriod_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 uVar2;
  
  uVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + 0xa37725) = uVar2;
  if (2 < iVar1) {
    printk("Set_CSPeriod_Proc::(CSPeriod=%d)\n",uVar2);
  }
  return 1;
}

