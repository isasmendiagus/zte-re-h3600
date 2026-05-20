// module: mt7915.ko
// function: hqa_get_cfg_on_off @ 0x24b574
// size: 156 bytes
//

undefined4 hqa_get_cfg_on_off(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14 [2];
  
  local_20 = param_2 + 0xc;
  local_1c = 0;
  local_18 = 0;
  local_14[0] = 0;
  FUN_002474f4(1,4,&local_20,&local_1c);
  FUN_002474f4(1,4,&local_20,&local_18);
  uVar1 = mt_serv_get_cfg_on_off(param_1,local_1c,local_14);
  local_14[0] = local_14[0] << 0x18 | (local_14[0] >> 8 & 0xff) << 0x10 |
                (local_14[0] >> 0x10 & 0xff) << 8 | local_14[0] >> 0x18;
  sys_ad_move_mem((void *)(param_2 + 0xe),local_14,4);
  FUN_00246b90(param_2,6,uVar1);
  return uVar1;
}

