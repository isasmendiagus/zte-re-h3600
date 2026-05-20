// module: mt7915.ko
// function: sta_mlme_dataq_tx @ 0x54ea8
// size: 1936 bytes
//

undefined4 sta_mlme_dataq_tx(int param_1,int param_2,int param_3)

{
  ushort uVar1;
  byte bVar2;
  undefined2 uVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  byte bVar8;
  undefined4 uVar9;
  uint uVar10;
  char cVar11;
  ushort *puVar12;
  undefined4 uVar13;
  int iVar14;
  uint uVar15;
  int iVar16;
  byte bVar17;
  int iVar18;
  byte bVar19;
  uint local_78;
  uint local_74;
  uint local_64;
  ushort local_60;
  undefined2 local_5e;
  undefined2 local_5c;
  undefined1 local_5a;
  undefined1 local_59;
  undefined1 local_58;
  undefined1 local_57;
  byte local_56;
  undefined1 local_55;
  undefined1 local_54;
  undefined1 local_51;
  undefined1 local_50;
  byte local_4f;
  byte local_4c;
  undefined1 local_4b;
  int local_48;
  undefined1 local_44;
  undefined1 local_40;
  undefined1 auStack_3f [2];
  undefined1 local_3d;
  undefined1 local_3c;
  byte local_3b;
  byte local_3a;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  
  pbVar4 = (byte *)hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar15 = (uint)pbVar4[2];
  sta_fill_offload_tx_blk(param_1,param_2,param_3);
  iVar16 = *(int *)(param_3 + 0x24);
  iVar14 = iVar16 + uVar15;
  iVar5 = MacTableLookup2(param_1,iVar14 + 4,param_2);
  iVar6 = GetStaCfgByWdev(param_1,param_2);
  if (iVar6 == 0) {
    printk(&_LC1,0x84c);
    dump_stack();
  }
  iVar18 = *(int *)(param_2 + 0x3fe4);
  local_60 = *(ushort *)(param_2 + 0xb0a);
  if (iVar18 == 0) {
    return 0;
  }
  bVar8 = *(byte *)(iVar14 + 4);
  uVar9 = *(undefined4 *)(param_3 + 0x24);
  local_64 = bVar8 & 1;
  uVar13 = *(undefined4 *)(param_3 + 0x28);
  if ((bVar8 & 1) == 0) {
    bVar17 = *(byte *)(param_1 + 0x794cd5);
  }
  else {
    bVar17 = *(byte *)(param_1 + 0x794cd6);
  }
  if (0xe < *(byte *)(param_2 + 0x1a) && bVar17 < 4) {
    bVar17 = 4;
    local_60 = local_60 & 0x1fc0 | 0x2000;
  }
  bVar19 = *(byte *)(iVar16 + uVar15) & 0xc;
  if (bVar19 == 8) {
LAB_00054fd4:
    if ((bVar8 & 1) == 0) {
      uVar3 = RTMPCalcDuration(param_1,bVar17,0xe);
      *(undefined2 *)(iVar14 + 2) = uVar3;
      if ((*(byte *)(iVar16 + uVar15) & 0xf0) == 0x50) {
        uVar10 = 1;
        local_74 = local_64;
      }
      else {
        local_74 = 1;
        uVar10 = local_64;
      }
    }
    else {
      *(undefined1 *)(iVar14 + 2) = 0;
      *(undefined1 *)(iVar14 + 3) = 0;
      local_74 = 0;
      local_64 = 0;
      uVar10 = 0;
    }
  }
  else {
    bVar2 = *(byte *)(iVar16 + uVar15) & 0xf0;
    if (((bVar2 == 0x40) || (*(char *)(iVar6 + 0x8d8) == '\0')) ||
       (*(char *)(param_1 + 0x795089) == '\0')) {
      *(byte *)(iVar14 + 1) = *(byte *)(iVar14 + 1) & 0xef;
    }
    else {
      *(byte *)(iVar14 + 1) =
           *(byte *)(iVar14 + 1) & 0xef | (*(byte *)(param_1 + 0x794cc6) & 1) << 4;
    }
    if (bVar19 != 4) goto LAB_00054fd4;
    if (bVar2 == 0x80) {
      local_74 = 1;
      local_64 = *(int *)(param_3 + 0x24) + uVar15;
      uVar10 = 0;
    }
    else if (bVar2 == 0x50) {
      local_78 = 0;
      uVar3 = RTMPCalcDuration(param_1,bVar17,(*(int *)(param_3 + 0x28) + -4) - (uint)*pbVar4);
      *(undefined2 *)(iVar14 + 2) = uVar3;
      local_74 = 0;
      local_64 = 0;
      uVar10 = local_78;
    }
    else {
      local_64 = 0;
      uVar10 = local_64;
      local_74 = local_64;
    }
  }
  puVar12 = (ushort *)(param_1 + 0xa39f90);
  uVar1 = *puVar12;
  *puVar12 = uVar1 + 1;
  *(char *)(iVar14 + 0x17) = (char)(((uint)uVar1 << 0x14) >> 0x18);
  *(byte *)(iVar14 + 0x16) = *(byte *)(iVar14 + 0x16) & 0xf | (byte)((uVar1 & 0xf) << 4);
  if (0xfff < *puVar12) {
    *puVar12 = 0;
  }
  if ((((*(byte *)(iVar16 + uVar15) & 0xf0) != 0x40) && (*(char *)(param_1 + 0x795074) == '\x01'))
     && (*(char *)(iVar18 + 4) != '\0')) {
    if (-1 < DebugLevel) {
      printk("MlmeHardTransmit --> radar detect not in normal mode !!!\n");
    }
LAB_000553c8:
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc));
    return 1;
  }
  if (iVar5 == 0) {
    bVar8 = *(byte *)(iVar16 + uVar15) & 0xfc;
    if (bVar8 == 0x84 || bVar8 == 0xd0) goto LAB_000553c8;
    if (param_2 == 0) {
      local_78 = 0xffff;
    }
    else {
      local_78 = (uint)*(ushort *)(param_2 + 0x9a0);
      uVar7 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      if (uVar7 <= local_78) {
        iVar6 = *(int *)(param_2 + 0x14);
        if (iVar6 == 4 || (iVar6 == 1 || iVar6 == 0x20)) goto LAB_000553c8;
        if (iVar6 == 2 || iVar6 == 0x40) {
          local_78 = 0;
        }
      }
    }
  }
  else {
    local_78 = (uint)*(ushort *)(iVar5 + 0xe0);
  }
  bVar17 = (byte)local_60;
  __memzero(&local_5c);
  bVar17 = bVar17 & 0x3f;
  local_55 = 0;
  local_54 = 0;
  local_59 = (undefined1)uVar10;
  local_5a = 0;
  local_5c = (undefined2)local_78;
  local_56 = *(byte *)(iVar14 + 4) & 1;
  local_58 = 0;
  local_51 = 0;
  local_57 = (undefined1)local_74;
  local_4f = 0;
  local_32 = HcGetWmmIdx(param_1,param_2);
  local_40 = HcGetMgmtQueueIdx(param_1,param_2,(int)*(char *)(*(int *)(param_3 + 0xc) + 0x4f));
  local_33 = *(undefined1 *)(param_2 + 0x29);
  local_48 = *(int *)(param_3 + 0x28) - uVar15;
  local_2c = 0;
  local_3b = (byte)(((uint)*(byte *)(iVar16 + uVar15) << 0x1c) >> 0x1e);
  local_3a = *(byte *)(iVar16 + uVar15) >> 4;
  bVar8 = *(byte *)(iVar16 + uVar15);
  uVar10 = (uint)bVar8;
  if ((bVar8 & 0xc) == 0) {
    local_44 = 0x18;
    local_50 = 3;
    if ((*(byte *)(iVar14 + 1) & 0x80) != 0) {
      local_44 = 0x1c;
    }
    PMF_PerformTxFrameAction(param_1,iVar14,*(int *)(param_3 + 0x28),uVar15,auStack_3f);
    uVar10 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
    if (((((uVar10 & 0x4000000) != 0) && ((*(byte *)(iVar16 + uVar15) & 0xf0) == 0xd0)) &&
        (iVar5 = *(int *)(param_3 + 0x24) + uVar15, *(char *)(iVar5 + 0x18) == '\x03')) &&
       (*(char *)(iVar5 + 0x19) == '\0')) {
      uVar10 = (uint)*(byte *)(iVar5 + 0x1b) << 0x1a;
      local_4f = (byte)(uVar10 >> 0x1c);
      local_2d = 1;
      local_40 = *(undefined1 *)((int)&WMM_UP2AC_MAP + (uVar10 >> 0x1c));
    }
    local_2c = *(undefined1 *)(param_2 + 0x93c);
    puVar12 = &local_60;
  }
  else if ((uVar10 & 0xc) == 8) {
    if (bVar8 >> 4 == 4) {
      local_44 = 0x18;
      bVar17 = (byte)local_60 & 0x3f;
    }
    else if (bVar8 >> 4 == 0xc) {
      local_44 = 0x1a;
      bVar17 = (byte)local_60 & 0x3f;
    }
    else {
      if (-1 < DebugLevel) {
        printk("%s(): FIXME!!!Unexpected frame(Type=%d, SubType=%d) send to MgmtRing, need to assign the length!\n"
               ,"sta_mlme_dataq_tx",(uVar10 << 0x1c) >> 0x1e);
      }
      hex_dump("DataFrame",uVar9,uVar13);
    }
    local_5c = (undefined2)local_78;
    if ((iVar5 == 0) || (*(char *)(param_1 + local_78 * 0x620 + 0x2fa7c) == '\0')) {
      puVar12 = &local_60;
      local_50 = 3;
    }
    else {
      puVar12 = &local_60;
      local_50 = 6;
    }
  }
  else if ((uVar10 & 0xc) == 4) {
    if (bVar8 >> 4 == 8) {
      cVar11 = '\x05';
      local_44 = 0x10;
      local_50 = 5;
      if (0xe < *(byte *)(param_2 + 0x1a)) {
        cVar11 = '\x01';
      }
      local_4f = *(byte *)(local_64 + 0x11) >> 4;
      if (*(byte *)(param_2 + 0x1a) < 0xf) {
        local_5e._1_1_ = local_5e._1_1_ & 0x1f;
      }
      else {
        local_5e._1_1_ = local_5e._1_1_ & 0x1f | cVar11 << 5;
      }
      puVar12 = &local_5e;
      local_5e = ((local_5e._1_1_ & 0xfe) & 0xf9) << 8;
    }
    else {
      if (-1 < DebugLevel) {
        printk("%s(): FIXME!!!Unexpected frame(Type=%d, SubType=%d) send to MgmtRing, need to assign the length!\n"
               ,"sta_mlme_dataq_tx",(uVar10 << 0x1c) >> 0x1e);
      }
      hex_dump("Control Frame",uVar9,uVar13);
      puVar12 = &local_60;
    }
  }
  else {
    puVar12 = &local_60;
  }
  local_4b = 3;
  local_3d = 1;
  local_3c = 1;
  local_2b = 0;
  local_4c = bVar17;
  if ((((param_2 != 0) &&
       (((*(ushort *)(param_2 + 0x18) & 0x4e) == 0 || (0xe < *(byte *)(param_2 + 0x1a))))) &&
      ((*(byte *)((int)puVar12 + 1) & 0xe0) == 0)) &&
     (*(byte *)((int)puVar12 + 1) = *(byte *)((int)puVar12 + 1) & 0x1f | 0x20, -1 < DebugLevel)) {
    printk("@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
           ,"sta_mlme_dataq_tx",((uint)*(byte *)(iVar16 + uVar15) << 0x1c) >> 0x1e,
           *(byte *)(iVar16 + uVar15) >> 4,local_48,local_32,local_40,local_33);
  }
  uVar9 = asic_mlme_hw_tx(param_1,uVar9,&local_5c,puVar12,param_3);
  return uVar9;
}

