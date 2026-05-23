// module: mt7915.ko
// function: hqa_get_dump_rxv_legacy @ 0x2499a0
// size: 340 bytes
//

/* WARNING: Type propagation algorithm not settling */

int hqa_get_dump_rxv_legacy(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int local_30 [4];
  uint *local_20;
  uint local_1c;
  
  local_30[0] = param_2 + 0xc;
  local_30[1] = 0;
  local_30[2] = 0;
  local_30[3] = 0;
  local_20 = (uint *)0x0;
  local_1c = 0;
  FUN_002474f4(1,4,local_30,local_30 + 1);
  *(char *)(param_1 + 0x4cc) = (char)local_30[1];
  mt_serv_get_rxv_cnt(param_1,local_30 + 2,local_30 + 3);
  uVar4 = local_30[2] * local_30[3];
  iVar1 = sys_ad_alloc_mem(&local_20,uVar4 * 4);
  if (iVar1 == 0) {
    iVar1 = mt_serv_get_rxv_content(param_1,uVar4,local_20);
    iVar3 = 6;
    local_1c = local_30[2] << 0x18 | ((uint)local_30[2] >> 8 & 0xff) << 0x10 |
               ((uint)local_30[2] >> 0x10 & 0xff) << 8 | (uint)local_30[2] >> 0x18;
    sys_ad_move_mem((void *)(param_2 + 0xe),&local_1c,4);
    if (uVar4 != 0) {
      do {
        uVar2 = *local_20;
        local_1c = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                   uVar2 >> 0x18;
        sys_ad_move_mem((void *)(param_2 + iVar3 + 0xc),&local_1c,4);
        uVar2 = iVar3 - 2;
        iVar3 = iVar3 + 4;
        local_20 = local_20 + 1;
      } while (uVar2 <= uVar4 && uVar4 - uVar2 != 0);
    }
    sys_ad_free_mem();
    FUN_00246b90(param_2,iVar3,iVar1);
  }
  else {
    printk("%s: dynamic memory allocate fail!!\n","hqa_get_dump_rxv_legacy");
    if (local_20 != (uint *)0x0) {
      sys_ad_free_mem();
    }
    FUN_00246b90(param_2,2,iVar1);
  }
  return iVar1;
}

