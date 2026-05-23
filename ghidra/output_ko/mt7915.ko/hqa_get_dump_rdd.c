// module: mt7915.ko
// function: hqa_get_dump_rdd @ 0x2497ec
// size: 432 bytes
//

int hqa_get_dump_rdd(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int local_34;
  undefined4 local_30;
  undefined4 local_2c;
  int local_28;
  uint *local_24;
  uint local_20;
  uint local_1c;
  
  local_34 = param_2 + 0xc;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = (uint *)0x0;
  local_20 = 0;
  local_1c = 0;
  FUN_002474f4(1,4,&local_34,&local_30);
  *(char *)(param_1 + 0x4cc) = (char)local_30;
  mt_serv_get_rdd_cnt(param_1,&local_2c,&local_28);
  printk("%s: band_idx: %d, pulse number: %d, rdd buffer size: %d\n","hqa_get_dump_rdd",local_30,
         local_2c,local_28);
  iVar1 = sys_ad_alloc_mem(&local_24,local_28 << 2);
  if (iVar1 == 0) {
    iVar1 = mt_serv_get_rdd_content(param_1,local_24,&local_1c);
    if (local_1c == 0) {
      iVar3 = 6;
      printk("%s: total_cnt %d\n","hqa_get_dump_rdd");
      sys_ad_move_mem((void *)(param_2 + 0xe),&local_1c,4);
    }
    else {
      local_20 = (local_1c >> 1) << 0x18 | (local_1c >> 9 & 0xff) << 0x10 |
                 (local_1c >> 0x11 & 0xff) << 8 | local_1c >> 0x19;
      iVar3 = 6;
      sys_ad_move_mem((void *)(param_2 + 0xe),&local_20,4);
      uVar4 = 0;
      if (local_1c != 0) {
        do {
          uVar2 = *local_24;
          local_20 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                     uVar2 >> 0x18;
          sys_ad_move_mem((void *)(param_2 + iVar3 + 0xc),&local_20,4);
          uVar4 = uVar4 + 1;
          iVar3 = iVar3 + 4;
          local_24 = local_24 + 1;
        } while (uVar4 < local_1c);
      }
    }
    sys_ad_free_mem(local_24);
    FUN_00246b90(param_2,iVar3,iVar1);
  }
  else {
    printk("%s: dynamic memory allocate fail!!\n","hqa_get_dump_rdd");
    if (local_24 != (uint *)0x0) {
      sys_ad_free_mem();
    }
    FUN_00246b90(param_2,2,iVar1);
  }
  return iVar1;
}

