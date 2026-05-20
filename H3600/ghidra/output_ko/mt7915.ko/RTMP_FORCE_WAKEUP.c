// module: mt7915.ko
// function: RTMP_FORCE_WAKEUP @ 0xb0d38
// size: 140 bytes
//

void RTMP_FORCE_WAKEUP(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *local_14 [2];
  
  local_14[0] = param_2;
  if (0 < DebugLevel) {
    printk("%s(%s):caller=%pS\n","RTMP_FORCE_WAKEUP",*param_2);
  }
  iVar1 = FUN_000b0a74(param_1,4,0x1d,4,local_14);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s::Failed to enqueue cmd\n","RTMP_FORCE_WAKEUP");
  }
  return;
}

