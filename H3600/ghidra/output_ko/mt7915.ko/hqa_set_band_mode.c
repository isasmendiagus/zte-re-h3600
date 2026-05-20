// module: mt7915.ko
// function: hqa_set_band_mode @ 0x24a310
// size: 156 bytes
//

undefined4 hqa_set_band_mode(int param_1,int param_2)

{
  undefined4 uVar1;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14 [2];
  
  local_1c = param_2 + 0xc;
  local_18 = 0;
  local_14[0] = 0;
  FUN_002474f4(1,4,&local_1c,&local_18);
  FUN_002474f4(1,4,&local_1c,local_14);
  *(undefined4 *)(param_1 + 0x4c4) = local_18;
  *(undefined4 *)(param_1 + 0x4c8) = local_14[0];
  uVar1 = mt_serv_set_band_mode(param_1);
  printk("%s: band_mode=%u, band_type=%u\n","hqa_set_band_mode",local_18,local_14[0]);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

