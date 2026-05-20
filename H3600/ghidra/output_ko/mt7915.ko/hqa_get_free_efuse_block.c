// module: mt7915.ko
// function: hqa_get_free_efuse_block @ 0x2472c4
// size: 88 bytes
//

undefined4 hqa_get_free_efuse_block(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint local_14;
  
  uVar1 = mt_serv_reg_eprm_operation(param_1,0xe);
  uVar2 = *(uint *)(param_1 + 0x1f30);
  local_14 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
             uVar2 >> 0x18;
  sys_ad_move_mem((void *)(param_2 + 0xe),&local_14,4);
  FUN_00246b90(param_2,6,uVar1);
  return uVar1;
}

