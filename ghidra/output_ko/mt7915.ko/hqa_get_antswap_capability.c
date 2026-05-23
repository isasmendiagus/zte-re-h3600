// module: mt7915.ko
// function: hqa_get_antswap_capability @ 0x247428
// size: 120 bytes
//

undefined4 hqa_get_antswap_capability(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  uint local_14 [2];
  
  printk(&_LC20,"hqa_get_antswap_capability");
  uVar1 = mt_serv_get_antswap_capability(param_1,local_14);
  printk("antswap_support = %x\n",local_14[0]);
  local_14[0] = local_14[0] << 0x18 | (local_14[0] >> 8 & 0xff) << 0x10 |
                (local_14[0] >> 0x10 & 0xff) << 8 | local_14[0] >> 0x18;
  sys_ad_move_mem((void *)(param_2 + 0xe),local_14,4);
  FUN_00246b90(param_2,6,uVar1);
  return uVar1;
}

