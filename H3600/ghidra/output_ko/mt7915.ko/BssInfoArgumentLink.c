// module: mt7915.ko
// function: BssInfoArgumentLink @ 0x14d65c
// size: 1260 bytes
//

void BssInfoArgumentLink(int param_1,int param_2,undefined4 *param_3)

{
  uint uVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  byte bVar8;
  undefined4 uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  undefined2 local_2a;
  
  iVar4 = GetStaCfgByWdev();
  iVar11 = *(int *)(param_2 + 4);
  uVar10 = 0;
  *(undefined1 *)(param_3 + 3) = *(undefined1 *)(param_2 + 0x29);
  iVar12 = param_1 + 0x286290;
  *(undefined1 *)((int)param_3 + 0x106) = *(undefined1 *)(param_2 + 0xaa7);
  iVar5 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar8 = *(byte *)(iVar5 + 0x14a);
  _raw_spin_lock_bh(iVar12);
  do {
    uVar13 = 1 << (uVar10 & 0xff);
    if ((uVar13 & *(uint *)(param_1 + 0x286288)) == 0) {
      *(uint *)(param_1 + 0x286288) = uVar13 | *(uint *)(param_1 + 0x286288);
      if (2 < DebugLevel) {
        printk("%s: found non-used BssInfoIdx: %d\n","GetBssIdx",uVar10);
      }
      uVar2 = (undefined1)uVar10;
      _raw_spin_unlock_bh(iVar12);
      goto LAB_0014d70c;
    }
    uVar10 = uVar10 + 1;
  } while (uVar10 != 0x20);
  uVar13 = *(uint *)(param_1 + 0x28628c);
  uVar10 = bVar8 + 0x23 & 0xff;
  if (uVar10 < 0x21) {
LAB_0014d8a8:
    _raw_spin_unlock_bh(iVar12);
    if (DebugLevel < 0) {
      uVar2 = 0xff;
    }
    else {
      uVar2 = 0xff;
      printk("%s: could not find usable BssInfoIdx\n","GetBssIdx");
    }
  }
  else {
    if ((uVar13 & 1) == 0) {
      uVar6 = 1;
      uVar7 = 0x20;
      uVar2 = 0x20;
    }
    else {
      uVar1 = 0x21;
      do {
        uVar7 = uVar1;
        uVar6 = 1 << (uVar7 - 0x20 & 0xff);
        if (uVar10 <= (uVar7 & 0xff)) goto LAB_0014d8a8;
        uVar1 = uVar7 + 1;
      } while ((uVar6 & uVar13) != 0);
      uVar2 = (undefined1)uVar7;
    }
    *(uint *)(param_1 + 0x28628c) = uVar6 | uVar13;
    if (2 < DebugLevel) {
      printk("%s: found non-used BssInfoIdx: %d\n","GetBssIdx",uVar7);
    }
    _raw_spin_unlock_bh(iVar12);
  }
LAB_0014d70c:
  *(undefined1 *)((int)param_3 + 0xd) = uVar2;
  os_move_mem((void *)((int)param_3 + 0xe),(void *)(param_2 + 0x21),6);
  uVar2 = SecHWCipherSuitMapping(*(undefined4 *)(param_2 + 0x174));
  *(undefined1 *)(param_3 + 8) = uVar2;
  *(char *)((int)param_3 + 0x22) = (char)*(undefined2 *)(param_2 + 0x18);
  hc_radio_query_by_wdev(param_2,(int)param_3 + 0x5b);
  uVar10 = *(uint *)(param_2 + 0x14);
  if (uVar10 == 8) {
    *param_3 = 2;
    param_3[7] = 0x200010;
    param_3[6] = 0x200000;
    goto LAB_0014d7b8;
  }
  if (uVar10 < 9) {
    if (uVar10 == 2) {
      *param_3 = 0;
      param_3[7] = 0x10001;
      param_3[6] = 0x10000;
      uVar9 = HcAcquireGroupKeyWcid(param_1,param_2);
      *(short *)(param_3 + 5) = (short)uVar9;
      TRTableInsertMcastEntry(param_1,uVar9,param_2);
      *(undefined1 *)((int)param_3 + 0x46) = 1;
      *(undefined1 *)((int)param_3 + 0x47) = 0x1e;
      if (iVar4 != 0) {
        *(undefined2 *)(param_3 + 0x16) = *(undefined2 *)(iVar4 + 0x416e);
        *(undefined1 *)((int)param_3 + 0x5a) = *(undefined1 *)(iVar4 + 0x4168);
        *(undefined1 *)(param_3 + 0x1a) = *(undefined1 *)(iVar4 + 0x213177);
        *(undefined1 *)(param_3 + 0x41) = *(undefined1 *)(iVar4 + 0x2123f0);
        *(undefined1 *)((int)param_3 + 0x105) = *(undefined1 *)(iVar4 + 0x2123f1);
      }
      uapsd_config_get(param_2,(int)param_3 + 0x66);
      goto LAB_0014d7b8;
    }
    if (uVar10 != 4) {
LAB_0014d8cc:
      *param_3 = 0;
      uVar9 = HcAcquireGroupKeyWcid(param_1,param_2);
      *(short *)(param_3 + 5) = (short)uVar9;
      TRTableInsertMcastEntry(param_1,uVar9,param_2);
      MgmtTableSetMcastEntry(param_1,*(undefined2 *)(param_3 + 5));
      param_3[6] = 0x10000;
      param_3[7] = 0x10002;
      *(undefined2 *)(param_3 + 0x16) = *(undefined2 *)(&DAT_00794c50 + param_1);
      if (iVar11 != 0) {
        iVar4 = HcGetBandByWdev(iVar11);
        uVar10 = *(uint *)(param_1 + (iVar4 + 0xd9e3a) * 4);
        if ((uVar10 != 0) &&
           ((*(uint *)(iVar11 + 0x4060) == (uint)(byte)(&DAT_003678f2)[param_1 + iVar4] ||
            ((uVar10 & 1 << (*(uint *)(iVar11 + 0x4064) & 0xff)) != 0)))) {
          *(undefined *)(param_3 + 0x41) = (&DAT_003678f0)[param_1 + iVar4];
          *(char *)((int)param_3 + 0x105) = (char)*(undefined4 *)(iVar11 + 0x4064);
        }
        *(undefined1 *)((int)param_3 + 0x5a) = *(undefined1 *)(iVar11 + 0x408b);
      }
      goto LAB_0014d7b8;
    }
    *param_3 = 0;
    param_3[7] = 0x40004;
    uVar9 = 0x40000;
  }
  else {
    if (uVar10 == 0x20) {
      *param_3 = 0;
      param_3[7] = 0x20002;
      param_3[6] = 0x10000;
      uVar9 = HcAcquireGroupKeyWcid(param_1,param_2);
      *(short *)(param_3 + 5) = (short)uVar9;
      TRTableInsertMcastEntry(param_1,uVar9,param_2);
      if (*(ushort *)(param_3 + 5) < 0x120) {
        MgmtTableSetMcastEntry(param_1);
      }
      goto LAB_0014d7b8;
    }
    if (uVar10 != 0x40) goto LAB_0014d8cc;
    param_3[7] = 0x20001;
    uVar9 = 0x20000;
    *param_3 = 0;
  }
  param_3[6] = uVar9;
  uVar3 = HcAcquireGroupKeyWcid(param_1,param_2);
  *(undefined2 *)(param_3 + 5) = uVar3;
LAB_0014d7b8:
  wdev_edca_acquire(param_1,param_2);
  uVar2 = HcGetWmmIdx(param_1,param_2);
  *(undefined1 *)((int)param_3 + 0x21) = uVar2;
  os_zero_mem(&local_2a,2);
  if (((*(ushort *)(param_2 + 0x18) & 2) == 0) || (0xe < *(byte *)(param_2 + 0x1a))) {
    bVar8 = local_2a._1_1_ & 0x1f | 0x20;
  }
  else {
    bVar8 = local_2a._1_1_ & 0x1f;
  }
  local_2a = CONCAT11(bVar8,(undefined1)local_2a);
  local_2a = local_2a & 0xfe40;
  uVar3 = *(undefined2 *)(param_2 + 0xb0c);
  *(ushort *)(param_3 + 0x15) = local_2a;
  *(undefined2 *)((int)param_3 + 0x56) = uVar3;
  raWrapperConfigSet(param_1,param_2,param_3 + 0x1b);
  fill_bssinfo_he(param_2,param_3);
  param_3[1] = 1;
  return;
}

