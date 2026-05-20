// module: mt7915.ko
// function: bss_update_prot_info @ 0x1c246c
// size: 136 bytes
//

void bss_update_prot_info(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  os_zero_mem(&local_30,0x18);
  local_2c = *(undefined4 *)(param_2 + 0xf4);
  local_28 = *(undefined4 *)(param_2 + 0xf8);
  local_24 = *(undefined4 *)(param_2 + 0x100);
  local_20._0_3_ = CONCAT12(*(undefined1 *)(param_2 + 0xfc),*(undefined2 *)(param_2 + 0xf8));
  local_30 = 0x18000e;
  AndesAppendCmdMsg(param_3,&local_30,0x18);
  return;
}

