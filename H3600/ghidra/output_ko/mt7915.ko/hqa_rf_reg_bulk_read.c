// module: mt7915.ko
// function: hqa_rf_reg_bulk_read @ 0x24b1b8
// size: 292 bytes
//

undefined4 hqa_rf_reg_bulk_read(int param_1,int param_2)

{
  size_t __n;
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int local_24 [2];
  
  local_24[0] = param_2 + 0xc;
  FUN_002474f4(1,4,local_24,param_1 + 0x1f20);
  FUN_002474f4(1,4,local_24,param_1 + 0x1f14);
  FUN_002474f4(1,4,local_24,param_1 + 0x1f18);
  __n = (uint)*(ushort *)(param_1 + 0x1f18) * 4;
  iVar1 = sys_ad_alloc_mem(param_1 + 0x1f1c,__n);
  if (iVar1 == 0) {
    uVar2 = mt_serv_reg_eprm_operation(param_1,3);
    if (*(short *)(param_1 + 0x1f18) != 0) {
      uVar3 = 0;
      do {
        uVar4 = *(uint *)(*(int *)(param_1 + 0x1f1c) + uVar3 * 4);
        *(uint *)(*(int *)(param_1 + 0x1f1c) + uVar3 * 4) =
             uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
             uVar4 >> 0x18;
        uVar3 = uVar3 + 1 & 0xffff;
      } while (uVar3 < *(ushort *)(param_1 + 0x1f18));
    }
    sys_ad_move_mem((void *)(param_2 + 0xe),*(void **)(param_1 + 0x1f1c),__n);
    FUN_00246b90(param_2,__n + 2,uVar2);
    sys_ad_free_mem(*(undefined4 *)(param_1 + 0x1f1c));
  }
  else {
    printk("%s: allocate register memory fail\n","hqa_rf_reg_bulk_read");
    FUN_00246b90(param_2,2,0x101);
    uVar2 = 0x101;
  }
  return uVar2;
}

