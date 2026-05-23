// module: mt7915.ko
// function: MlmeDynamicTxRateSwitchingNew @ 0xb1788
// size: 88 bytes
//

void MlmeDynamicTxRateSwitchingNew(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_000b0a74(param_1,4,0x24,0,0);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s::Failed to enqueue cmd\n","MlmeDynamicTxRateSwitchingNew");
    return;
  }
  return;
}

