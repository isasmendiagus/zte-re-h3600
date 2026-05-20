// module: mt7915.ko
// function: StaRecUpdateSecKey @ 0x1c32f8
// size: 96 bytes
//

undefined4 StaRecUpdateSecKey(int param_1,undefined4 param_2,int param_3)

{
  undefined4 local_18;
  undefined4 local_14 [2];
  
  local_18 = 0;
  local_14[0] = 0;
  chip_fill_key_install_cmd(*(undefined4 *)(param_1 + 0xa797a0),param_3 + 0x14,1,&local_18,local_14)
  ;
  AndesAppendCmdMsg(param_2,local_18,local_14[0]);
  os_free_mem(local_18);
  return 0;
}

