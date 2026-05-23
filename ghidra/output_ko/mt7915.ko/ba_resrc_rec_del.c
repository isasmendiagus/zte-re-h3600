// module: mt7915.ko
// function: ba_resrc_rec_del @ 0xa69ac
// size: 548 bytes
//

undefined4 ba_resrc_rec_del(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  uVar3 = (uint)*(ushort *)(param_1 + (param_2 * 0xa60 + param_3 + 0x514f8) * 2 + 4);
  if (0x47e < uVar3 - 1) {
    return 0;
  }
  iVar4 = param_1 + 0x1c0;
  iVar1 = uVar3 * 0x60;
  iVar5 = iVar4 + iVar1 + 0x10;
  HW_SET_BA_REC(param_1,param_2,param_3,0,0,0,2,0);
  _raw_spin_lock_bh(iVar5);
  if (*(int *)(param_1 + iVar1 + 0x1c8) != 0) {
    uVar6 = (uint)*(byte *)(param_1 + iVar1 + 0x1fe);
    uVar2 = (uint)*(ushort *)(iVar4 + iVar1 + 0x3c);
    iVar1 = uVar2 * 0x14c0 + param_1;
    *(undefined2 *)(param_1 + (uVar2 * 0xa60 + uVar6 + 0x514f8) * 2 + 4) = 0;
    *(ushort *)(iVar1 + 0xa29de) = *(ushort *)(iVar1 + 0xa29de) & ~(ushort)(1 << uVar6);
    if (*(int *)(param_1 + 0x2f680) == 0) {
      printk(&_LC50,0x5a4);
      dump_stack();
    }
    iVar1 = param_1 + uVar3 * 0x60;
    *(undefined4 *)(iVar1 + 0x1c8) = 0;
    *(undefined4 *)(iVar1 + 0x1dc) = 0;
    *(undefined4 *)(iVar1 + 0x1e0) = 0;
    *(undefined4 *)(iVar1 + 0x1e4) = 0;
    *(undefined4 *)(iVar1 + 0x1e8) = 0;
    _raw_spin_lock_bh(param_1 + 0x2f5c0);
    if (*(int *)(param_1 + 0x2f680) == 0) {
      if (0 < DebugLevel) {
        iVar1 = param_1 + uVar3 * 0x60;
        printk("Idx = %lu, REC_BA_Status = %d, Wcid(pBAEntry) = %d,\t\t\t\tWcid(pEntry) = %d, Tid = %d\n"
               ,uVar3,*(undefined4 *)(iVar1 + 0x1c8),*(undefined2 *)(iVar4 + uVar3 * 0x60 + 0x3c),
               *(undefined2 *)(uVar2 * 0x14c0 + param_1 + 0xa1e00),*(undefined1 *)(iVar1 + 0x1fe));
      }
    }
    else {
      *(int *)(param_1 + 0x2f680) = *(int *)(param_1 + 0x2f680) + -1;
    }
    _raw_spin_unlock_bh(param_1 + 0x2f5c0);
    if ((*(uint *)(param_1 + 0x2f68c) & 1) != 0) {
      iVar1 = param_1 + uVar3 * 0x60;
      if (*(int *)(iVar1 + 0x208) != 0) {
        os_free_mem();
        *(undefined4 *)(iVar1 + 0x208) = 0;
      }
      *(undefined4 *)(param_1 + uVar3 * 0x60 + 0x20c) = 0;
    }
  }
  _raw_spin_unlock_bh(iVar5);
  FUN_000a4598(param_1,iVar4,iVar4 + uVar3 * 0x60);
  return 1;
}

