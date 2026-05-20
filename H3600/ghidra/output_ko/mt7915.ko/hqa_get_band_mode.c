// module: mt7915.ko
// function: hqa_get_band_mode @ 0x24a274
// size: 152 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 hqa_get_band_mode(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int local_1c;
  uint local_18 [2];
  
  local_1c = param_2 + 0xc;
  local_18[0] = 0;
  local_18[1] = 0;
  FUN_002474f4(1,4,&local_1c,local_18 + 1);
  *(char *)(param_1 + 0x4cc) = (char)local_18[1];
  uVar1 = mt_serv_get_band_mode(param_1);
  printk("%s: band_type=%u\n","hqa_get_band_mode",local_18[0]);
  uVar2 = *(uint *)(param_1 + 0x4c8);
  local_18[0] = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                uVar2 >> 0x18;
  sys_ad_move_mem((void *)(param_2 + 0xe),local_18,4);
  FUN_00246b90(param_2,6,uVar1);
  return uVar1;
}

