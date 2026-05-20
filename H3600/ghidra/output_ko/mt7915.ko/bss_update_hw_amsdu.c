// module: mt7915.ko
// function: bss_update_hw_amsdu @ 0x1c30fc
// size: 136 bytes
//

void bss_update_hw_amsdu(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  os_zero_mem(&local_20,0x10);
  local_18 = *(undefined4 *)(iVar1 + 0x1c8);
  local_14 = CONCAT13(local_14._3_1_,0x10000);
  local_20 = 0x10000b;
  local_14 = CONCAT22(local_14._2_2_,2);
  local_1c = 0xffff;
  AndesAppendCmdMsg(param_3,&local_20,0x10);
  return;
}

