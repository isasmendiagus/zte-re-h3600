// module: mt7915.ko
// function: hqa_get_ibf_status_ext @ 0x247b24
// size: 204 bytes
//

undefined4 hqa_get_ibf_status_ext(int param_1,int param_2)

{
  int iVar1;
  int iStack_1c;
  undefined4 local_18;
  uint local_14;
  
  param_1 = (uint)*(byte *)(param_1 + 0x4cc) * 0xd18 + param_1;
  iStack_1c = param_2 + 0xc;
  local_14 = 0;
  local_18 = 0;
  iVar1 = *(int *)(param_1 + 0x11d0);
  FUN_002474f4(1,4,&iStack_1c,&local_18);
  local_14 = (uint)*(byte *)(param_1 + 0x11d8);
  *(uint *)(param_1 + 0x4e0) = *(uint *)(param_1 + 0x4e0) & 0xfffffbff;
  if (iVar1 != 0) {
    sys_ad_free_mem(iVar1);
  }
  sys_ad_move_mem((void *)(param_2 + 0xe),&local_18,4);
  local_14 = local_14 << 0x18 | (local_14 >> 8 & 0xff) << 0x10 | (local_14 >> 0x10 & 0xff) << 8 |
             local_14 >> 0x18;
  sys_ad_move_mem((void *)(param_2 + 0x12),&local_14,4);
  FUN_00246b90(param_2,10,0);
  printk("%s: HQA iBF phase cal ID = %d and status = %d\n","hqa_get_ibf_status_ext",local_18,
         local_14);
  return 0;
}

