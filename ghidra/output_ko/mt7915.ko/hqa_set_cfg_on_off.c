// module: mt7915.ko
// function: hqa_set_cfg_on_off @ 0x24ba88
// size: 200 bytes
//

undefined4 hqa_set_cfg_on_off(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  
  local_20 = param_2 + 0xc;
  FUN_002474f4(1,4,&local_20,&local_1c);
  FUN_002474f4(1,4,&local_20,&local_18);
  FUN_002474f4(1,4,&local_20,&local_14);
  iVar2 = local_14 * 0xd18 + param_1;
  *(char *)(param_1 + 0x4cc) = (char)local_14;
  *(char *)(iVar2 + 0x11b0) = (char)local_1c;
  *(char *)(iVar2 + 0x11b1) = (char)local_18;
  uVar1 = mt_serv_set_cfg_on_off(param_1);
  printk("%s: type=%u, enable=%u, band_idx=%u\n","hqa_set_cfg_on_off",local_1c,local_18,local_14);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

