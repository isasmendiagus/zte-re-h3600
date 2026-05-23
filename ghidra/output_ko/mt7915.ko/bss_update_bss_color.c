// module: mt7915.ko
// function: bss_update_bss_color @ 0x1c25c0
// size: 96 bytes
//

void bss_update_bss_color(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 local_18;
  undefined4 local_14;
  
  local_18 = 0;
  local_14 = 0;
  os_zero_mem(&local_18,8);
  local_14 = CONCAT22(local_14._2_2_,*(undefined2 *)(param_2 + 0xb0));
  local_18 = 0x8000c;
  AndesAppendCmdMsg(param_3,&local_18,8);
  return;
}

