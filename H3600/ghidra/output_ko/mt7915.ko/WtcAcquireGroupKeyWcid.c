// module: mt7915.ko
// function: WtcAcquireGroupKeyWcid @ 0xada48
// size: 336 bytes
//

uint WtcAcquireGroupKeyWcid(int param_1,int param_2)

{
  int iVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  char cVar4;
  ushort uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  
  uVar5 = *(ushort *)(param_1 + 0x1a2a);
  iVar9 = param_1 + 0x1000;
  iVar10 = param_1 + 0x2c30;
  iVar6 = hc_get_chip_wtbl_max_num(*(undefined4 *)(*(int *)(param_1 + 0x4328) + 0xa797a0));
  uVar2 = *(undefined1 *)(param_2 + 4);
  uVar3 = *(undefined1 *)(param_2 + 2);
  uVar8 = iVar6 - 1U & 0xffff;
  _raw_spin_lock_bh(iVar10);
  iVar6 = DebugLevel;
  if (uVar8 < uVar5) {
LAB_000adb34:
    _raw_spin_unlock_bh(iVar10);
    if (DebugLevel < 0) {
      uVar8 = 0xffff;
    }
    else {
      printk("%s: no available wtbl_idx for WDEV_TYPE:%d\n","wtc_acquire_groupkey_wcid",uVar3);
      uVar8 = 0xffff;
    }
  }
  else {
    iVar1 = uVar8 * 0x10;
    cVar4 = *(char *)(iVar9 + iVar1 + 0xa30);
    while (cVar4 != '\0') {
      uVar8 = uVar8 - 1 & 0xffff;
      iVar1 = uVar8 * 0x10;
      if (uVar8 < uVar5) goto LAB_000adb34;
      cVar4 = *(char *)(iVar9 + iVar1 + 0xa30);
    }
    iVar7 = iVar9 + iVar1;
    *(undefined1 *)(iVar7 + 0xa30) = 1;
    *(short *)(iVar9 + iVar1 + 0xa34) = (short)uVar8;
    *(undefined1 *)(iVar7 + 0xa31) = uVar2;
    *(undefined1 *)(iVar7 + 0xa32) = uVar3;
    *(undefined1 *)(iVar7 + 0xa36) = 2;
    if (2 < iVar6) {
      printk("%s: Found a non-occupied wtbl_idx:%d for WDEV_TYPE:%d\n LinkToOmacIdx = %x, LinkToWdevType = %d\n"
             ,"wtc_acquire_groupkey_wcid",uVar8,uVar3,uVar2,uVar3);
    }
    _raw_spin_unlock_bh(iVar10);
  }
  return uVar8;
}

