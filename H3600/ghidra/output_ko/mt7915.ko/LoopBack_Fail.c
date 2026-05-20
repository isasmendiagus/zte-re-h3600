// module: mt7915.ko
// function: LoopBack_Fail @ 0x28d538
// size: 72 bytes
//

void LoopBack_Fail(int param_1,undefined4 param_2)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0xa3bafc) != 0) {
    return;
  }
  *(undefined4 *)(param_1 + 0xa3bb00) = param_2;
  iVar1 = DebugLevel;
  *(undefined4 *)(param_1 + 0xa3bafc) = 2;
  if (iVar1 < 3) {
    return;
  }
  printk("%s, FailReason = %d\n","LoopBack_Fail",param_2);
  return;
}

