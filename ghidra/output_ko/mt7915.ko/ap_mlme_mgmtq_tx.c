// module: mt7915.ko
// function: ap_mlme_mgmtq_tx @ 0x1aaec
// size: 2076 bytes
//

undefined4 ap_mlme_mgmtq_tx(int param_1,int param_2,int param_3)

{
  ushort uVar1;
  bool bVar2;
  undefined2 uVar3;
  int iVar4;
  undefined4 uVar5;
  byte bVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  ushort *puVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  byte bVar14;
  uint uVar15;
  bool bVar16;
  uint uVar17;
  uint local_70;
  byte local_5f;
  ushort local_5e;
  short local_5c;
  undefined1 local_5a;
  byte local_59;
  undefined1 local_58;
  byte local_57;
  byte local_56;
  undefined1 local_55;
  undefined1 local_54;
  undefined1 local_51;
  undefined1 local_50;
  undefined1 local_4f;
  byte local_4c;
  undefined1 local_4b;
  int local_48;
  undefined1 local_44;
  undefined1 local_41;
  byte local_40;
  byte local_3f;
  undefined1 local_3e;
  undefined1 local_3d;
  undefined1 local_3c;
  byte local_3b;
  byte local_3a;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  char local_31;
  undefined1 local_2c;
  undefined1 local_2b;
  
  iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  piVar9 = *(int **)(param_3 + 0x14);
  uVar12 = (uint)*(byte *)(iVar4 + 2);
  local_5f = 0;
  if ((param_2 == 0) || (iVar4 = *(int *)(param_2 + 0x3fe4), iVar4 == 0)) {
    return 1;
  }
  ap_fill_offload_tx_blk(param_1,param_2,param_3);
  iVar13 = *(int *)(param_3 + 0x24);
  iVar11 = iVar13 + uVar12;
  bVar14 = *(byte *)(iVar11 + 4);
  if ((bVar14 & 1) == 0) {
    bVar6 = *(byte *)(param_1 + 0x794cd5);
  }
  else {
    bVar6 = *(byte *)(param_1 + 0x794cd6);
  }
  local_5e = *(ushort *)(param_2 + 0xb0a);
  if (0xe < *(byte *)(param_2 + 0x1a) && bVar6 < 4) {
    bVar6 = 4;
    local_5e = local_5e & 0x1fc0 | 0x2000;
  }
  *(byte *)(iVar11 + 1) =
       *(byte *)(iVar11 + 1) & 0xdf | (*(byte *)(*(int *)(param_3 + 0xc) + 0x2f) & 1) << 5;
  if ((*(byte *)(iVar13 + uVar12) & 0xc) == 4) {
    if ((*(byte *)(iVar13 + uVar12) & 0xf0) == 0x50) {
      bVar2 = false;
      *(undefined1 *)(iVar11 + 3) = 0;
      bVar16 = false;
      *(undefined1 *)(iVar11 + 2) = 100;
    }
    else {
LAB_0001afc8:
      bVar2 = false;
      bVar16 = false;
    }
  }
  else if ((bVar14 & 1) == 0) {
    uVar3 = RTMPCalcDuration(param_1,bVar6,0xe);
    *(undefined2 *)(iVar11 + 2) = uVar3;
    bVar6 = *(byte *)(iVar13 + uVar12) & 0xfc;
    if (bVar6 == 0x50) {
      bVar2 = true;
      bVar16 = (bool)(bVar14 & 1);
    }
    else {
      if (bVar6 == 0x40) goto LAB_0001afc8;
      bVar16 = (*(byte *)(iVar13 + uVar12) & 0xf0) != 0xc0 || piVar9 != (int *)0x0;
      bVar2 = (bool)(bVar14 & 1);
    }
  }
  else {
    *(undefined1 *)(iVar11 + 2) = 0;
    *(undefined1 *)(iVar11 + 3) = 0;
    bVar16 = false;
    bVar2 = false;
  }
  puVar10 = (ushort *)(param_1 + 0xa39f90);
  uVar1 = *puVar10;
  *puVar10 = uVar1 + 1;
  *(char *)(iVar11 + 0x17) = (char)(((uint)uVar1 << 0x14) >> 0x18);
  *(byte *)(iVar11 + 0x16) = *(byte *)(iVar11 + 0x16) & 0xf | (byte)((uVar1 & 0xf) << 4);
  if (0xfff < *puVar10) {
    *puVar10 = 0;
  }
  if ((((*(byte *)(iVar13 + uVar12) & 0xf0) != 0x40) && (*(char *)(param_1 + 0x795074) == '\x01'))
     && (*(char *)(iVar4 + 4) != '\0')) {
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc));
    return 1;
  }
  PMF_PerformTxFrameAction(param_1,iVar11,*(undefined4 *)(param_3 + 0x28),uVar12,&local_5f);
  if (piVar9 == (int *)0x0) {
    local_70 = 0;
    if (0 < DebugLevel) {
      printk("pMacEntry is null !!\n");
    }
  }
  else {
    local_70 = (uint)*(ushort *)(piVar9 + 0x38);
  }
  bVar14 = (byte)local_5e;
  __memzero(&local_5c,0x34);
  bVar14 = bVar14 & 0x3f;
  if ((local_5f != 0) && (local_3f = local_5f, local_5f - 2 < 2)) {
    local_41 = 0;
  }
  local_5c = (short)local_70;
  local_55 = 0;
  local_54 = 0;
  local_5a = 0;
  local_58 = 0;
  local_56 = *(byte *)(iVar11 + 4) & 1;
  local_51 = 0;
  local_3b = (byte)(((uint)*(byte *)(iVar13 + uVar12) << 0x1c) >> 0x1e);
  local_2c = 0;
  local_34 = 1;
  local_3a = *(byte *)(iVar13 + uVar12) >> 4;
  local_59 = bVar2;
  local_57 = bVar16;
  if (*(char *)(param_1 + 0x795943) != '\x01') {
    iVar4 = HcGetBandByWdev(param_2);
    if (iVar4 == 0) {
      local_3e = 0x18;
    }
    else {
      iVar4 = HcGetBandByWdev(param_2);
      if (iVar4 == 1) {
        local_3e = 0x19;
      }
    }
  }
  local_48 = *(int *)(param_3 + 0x28) - uVar12;
  bVar6 = *(byte *)(iVar13 + uVar12);
  uVar8 = (uint)bVar6;
  if ((bVar6 & 0xc) == 0) {
    local_44 = 0x18;
    local_2c = *(undefined1 *)(param_2 + 0x93c);
    if ((*(byte *)(iVar11 + 1) & 0x80) != 0) {
      local_44 = 0x1c;
    }
    local_50 = 3;
  }
  else if ((uVar8 & 0xc) == 8) {
    if (bVar6 >> 4 == 4) {
      local_44 = 0x18;
      bVar14 = (byte)local_5e & 0x3f;
    }
    else if (bVar6 >> 4 == 0xc) {
      local_44 = 0x1a;
      bVar14 = (byte)local_5e & 0x3f;
    }
    else {
      if (-1 < DebugLevel) {
        printk("%s(): FIXME!!!Unexpected frame(Type=%d, SubType=%d) send to MgmtRing, need to assign the length!\n"
               ,"ap_mlme_mgmtq_tx",(uVar8 << 0x1c) >> 0x1e);
      }
      hex_dump("DataFrame",iVar11,0x18);
    }
    if (piVar9 == (int *)0x0) {
      local_50 = 3;
    }
    else if (*(char *)(param_1 + local_70 * 0x620 + 0x2fa7c) == '\0') {
      local_50 = 3;
    }
    else {
      local_50 = 6;
    }
    local_5c = (short)local_70;
  }
  else {
    if ((uVar8 & 0xc) == 4) {
      if (bVar6 >> 4 == 10) {
        local_50 = 3;
        local_44 = 0x10;
        bVar14 = (byte)local_5e & 0x3f;
        goto LAB_0001ad80;
      }
      if (-1 < DebugLevel) {
        printk("%s(): FIXME!!!Unexpected frame(Type=%d, SubType=%d) send to MgmtRing, need to assign the length!\n"
               ,"ap_mlme_mgmtq_tx",(uVar8 << 0x1c) >> 0x1e);
        local_50 = 3;
        goto LAB_0001ad80;
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n",
             "ap_mlme_mgmtq_tx");
      local_50 = 3;
      goto LAB_0001ad80;
    }
    local_50 = 3;
  }
