// module: mt7915.ko
// function: hqa_get_dump_recal @ 0x249af8
// size: 344 bytes
//

/* WARNING: Type propagation algorithm not settling */

int hqa_get_dump_recal(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  void *__dest;
  int local_38 [4];
  uint *local_28;
  uint local_24;
  
  local_38[0] = param_2 + 0xc;
  local_38[1] = 0;
  local_38[2] = 0;
  local_38[3] = 0;
  local_28 = (uint *)0x0;
  local_24 = 0;
  FUN_002474f4(1,4,local_38,local_38 + 1);
  *(char *)(param_1 + 0x4cc) = (char)local_38[1];
  mt_serv_get_recal_cnt(param_1,local_38 + 2,local_38 + 3);
  iVar3 = local_38[2] * local_38[3];
  iVar1 = sys_ad_alloc_mem(&local_28,iVar3 * 4);
  if (iVar1 == 0) {
    iVar1 = mt_serv_get_recal_content(param_1,local_28);
    local_24 = local_38[2] << 0x18 | ((uint)local_38[2] >> 8 & 0xff) << 0x10 |
               ((uint)local_38[2] >> 0x10 & 0xff) << 8 | (uint)local_38[2] >> 0x18;
    sys_ad_move_mem((void *)(param_2 + 0xe),&local_24,4);
    if (iVar3 == 0) {
      iVar3 = 6;
    }
    else {
      __dest = (void *)(param_2 + 0x12);
      iVar4 = 0;
      do {
        uVar2 = *local_28;
        local_24 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                   uVar2 >> 0x18;
        sys_ad_move_mem(__dest,&local_24,4);
        iVar4 = iVar4 + 1;
        __dest = (void *)((int)__dest + 4);
        local_28 = local_28 + 1;
      } while (iVar4 != iVar3);
      iVar3 = iVar3 * 4 + 6;
    }
    sys_ad_free_mem();
    FUN_00246b90(param_2,iVar3,iVar1);
  }
  else {
    printk("%s: dynamic memory allocate fail!!\n","hqa_get_dump_recal");
    if (local_28 != (uint *)0x0) {
      sys_ad_free_mem();
    }
    FUN_00246b90(param_2,6,iVar1);
  }
  return iVar1;
}

