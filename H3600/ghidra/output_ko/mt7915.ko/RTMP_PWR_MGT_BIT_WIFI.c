// module: mt7915.ko
// function: RTMP_PWR_MGT_BIT_WIFI @ 0xb0bcc
// size: 188 bytes
//

void RTMP_PWR_MGT_BIT_WIFI(undefined4 param_1,undefined2 param_2,undefined1 param_3)

{
  int iVar1;
  undefined4 local_1c;
  
  local_1c = 0;
  if (2 < DebugLevel) {
    printk("%s::--->\n","RTMP_PWR_MGT_BIT_WIFI");
  }
  local_1c._0_3_ = CONCAT12(param_3,param_2);
  iVar1 = FUN_000b0a74(param_1,4,0x1c,4,&local_1c);
  if (iVar1 != 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s::Failed to enqueue cmd\n","RTMP_PWR_MGT_BIT_WIFI");
  }
  if (2 < DebugLevel) {
    printk("%s::<---\n","RTMP_PWR_MGT_BIT_WIFI");
  }
  return;
}