LAB_0001ad80:
  local_4f = 0;
  local_2b = 0;
  local_3d = 1;
  local_3c = 1;
  local_4c = bVar14;
  local_32 = HcGetWmmIdx(param_1,param_2);
  local_40 = HcGetMgmtQueueIdx(param_1,param_2,(int)*(char *)(*(int *)(param_3 + 0xc) + 0x4f));
  local_33 = *(undefined1 *)(param_2 + 0x29);
  if (3 < DebugLevel) {
    printk("%s(): %d, WMMSET=%d,QId=%d\n","ap_mlme_mgmtq_tx",0x5d5,local_32,local_40);
  }
  if ((((*(byte *)(iVar13 + uVar12) & 0xc) == 8) &&
      (piVar9 != (int *)0x0 && (*(byte *)(iVar13 + uVar12) & 0x70) == 0x40)) &&
     ((*piVar9 == 2 || *piVar9 == 0x40001 &&
      (uVar8 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff,
      uVar8 == 0x7915 ||
      (uVar8 == 0x6867 ||
      (uVar8 == 0x7663 ||
      (uVar8 == 0x6632 ||
      (uVar8 == 0x7615 || (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xfffb) == 0x7622))
      )))))) {
    local_2b = 1;
  }
  iVar4 = *(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10);
  local_4b = 3;
  if (((iVar4 != 0) && (*(char *)(iVar4 + 1) != '\0')) && (local_31 == '\x01')) {
    *(undefined1 *)(iVar4 + 2) = 1;
  }
  if ((((*(ushort *)(param_2 + 0x18) & 0x4e) == 0) || (0xe < *(byte *)(param_2 + 0x1a))) &&
     (((local_5e & 0xe000) == 0 && (local_5e = local_5e & 0x1fff | 0x2000, -1 < DebugLevel)))) {
    printk("@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
           ,"ap_mlme_mgmtq_tx",((uint)*(byte *)(iVar13 + uVar12) << 0x1c) >> 0x1e,
           *(byte *)(iVar13 + uVar12) >> 4,local_48,local_32,local_40,local_33);
  }
  iVar4 = (int)*(char *)(*(int *)(param_3 + 0xc) + 0x4f);
  if ((iVar4 != 3) && (local_5c == 0)) {
    uVar8 = HcGetMgmtQueueIdx(param_1,param_2,iVar4);
    *(undefined1 *)(*(int *)(param_3 + 0xc) + 0x4f) = 3;
    local_40 = HcGetMgmtQueueIdx(param_1,param_2,(int)*(char *)(*(int *)(param_3 + 0xc) + 0x4f));
    bVar16 = -1 < DebugLevel;
    iVar7 = *(int *)(param_1 + 0x9dbac) + 1;
    *(int *)(param_1 + 0x9dbac) = iVar7;
    if (bVar16) {
      uVar8 = uVar8 & 0xff;
      uVar15 = (uint)local_40;
      uVar17 = (uint)(*(byte *)(iVar13 + uVar12) >> 4);
      printk("%s:pkt_t(%d),type(%d),sub_type(%d),q_idx(%d,%d),cnt(%d)\n","ap_mlme_mgmtq_tx",iVar4,
             ((uint)*(byte *)(iVar13 + uVar12) << 0x1c) >> 0x1e,uVar17,uVar8,uVar15,iVar7);
      if (((*(byte *)(iVar13 + uVar12) & 0xf0) == 0xd0) && (-1 < DebugLevel)) {
        printk("%s:cat(%d),act(%d)\n","ap_mlme_mgmtq_tx",*(undefined1 *)(iVar11 + 0x18),
               *(undefined1 *)(iVar11 + 0x19),uVar17,uVar8,uVar15,iVar7);
      }
    }
  }
  uVar5 = asic_mlme_hw_tx(param_1,iVar13,&local_5c,&local_5e,param_3);
  return uVar5;
}

