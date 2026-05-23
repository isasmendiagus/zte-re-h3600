// module: mt7915.ko
// function: NICUpdateRawCountersNew @ 0xb172c
// size: 88 bytes
//

void NICUpdateRawCountersNew(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_000b0a74(param_1,4,0x25,0,0);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s::Failed to enqueue cmd\n","NICUpdateRawCountersNew");
    return;
  }
  return;
}

