// module: mt7915.ko
// function: hqa_rf_reg_bulk_write @ 0x24b09c
// size: 280 bytes
//

undefined4 hqa_rf_reg_bulk_write(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int local_24 [2];
  
  local_24[0] = param_2 + 0xc;
  FUN_002474f4(1,4,local_24,param_1 + 0x1f20);
  FUN_002474f4(1,4,local_24,param_1 + 0x1f14);
  FUN_002474f4(1,4,local_24,param_1 + 0x1f18);
  iVar1 = sys_ad_alloc_mem(param_1 + 0x1f1c,(uint)*(ushort *)(param_1 + 0x1f18) << 2);
  if (iVar1 == 0) {
    if (*(short *)(param_1 + 0x1f18) != 0) {
      uVar3 = 0;
      do {
        iVar1 = uVar3 * 4;
        uVar3 = uVar3 + 1;
        FUN_002474f4(1,4,local_24,*(int *)(param_1 + 0x1f1c) + iVar1);
      } while (uVar3 < *(ushort *)(param_1 + 0x1f18));
    }
    uVar2 = mt_serv_reg_eprm_operation(param_1,4);
    FUN_00246b90(param_2,2,uVar2);
    sys_ad_free_mem(*(undefined4 *)(param_1 + 0x1f1c));
  }
  else {
    printk("%s: allocate register memory fail\n","hqa_rf_reg_bulk_write");
    FUN_00246b90(param_2,2,0x101);
    uVar2 = 0x101;
  }
  return uVar2;
}

