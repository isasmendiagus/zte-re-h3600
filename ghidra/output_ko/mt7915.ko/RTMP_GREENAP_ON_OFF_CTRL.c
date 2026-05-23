// module: mt7915.ko
// function: RTMP_GREENAP_ON_OFF_CTRL @ 0xb0fb8
// size: 96 bytes
//

void RTMP_GREENAP_ON_OFF_CTRL(undefined4 param_1,undefined1 param_2,undefined1 param_3)

{
  int iVar1;
  undefined1 local_a;
  undefined1 local_9;
  
  local_a = param_2;
  local_9 = param_3;
  iVar1 = FUN_000b0a74(param_1,0,0x34,2,&local_a);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s::Failed to enqueue cmd\n","RTMP_GREENAP_ON_OFF_CTRL");
  }
  return;
}

