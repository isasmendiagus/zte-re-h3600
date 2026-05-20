// module: mt7915.ko
// function: Set_DfsZeroWaitCacTime_Proc @ 0x231a6c
// size: 92 bytes
//

undefined4 Set_DfsZeroWaitCacTime_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 uVar2;
  
  uVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + 0x7953f8) = uVar2;
  if (2 < iVar1) {
    printk("[%s]CacTime=%d/%d\n","Set_DfsZeroWaitCacTime_Proc",uVar2,uVar2);
  }
  return 1;
}

