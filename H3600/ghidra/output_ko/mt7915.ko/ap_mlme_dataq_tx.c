// module: mt7915.ko
// function: ap_mlme_dataq_tx @ 0x1b30c
// size: 2172 bytes
//

undefined4 ap_mlme_dataq_tx(int param_1,int param_2,int param_3)

{
  byte bVar1;
  ushort uVar2;
  undefined2 uVar3;
  byte *pbVar4;
  undefined4 uVar5;
  byte bVar6;
  char cVar7;
  uint uVar8;
  byte bVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  ushort *puVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  bool bVar18;
  uint uVar19;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_64;
  ushort local_60;
  undefined2 local_5e;
  short local_5c;
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
  byte local_40;
  undefined1 uStack_3f;
  undefined1 local_3e;
  undefined1 local_3d;
  undefined1 local_3c;
  byte local_3b;
  byte local_3a;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_2d;
  undefined1 local_2c;
  bool local_2b;
  
  piVar10 = *(int **)(param_3 + 0x14);
  pbVar4 = (byte *)hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar14 = (uint)pbVar4[2];
  if ((param_2 != 0) && (iVar11 = *(int *)(param_2 + 0x3fe4), iVar11 != 0)) {
    ap_fill_offload_tx_blk(param_1,param_2,param_3);
    iVar15 = *(int *)(param_3 + 0x24);
    uVar16 = iVar15 + uVar14;
    iVar12 = *(int *)(param_3 + 0x28);
    bVar9 = *(byte *)(uVar16 + 4);
    local_64 = bVar9 & 1;
    if ((bVar9 & 1) == 0) {
      bVar6 = *(byte *)(param_1 + 0x794cd5);
    }
    else {
      bVar6 = *(byte *)(param_1 + 0x794cd6);
    }
    local_60 = *(ushort *)(param_2 + 0xb0a);
    if (*(byte *)(param_2 + 0x1a) < 0xf || 3 < bVar6) {
      bVar1 = *(byte *)(iVar15 + uVar14);
    }
    else {
      bVar6 = 4;
      local_60 = local_60 & 0x1fc0 | 0x2000;
      bVar1 = *(byte *)(iVar15 + uVar14);
    }
    if ((bVar1 & 0xc) == 4) {
      if ((bVar1 & 0xf0) == 0x80) {
        local_74 = 0;
        local_78 = 1;
        local_64 = uVar16;
      }
      else if ((bVar1 & 0xf0) == 0x50) {
        local_74 = 0;
        uVar3 = RTMPCalcDuration(param_1,bVar6,(iVar12 + -4) - (uint)*pbVar4);
        local_78 = 0;
        local_64 = 0;
        *(undefined2 *)(uVar16 + 2) = uVar3;
      }
      else {
        local_74 = 0;
        local_78 = 0;
        local_64 = 0;
      }
    }
    else if ((bVar9 & 1) == 0) {
      uVar3 = RTMPCalcDuration(param_1,bVar6,0xe);
      *(undefined2 *)(uVar16 + 2) = uVar3;
      if ((*(byte *)(iVar15 + uVar14) & 0xf0) == 0x50) {
        local_74 = 1;
        local_78 = local_64;
      }
      else {
        local_78 = 1;
        local_74 = local_64;
      }
    }
    else {
      *(undefined1 *)(uVar16 + 2) = 0;
      local_74 = 0;
      *(undefined1 *)(uVar16 + 3) = 0;
      local_78 = 0;
      local_64 = 0;
    }
    puVar13 = (ushort *)(param_1 + 0xa39f90);
    uVar2 = *puVar13;
    *puVar13 = uVar2 + 1;
    *(char *)(uVar16 + 0x17) = (char)(((uint)uVar2 << 0x14) >> 0x18);
    *(byte *)(uVar16 + 0x16) = *(byte *)(uVar16 + 0x16) & 0xf | (byte)((uVar2 & 0xf) << 4);
    if (0xfff < *puVar13) {
      *puVar13 = 0;
    }
    if ((((*(byte *)(iVar15 + uVar14) & 0xf0) == 0x40) || (*(char *)(param_1 + 0x795074) != '\x01'))
       || (*(char *)(iVar11 + 4) == '\0')) {
      if (piVar10 == (int *)0x0) {
        local_7c = 0;
        if (0 < DebugLevel) {
          printk("pMacEntry is null !!\n");
        }
      }
      else {
        local_7c = (uint)*(ushort *)(piVar10 + 0x38);
      }
      bVar9 = *(byte *)(param_2 + 0xb0a) & 0x3f;
      __memzero(&local_5c);
      local_55 = 0;
      local_54 = 0;
      local_59 = (undefined1)local_74;
      local_5a = 0;
      local_5c = (short)local_7c;
      local_56 = *(byte *)(uVar16 + 4) & 1;
      local_58 = 0;
      local_57 = (undefined1)local_78;
      local_51 = 0;
      local_4f = 0;
      local_32 = HcGetWmmIdx(param_1,param_2);
      local_40 = HcGetMgmtQueueIdx(param_1,param_2,(int)*(char *)(*(int *)(param_3 + 0xc) + 0x4f));
      local_2c = 0;
      if (*(char *)(param_1 + 0x795943) != '\x01') {
        iVar11 = HcGetBandByWdev(param_2);
        if (iVar11 == 0) {
          local_3e = 0x18;
        }
        else {
          iVar11 = HcGetBandByWdev(param_2);
          if (iVar11 == 1) {
            local_3e = 0x19;
          }
        }
      }
      local_33 = *(undefined1 *)(param_2 + 0x29);
      local_48 = *(int *)(param_3 + 0x28) - uVar14;
      local_3b = (byte)(((uint)*(byte *)(iVar15 + uVar14) << 0x1c) >> 0x1e);
      local_3a = *(byte *)(iVar15 + uVar14) >> 4;
      bVar6 = *(byte *)(iVar15 + uVar14);
      uVar8 = (uint)bVar6;
      local_4c = bVar9;
      if ((bVar6 & 0xc) == 0) {
        local_44 = 0x18;
        if ((*(byte *)(uVar16 + 1) & 0x80) != 0) {
          local_44 = 0x1c;
        }
        local_50 = 3;
        uVar8 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
        if ((((uVar8 & 0x4000000) != 0) && ((*(byte *)(iVar15 + uVar14) & 0xf0) == 0xd0)) &&
           ((iVar11 = *(int *)(param_3 + 0x24) + uVar14, *(char *)(iVar11 + 0x18) == '\x03' &&
            (*(char *)(iVar11 + 0x19) == '\0')))) {
          uVar8 = (uint)*(byte *)(iVar11 + 0x1b) << 0x1a;
          local_4f = (byte)(uVar8 >> 0x1c);
          local_2d = 1;
          local_40 = *(byte *)((int)&WMM_UP2AC_MAP + (uVar8 >> 0x1c));
        }
        puVar13 = &local_60;
        PMF_PerformTxFrameAction(param_1,uVar16,*(undefined4 *)(param_3 + 0x28),uVar14,&uStack_3f);
        local_2c = *(undefined1 *)(param_2 + 0x93c);
      }
      else if ((uVar8 & 0xc) == 8) {
        if (bVar6 >> 4 == 4) {
          local_44 = 0x18;
          local_4c = (byte)local_60 & 0x3f;
        }
        else if (bVar6 >> 4 == 0xc) {
          local_44 = 0x1a;
          local_4c = (byte)local_60 & 0x3f;
        }
        else {
          if (-1 < DebugLevel) {
            printk("%s(): FIXME!!!Unexpected frame(Type=%d, SubType=%d) send to MgmtRing, need to assign the length!\n"
                   ,"ap_mlme_dataq_tx",(uVar8 << 0x1c) >> 0x1e);
          }
          hex_dump("DataFrame",iVar15,iVar12);
        }
        local_5c = (short)local_7c;
        if ((piVar10 == (int *)0x0) || (*(char *)(param_1 + local_7c * 0x620 + 0x2fa7c) == '\0')) {
          puVar13 = &local_60;
          local_50 = 3;
        }
        else {
          puVar13 = &local_60;
          local_50 = 6;
        }
      }
      else if ((uVar8 & 0xc) == 4) {
        if (bVar6 >> 4 == 8) {
          local_44 = 0x10;
          cVar7 = 't';
          local_50 = 5;
          local_4f = *(byte *)(local_64 + 0x11) >> 4;
          local_40 = *(byte *)((int)&WMM_UP2AC_MAP +
                              (((uint)*(byte *)(local_64 + 0x11) << 0x18) >> 0x1c));
          if (0xe < *(byte *)(param_2 + 0x1a)) {
            cVar7 = '\x01';
          }
          if (*(byte *)(param_2 + 0x1a) < 0xf) {
            local_5e._1_1_ = local_5e._1_1_ & 0x1f;
          }
          else {
            local_5e._1_1_ = local_5e._1_1_ & 0x1f | cVar7 << 5;
          }
          puVar13 = &local_5e;
          local_5e = ((local_5e._1_1_ & 0xfe) & 0xf9) << 8;
        }
        else {
          if (-1 < DebugLevel) {
            printk("%s(): FIXME!!!Unexpected frame(Type=%d, SubType=%d) send to MgmtRing, need to assign the length!\n"
                   ,"ap_mlme_dataq_tx",(uVar8 << 0x1c) >> 0x1e);
          }
          hex_dump("Control Frame",iVar15,iVar12);
          puVar13 = &local_60;
        }
      }
      else {
        puVar13 = &local_60;
      }
      local_3d = 1;
      local_3c = 1;
      local_4b = 3;
      local_2b = false;
      if (((*(byte *)(iVar15 + uVar14) & 0xc) == 8) &&
         (piVar10 != (int *)0x0 && (*(byte *)(iVar15 + uVar14) & 0x70) == 0x40)) {
        local_2b = *piVar10 == 2 || *piVar10 == 0x40001;
      }
      if (((((*(ushort *)(param_2 + 0x18) & 0x4e) == 0) || (0xe < *(byte *)(param_2 + 0x1a))) &&
          ((*(byte *)((int)puVar13 + 1) & 0xe0) == 0)) &&
         (*(byte *)((int)puVar13 + 1) = *(byte *)((int)puVar13 + 1) & 0x1f | 0x20, -1 < DebugLevel))
      {
        printk("@@@@ FIXME!! %s(): frame(Type=%d, SubType=%d) use the CCK RATE but wdev support A band only, mac_info.Length=%lu, mac_info.wmm_set=%d, mac_info.q_idx=%d, mac_info.OmacIdx=%d\n"
               ,"ap_mlme_dataq_tx",((uint)*(byte *)(iVar15 + uVar14) << 0x1c) >> 0x1e,
               *(byte *)(iVar15 + uVar14) >> 4,local_48,local_32,local_40,local_33);
      }
      iVar11 = (int)*(char *)(*(int *)(param_3 + 0xc) + 0x4f);
      if ((iVar11 != 3) && (local_5c == 0)) {
        uVar8 = HcGetMgmtQueueIdx(param_1,param_2,iVar11);
        *(undefined1 *)(*(int *)(param_3 + 0xc) + 0x4f) = 3;
        local_40 = HcGetMgmtQueueIdx(param_1,param_2,(int)*(char *)(*(int *)(param_3 + 0xc) + 0x4f))
        ;
        bVar18 = -1 < DebugLevel;
        iVar12 = *(int *)(param_1 + 0x9dbac) + 1;
        *(int *)(param_1 + 0x9dbac) = iVar12;
        if (bVar18) {
          uVar8 = uVar8 & 0xff;
          uVar17 = (uint)local_40;
          uVar19 = (uint)(*(byte *)(iVar15 + uVar14) >> 4);
          printk("%s:pkt_t(%d),type(%d),sub_type(%d),q_idx(%d,%d),cnt(%d)\n","ap_mlme_dataq_tx",
                 iVar11,((uint)*(byte *)(iVar15 + uVar14) << 0x1c) >> 0x1e,uVar19,uVar8,uVar17,
                 iVar12);
          if (((*(byte *)(iVar15 + uVar14) & 0xf0) == 0xd0) && (-1 < DebugLevel)) {
            printk("%s:cat(%d),act(%d)\n","ap_mlme_dataq_tx",*(undefined1 *)(uVar16 + 0x18),
                   *(undefined1 *)(uVar16 + 0x19),uVar19,uVar8,uVar17,iVar12);
          }
        }
      }
      uVar5 = asic_mlme_hw_tx(param_1,iVar15,&local_5c,puVar13,param_3);
    }
    else {
      if (-1 < DebugLevel) {
        printk("MlmeHardTransmit --> radar detect not in normal mode !!!\n");
      }
      RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc));
      uVar5 = 1;
    }
    return uVar5;
  }
  return 1;
}

