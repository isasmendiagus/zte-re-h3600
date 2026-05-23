// module: mt7915.ko
// function: mt7915_hif_chip_match @ 0x17a69c
// size: 232 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void mt7915_hif_chip_match(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar1 = hc_get_hif_ctrl();
  iVar4 = *(int *)(iVar1 + 0xa0);
  uVar2 = hc_get_asic_cap(param_1);
  uVar3 = multi_hif_entry_id_get(iVar4);
  multi_hif_entry_gid_set(iVar4,uVar3);
  if ((uVar2 & 0x400000) == 0) {
    return;
  }
  uVar2 = multi_hif_entry_rid_get(iVar4);
  if (uVar2 != 0) {
    iVar4 = multi_hif_entry_get_by_id(uVar2 - 1);
    if (iVar4 == 0) {
      return;
    }
    DataSynchronizationBarrier(0xe);
    if (___aeabi_idivmod != (code *)0x0) {
      (*___aeabi_idivmod)();
    }
    *(uint *)(*(int *)(iVar4 + 0xbc) + 0xd7090) = uVar2 | 0x80000000;
    *(int *)(iVar1 + 0xa4) = iVar4;
    return;
  }
  DataSynchronizationBarrier(0xf);
  uVar2 = *(uint *)(*(int *)(iVar4 + 0xbc) + 0xd7090) & 0x7fffffff;
  multi_hif_entry_rid_set(iVar4,uVar2);
  if (uVar2 == 0) {
    return;
  }
  iVar4 = multi_hif_entry_get_by_id(uVar2 - 1);
  if (iVar4 == 0) {
    return;
  }
  multi_hif_entry_gid_set(iVar4,uVar3);
  multi_hif_entry_rid_set(iVar4,uVar2);
  *(int *)(iVar1 + 0xa4) = iVar4;
  return;
}

