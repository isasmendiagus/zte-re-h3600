// module: mt7915.ko
// function: sta_mlme_mgmtq_tx @ 0x5474c
// size: 1880 bytes
//

void sta_mlme_mgmtq_tx(int param_1,int param_2,int param_3)

{
  byte bVar1;
  ushort uVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte bVar7;
  byte bVar8;
  uint uVar9;
  ushort *puVar10;
  uint uVar11;
  int iVar12;
  bool bVar13;
  bool bVar14;
  uint uVar15;
  byte local_5d;
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
  undefined1 local_4f;
  byte local_4c;
  undefined1 local_4b;
  int local_48;
  undefined1 local_44;
  undefined1 local_41;
  undefined1 local_40;
  byte local_3f;
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
  uVar11 = (uint)*(byte *)(iVar4 + 2);
  local_5d = 0;
  sta_fill_offload_tx_blk(param_1,param_2,param_3);
  iVar12 = *(int *)(param_3 + 0x24);
  iVar4 = iVar12 + uVar11;
  if ((*(byte *)(iVar4 + 4) & 1) == 0) {
    bVar8 = *(byte *)(param_1 + 0x794cd5);
  }
  else {
    bVar8 = *(byte *)(param_1 + 0x794cd6);
  }
  if (0xe < *(byte *)(param_2 + 0x1a) && bVar8 < 4) {
    bVar8 = 4;
  }
  if ((*(ushort *)(param_2 + 0x18) == 7) || ((*(ushort *)(param_2 + 0x18) & 0x3f) != 0)) {
    if ((byte)"rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x20] < 0xf) {
      bVar7 = *(byte *)(param_2 + 0xb0b) & 0x1f;
      bVar1 = *(byte *)(param_2 + 0xb0a);
    }
    else {
      bVar1 = *(byte *)(param_2 + 0xb0a);
      bVar7 = *(byte *)(param_2 + 0xb0b) & 0x1f | 0x20;
    }
    *(byte *)(param_2 + 0xb0b) = bVar7;
    *(byte *)(param_2 + 0xb0a) = bVar1 & 0xc0;
  }
  if ((*(uint *)(param_1 + 0xa39f84) & 0x4000) == 0) {
    *(byte *)(iVar4 + 1) = *(byte *)(iVar4 + 1) & 0xef;
  }
  iVar5 = GetStaCfgByWdev(param_1,param_2);
  bVar1 = *(byte *)(iVar12 + uVar11);
  if (((bVar1 & 0xf0) == 0xd0 || (bVar1 & 0xf0) == 0xa0) ||
     (((bVar1 & 0xc) == 8 && ((bVar1 & 0x70) == 0x40)))) {
    iVar6 = RtmpPktPmBitCheck(param_1,iVar5);
    if (iVar6 == 1) {
      *(byte *)(iVar4 + 1) = *(byte *)(iVar4 + 1) | 0x10;
    }
    else if (((*(uint *)(iVar5 + 0x212464) & 0x81) != 0x81) ||
            ((*(uint *)(param_1 + 0xa39f84) & 0x4000) == 0)) {
      *(byte *)(iVar4 + 1) = *(byte *)(iVar4 + 1) & 0xef | (*(byte *)(param_1 + 0x794cc6) & 1) << 4;
    }
  }
  iVar5 = MacTableLookup2(param_1,iVar4 + 4,param_2);
  if ((*(byte *)(iVar12 + uVar11) & 0xc) == 4) {
    bVar8 = *(byte *)(iVar12 + uVar11) & 0xf0;
    if ((*(char *)(param_1 + 0x286285) == '\0') && (bVar8 == 0xa0)) {
      *(byte *)(iVar4 + 1) = *(byte *)(iVar4 + 1) | 0x10;
      bVar13 = false;
      bVar14 = false;
    }
    else if (bVar8 == 0x50) {
      bVar13 = false;
      *(undefined1 *)(iVar4 + 3) = 0;
      bVar14 = false;
      *(undefined1 *)(iVar4 + 2) = 100;
    }
    else {
LAB_00054bd0:
      bVar13 = false;
      bVar14 = false;
    }
  }
  else {
    bVar14 = (bool)(*(byte *)(iVar4 + 4) & 1);
    if ((*(byte *)(iVar4 + 4) & 1) == 0) {
      uVar3 = RTMPCalcDuration(param_1,bVar8,0xe);
      *(undefined2 *)(iVar4 + 2) = uVar3;
      bVar8 = *(byte *)(iVar12 + uVar11) & 0xfc;
      if (bVar8 == 0x50) {
        bVar13 = true;
      }
      else {
        if (bVar8 == 0x40) goto LAB_00054bd0;
        bVar13 = bVar14;
        bVar14 = iVar5 != 0 || (*(byte *)(iVar12 + uVar11) & 0xf0) != 0xc0;
      }
    }
    else {
      *(undefined1 *)(iVar4 + 2) = 0;
      *(undefined1 *)(iVar4 + 3) = 0;
      bVar13 = false;
      bVar14 = false;
    }
  }
  puVar10 = (ushort *)(param_1 + 0xa39f90);
  uVar2 = *puVar10;
  *puVar10 = uVar2 + 1;
  *(char *)(iVar4 + 0x17) = (char)(((uint)uVar2 << 0x14) >> 0x18);
  *(byte *)(iVar4 + 0x16) = *(byte *)(iVar4 + 0x16) & 0xf | (byte)((uVar2 & 0xf) << 4);
  if (0xfff < *puVar10) {
    *puVar10 = 0;
  }
  PMF_PerformTxFrameAction(param_1,iVar4,*(undefined4 *)(param_3 + 0x28),uVar11,&local_5d);
  if (iVar5 == 0) {
    bVar8 = *(byte *)(param_2 + 0xb0a) & 0x3f;
    uVar15 = 0;
    if (*(char *)(param_1 + 0xa78697) != '\0') {
      *(byte *)(param_2 + 0xb0b) = *(byte *)(param_2 + 0xb0b) & 0x1f | 0x80;
      *(byte *)(param_2 + 0xb0a) = *(byte *)(param_2 + 0xb0a) & 0xc0;
    }
  }
  else {
    uVar15 = (uint)*(ushort *)(iVar5 + 0xe0);
    bVar8 = *(byte *)(param_2 + 0xb0a) & 0x3f;
  }
  __memzero(&local_5c,0x34);
  if ((local_5d != 0) && (local_3f = local_5d, local_5d - 2 < 2)) {
    local_41 = 0;
  }
  uVar3 = (undefined2)uVar15;
  local_55 = 0;
  local_54 = 0;
  local_5a = 0;
  local_58 = 0;
  local_56 = *(byte *)(iVar4 + 4) & 1;
  local_51 = 0;
  local_3b = (byte)(((uint)*(byte *)(iVar12 + uVar11) << 0x1c) >> 0x1e);
  local_48 = *(int *)(param_3 + 0x28) - uVar11;
  local_2c = 0;
  local_34 = 1;
  local_3a = *(byte *)(iVar12 + uVar11) >> 4;
  bVar1 = *(byte *)(iVar12 + uVar11);
  uVar9 = (uint)bVar1;
  local_5c = uVar3;
  local_59 = bVar13;
  local_57 = bVar14;
  local_4c = bVar8;
  if ((bVar1 & 0xc) == 0) {
    local_44 = 0x18;
    local_2c = *(undefined1 *)(param_2 + 0x93c);
    if ((*(byte *)(iVar4 + 1) & 0x80) != 0) {
      local_44 = 0x1c;
    }
    local_50 = 3;
  }
  else if ((uVar9 & 0xc) == 8) {
    if (bVar1 >> 4 == 4) {
      local_4c = *(byte *)(param_2 + 0xb0a) & 0x3f;
      local_44 = 0x18;
    }
    else if (bVar1 >> 4 == 0xc) {
      local_4c = *(byte *)(param_2 + 0xb0a) & 0x3f;
      local_44 = 0x1a;
    }
    else {
      if (-1 < DebugLevel) {
        printk("%s(): FIXME!!!Unexpected frame(Type=%d, SubType=%d) send to MgmtRing, need to assign the length!\n"
               ,"sta_mlme_mgmtq_tx",(uVar9 << 0x1c) >> 0x1e);
      }
      hex_dump("DataFrame",iVar4,0x18);
    }
    if (iVar5 == 0) {
      local_50 = 3;
      local_5c = uVar3;
    }
    else if (*(char *)(param_1 + uVar15 * 0x620 + 0x2fa7c) == '\0') {
      local_50 = 3;
      local_5c = uVar3;
    }
    else {
      local_50 = 6;
      local_5c = uVar3;
    }
  }
  else if ((uVar9 & 0xc) == 4) {
    if (bVar1 >> 4 == 10) {
      local_44 = 0x10;
      local_50 = 3;
      local_4c = *(byte *)(param_2 + 0xb0a) & 0x3f;
    }
    else {
      if (DebugLevel < 0) goto LAB_00054b08;
      printk("%s(): FIXME!!!Unexpected frame(Type=%d, SubType=%d) send to MgmtRing, need to assign the length!\n"
             ,"sta_mlme_mgmtq_tx",(uVar9 << 0x1c) >> 0x1e);
      local_50 = 3;
    }
  }
  else if (DebugLevel < 0) {
LAB_00054b08:
    local_50 = 3;
  }
  else {
    printk("%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n",
           "sta_mlme_mgmtq_tx");
    local_50 = 3;
  }
  local_4f = 0;
  local_2b = 0;
  local_3d = 1;
  local_3c = 1;
  local_32 = HcGetWmmIdx(param_1,param_2);
  local_40 = HcGetMgmtQueueIdx(param_1,param_2,(int)*(char *)(*(int *)(param_3 + 0xc) + 0x4f));
  local_33 = *(undefined1 *)(param_2 + 0x29);
  if (3 < DebugLevel) {
    printk("%s(): %d, WMMSET=%d,QId=%d\n","sta_mlme_mgmtq_tx",0x805,local_32,local_40);
  }
  local_4b = 3;
  iVar4 = *(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10);
  if (((iVar4 != 0) && (*(char *)(iVar4 + 1) != '\0')) && (local_31 == '\x01')) {
    *(undefined1 *)(iVar4 + 2) = 1;
  }
  if (param_2 != 0) {
    if ((*(ushort *)(param_2 + 0x18) & 0x4e) == 0) {
      bVar8 = *(byte *)(param_2 + 0xb0b);
    }
    else {
      if (*(byte *)(param_2 + 0x1a) < 0xf) goto LAB_00054ac4;
      bVar8 = *(byte *)(param_2 + 0xb0b);
    }
    if (((bVar8 & 0xe0) == 0) && (*(byte *)(param_2 + 0xb0b) = bVar8 & 0x1f | 0x20, -1 < DebugLevel)
       ) {
      printk("@@@@ FIXME!! %s(): frame(Type=%x, SubType=%x) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
             ,"sta_mlme_mgmtq_tx",((uint)*(byte *)(iVar12 + uVar11) << 0x1c) >> 0x1e,
             *(byte *)(iVar12 + uVar11) >> 4,local_48,local_32,local_40,local_33);
    }
  }
LAB_00054ac4:
  asic_mlme_hw_tx(param_1,iVar12,&local_5c,param_2 + 0xb0a,param_3);
  return;
}

