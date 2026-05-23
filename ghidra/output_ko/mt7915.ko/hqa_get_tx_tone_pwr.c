// module: mt7915.ko
// function: hqa_get_tx_tone_pwr @ 0x24b4f0
// size: 132 bytes
//

undefined4 hqa_get_tx_tone_pwr(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int local_1c;
  uint local_18;
  undefined4 local_14 [2];
  
  local_1c = param_2 + 0xc;
  local_18 = 0;
  local_14[0] = 0;
  FUN_002474f4(1,4,&local_1c,local_14);
  uVar1 = mt_serv_get_tx_tone_pwr(param_1,local_14[0],&local_18);
  local_18 = local_18 << 0x18 | (local_18 >> 8 & 0xff) << 0x10 | (local_18 >> 0x10 & 0xff) << 8 |
             local_18 >> 0x18;
  sys_ad_move_mem((void *)(param_2 + 0xe),&local_18,4);
  FUN_00246b90(param_2,6,uVar1);
  return uVar1;
}

