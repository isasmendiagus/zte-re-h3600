// module: mt7915.ko
// function: HW_REMOVE_REPT_ENTRY @ 0xb1a68
// size: 116 bytes
//

void HW_REMOVE_REPT_ENTRY(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_11;
  
  if (0 < DebugLevel) {
    printk("%s,CliIdx(%d),caller:%pS\n","HW_REMOVE_REPT_ENTRY",param_2);
  }
  os_zero_mem(&local_11,1);
  local_11 = (undefined1)param_2;
  FUN_000b0a74(param_1,0,0x28,1,&local_11);
  return;
}

