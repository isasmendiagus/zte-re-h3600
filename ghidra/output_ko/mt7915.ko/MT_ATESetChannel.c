// module: mt7915.ko
// function: MT_ATESetChannel @ 0x28bca8
// size: 2580 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4
MT_ATESetChannel(int param_1,undefined4 param_2,uint param_3,undefined4 param_4,uint param_5)

{
  undefined1 uVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  ushort uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  char cVar14;
  byte bVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  undefined1 *puVar20;
  int iVar21;
  undefined4 uVar22;
  uint uVar23;
  undefined2 uVar24;
  uint uVar25;
  bool bVar26;
  uint local_90;
  uint local_88;
  uint local_78;
  uint local_6c;
  uint local_68 [4];
  uint local_58 [12];
  undefined1 auStack_28 [4];
  
  bVar15 = *(byte *)(param_1 + 0xa3ae36);
  uVar23 = (uint)bVar15;
  iVar9 = net_ad_wrap_service();
  iVar21 = uVar23 * 0xd18;
  uVar16 = (uint)*(byte *)(iVar9 + iVar21 + 0x1130);
  iVar9 = net_ad_wrap_service(param_1);
  uVar17 = (uint)*(byte *)(iVar9 + iVar21 + 0x1136);
  iVar9 = net_ad_wrap_service(param_1);
  uVar18 = (uint)*(byte *)(iVar9 + iVar21 + 0x1137);
  iVar9 = net_ad_wrap_service(param_1);
  uVar1 = *(undefined1 *)(iVar9 + iVar21 + 0x1135);
  iVar9 = net_ad_wrap_service(param_1);
  uVar25 = *(uint *)(iVar9 + iVar21 + 0x1128);
  iVar9 = net_ad_wrap_service(param_1);
  uVar6 = *(ushort *)(iVar9 + iVar21 + 0x112e);
  iVar9 = net_ad_wrap_service(param_1);
  cVar14 = *(char *)(iVar9 + iVar21 + 0x11cc);
  iVar9 = net_ad_wrap_service(param_1);
  local_68[2] = 0xfffffffe;
  local_68[3] = 2;
  local_58[0] = 0xfffffffa;
  local_58[1] = 0xfffffffe;
  local_58[2] = 2;
  local_58[3] = 6;
  cVar2 = *(char *)(iVar9 + iVar21 + 0x11cd);
  local_58[4] = 0xfffffff2;
  local_58[5] = 0xfffffff6;
  local_58[6] = 0xfffffffa;
  local_58[7] = 0xfffffffe;
  local_58[8] = 2;
  local_58[9] = 6;
  local_58[10] = 10;
  local_58[0xb] = 0xe;
  iVar9 = net_ad_wrap_service(param_1);
  local_88 = (uint)*(byte *)(iVar9 + iVar21 + 0x1143);
  iVar9 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar10 = net_ad_wrap_service(param_1);
  iVar10 = *(int *)(iVar10 + iVar21 + 0x504);
  if (iVar10 == 0) {
LAB_0028bec4:
    if (-1 < DebugLevel) {
      printk("%s: invalid wdev\n","MT_ATESetChannel");
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  if (0 < DebugLevel) {
    printk("%s: wdev_idx=%d, ch=%d\n","MT_ATESetChannel",*(undefined1 *)(iVar10 + 0xc),
           *(undefined1 *)(iVar10 + 0x1a));
  }
  iVar21 = net_ad_wrap_service(param_1);
  iVar21 = *(int *)(uVar23 * 0xd18 + iVar21 + 0x508);
  if (iVar21 == 0) goto LAB_0028bec4;
  if (0 < DebugLevel) {
    printk("%s: wdev_idx(txd)=%d, ch=%d\n","MT_ATESetChannel",*(undefined1 *)(iVar21 + 0xc),
           *(undefined1 *)(iVar21 + 0x1a));
  }
  HcReleaseRadioForWdev(param_1,iVar21);
  HcReleaseRadioForWdev(param_1,iVar10);
  local_68[0] = (uint)*(byte *)(iVar9 + 0x6d);
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    if (local_68[0] < 2) {
      local_68[0] = 1;
    }
    else {
      local_68[0] = (uint)(*(byte *)(iVar9 + 0x6d) >> 1);
    }
  }
  local_68[1] = uVar17 - 1;
  local_90 = uVar16;
  switch(local_68[1]) {
  case 0:
    if (param_3 < 2) {
      uVar19 = local_68[param_3 + 2];
LAB_0028bfb0:
      local_6c = uVar19 & 0xff;
      local_78 = uVar16 + local_6c & 0xff;
      if (((int)(uVar19 + uVar16) < 1) || ((int)(uVar16 - uVar19) < 1)) goto LAB_0028bf64;
      goto LAB_0028bfdc;
    }
    break;
  case 1:
    if (param_3 < 4) {
      puVar20 = auStack_28 + param_3 * 4;
LAB_0028bfa8:
      uVar19 = *(uint *)(puVar20 + -0x30);
      uVar16 = local_90;
      goto LAB_0028bfb0;
    }
    break;
  case 2:
    if (param_3 < 8) {
      uVar19 = local_58[param_3 + 4];
      goto LAB_0028bfb0;
    }
    break;
  default:
    local_78 = uVar16;
    if (uVar17 < uVar18) {
      if (uVar18 != 2) {
        if (uVar18 == 3) {
          if (param_3 < 8) {
            iVar13 = net_ad_wrap_service(param_1);
            local_6c = (uint)(byte)local_58[param_3 + 4];
            local_88 = (uint)*(byte *)(uVar23 * 0xd18 + iVar13 + 0x1143);
            goto LAB_0028bfdc;
          }
        }
        else if (param_3 < 2) {
          local_88 = 0;
          local_6c = (uint)(byte)local_68[param_3 + 2];
          goto LAB_0028bfdc;
        }
        break;
      }
      if (3 < param_3) break;
      local_88 = 0;
      local_6c = (uint)(byte)local_58[param_3];
    }
    else {
      local_6c = 0;
      local_88 = 0;
    }
LAB_0028bfdc:
    iVar13 = net_ad_wrap_service(param_1);
    uVar16 = local_68[0];
    *(undefined1 *)(uVar23 * 0xd18 + iVar13 + 0x1132) = (undefined1)local_78;
    switch(uVar1) {
    case 0:
    case 1:
      uVar8 = local_68[0];
      do {
        if (uVar8 == 0) goto LAB_0028c3d8;
        uVar7 = uVar8 - 1;
        uVar19 = uVar8;
        uVar8 = uVar7;
      } while ((uVar25 >> (uVar7 & 0xff) & 1) == 0);
      break;
    case 2:
    case 3:
    case 4:
    case 0xc:
      if (cVar2 != '\0' || cVar14 != '\0') {
        if (((uVar25 & 1) == 0) || ((uVar25 & 2) == 0)) {
LAB_0028c3d8:
          uVar19 = 1;
        }
        else if ((uVar25 & 4) == 0) {
          uVar19 = 2;
        }
        else if ((uVar25 & 8) == 0) {
          uVar19 = 3;
        }
        else {
          uVar19 = 4;
        }
        break;
      }
    default:
      uVar19 = local_68[0];
      if (local_68[0] == 0) {
        uVar19 = 1;
      }
    }
    bVar26 = local_68[0] <= uVar19;
    local_68[0] = local_68[1];
    if (bVar26) {
      uVar19 = uVar16;
    }
    iVar13 = net_ad_wrap_service(param_1);
    cVar14 = (char)uVar19;
    *(byte *)(iVar13 + uVar23 * 0xd18 + 0x1140) = (byte)uVar6;
    iVar11 = net_ad_wrap_service(param_1);
    uVar16 = local_68[0];
    iVar13 = DebugLevel;
    *(char *)(iVar11 + uVar23 * 0xd18 + 0x113f) = cVar14;
    if (2 < iVar13) {
      printk("%s: T/Rx_sel:%x/%x, Tx Stream:%x, PhyMode:%x\n","MT_ATESetChannel",uVar25,(uint)uVar6,
             uVar19,0);
    }
    if (((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) &&
       (*(char *)(param_1 + 0x79504d) != '\0')) {
      if (uVar23 == 0) {
        bVar26 = (uVar6 & 1) == 0;
        uVar25 = uVar6 & 3;
        if (bVar26) {
          "rtmp_read_vow_parms_from_file"[param_1 + 3] = bVar15;
        }
        "rtmp_read_vow_parms_from_file"[param_1 + 2] = cVar14;
        if (!bVar26) {
          cVar14 = '\x01';
        }
        "SetPartProfileParameters"[param_1 + 0x1b] = (char)uVar25;
        if (!bVar26) {
          "rtmp_read_vow_parms_from_file"[param_1 + 3] = cVar14;
        }
        if (uVar25 >> 1 != 0) {
          "rtmp_read_vow_parms_from_file"[param_1 + 3] =
               "rtmp_read_vow_parms_from_file"[param_1 + 3] + '\x01';
        }
      }
      else {
        "rtmp_read_vow_parms_from_file"[param_1 + 4] = cVar14;
        uVar6 = uVar6 >> ((uVar23 & 0x7f) << 1);
        "rtmp_read_vow_parms_from_file"[param_1 + 1] = (byte)uVar6;
        bVar15 = (byte)uVar6 & 1;
        if ((uVar6 & 1) != 0) {
          bVar15 = 1;
        }
        "rtmp_read_vow_parms_from_file"[param_1 + 5] = bVar15;
        if ((uVar6 & 2) != 0) {
          "rtmp_read_vow_parms_from_file"[param_1 + 5] =
               "rtmp_read_vow_parms_from_file"[param_1 + 5] + '\x01';
        }
      }
    }
    else {
      "SetPartProfileParameters"[param_1 + 0x18] = (byte)((uVar19 & 0xf) << 4) | (byte)uVar6 & 0xf;
    }
    if (param_5 == 0) {
      uVar24 = 0x4e;
    }
    else {
      uVar24 = 0xb1;
    }
    *(undefined1 *)(iVar10 + 0x1a) = (undefined1)local_78;
    *(undefined2 *)(iVar10 + 0x18) = uVar24;
    bVar26 = uVar17 != 0;
    wlan_config_set_ch_band(iVar10,uVar24);
    wlan_config_set_ap_bw(iVar10,uVar18);
    uVar25 = local_90 - local_6c & 0xff;
    wlan_config_set_ap_cen(iVar10,uVar25);
    wlan_config_set_ht_bw(iVar10,bVar26);
    wlan_config_set_ext_cha(iVar10,local_6c);
    if (uVar17 < 2) {
      wlan_config_set_vht_bw(iVar10,0);
      wdev_attr_update(param_1,iVar10);
      wdev_edca_acquire(param_1,iVar10);
      *(undefined2 *)(iVar21 + 0x18) = uVar24;
      *(undefined1 *)(iVar21 + 0x1a) = (undefined1)local_78;
      wlan_config_set_ch_band(iVar21,uVar24);
      wlan_config_set_ap_bw(iVar21,uVar18);
      wlan_config_set_ap_cen(iVar21,uVar25);
      wlan_config_set_ht_bw(iVar21,bVar26);
      wlan_config_set_ext_cha(iVar21,local_6c);
      uVar16 = 0;
    }
    else {
      uVar16 = uVar16 & 0xff;
      wlan_config_set_vht_bw(iVar10,uVar16);
      wdev_attr_update(param_1,iVar10);
      wdev_edca_acquire(param_1,iVar10);
      *(undefined2 *)(iVar21 + 0x18) = uVar24;
      *(undefined1 *)(iVar21 + 0x1a) = (undefined1)local_78;
      wlan_config_set_ch_band(iVar21,uVar24);
      wlan_config_set_ap_bw(iVar21,uVar18);
      wlan_config_set_ap_cen(iVar21,uVar25);
      wlan_config_set_ht_bw(iVar21,bVar26);
      wlan_config_set_ext_cha(iVar21,local_6c);
    }
    wlan_config_set_vht_bw(iVar21,uVar16);
    wdev_attr_update(param_1,iVar21);
    wdev_edca_acquire(param_1,iVar21);
    "SetPartProfileParameters"[param_1 + 0x18] =
         "SetPartProfileParameters"[param_1 + 0x18] & 0xfU |
         (byte)((*(ushort *)(param_1 + 0xa3abc8) & 0xf) << 4);
    "SetPartProfileParameters"[param_1 + 0x18] =
         "SetPartProfileParameters"[param_1 + 0x18] & 0xf0U |
         (byte)*(undefined2 *)(param_1 + 0xa3abca) & 0xf;
    if (*(char *)(iVar9 + 0x210) == '\x01') {
      MtPwrLimitTblChProc(param_1,uVar23,param_5 & 0xff,local_78,local_90);
    }
    if (0 < DebugLevel) {
      printk("%s: control_band_idx:%u, bw:%x, ch:%u, ctrl_ch:%u, cntl_ch2:%u, pri_sel:%x\n",
             "MT_ATESetChannel",uVar23,uVar17,local_90,local_78,local_88,param_3);
    }
    iVar9 = net_ad_wrap_service(param_1);
    iVar10 = uVar23 * 0xd18;
    uVar1 = *(undefined1 *)(iVar9 + iVar10 + 0x1137);
    iVar9 = net_ad_wrap_service(param_1);
    uVar3 = *(undefined1 *)(iVar9 + iVar10 + 0x1135);
    iVar9 = net_ad_wrap_service(param_1);
    uVar4 = *(undefined1 *)(iVar9 + iVar10 + 0x1138);
    iVar9 = net_ad_wrap_service(param_1);
    uVar5 = *(undefined1 *)(iVar9 + iVar10 + 0x1139);
    iVar9 = net_ad_wrap_service(param_1);
    uVar22 = *(undefined4 *)(iVar9 + iVar10 + 0x6dc);
    uVar12 = MtATETssiTrainingProc(param_1,uVar17,uVar23);
    iVar9 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar9 + iVar10 + 0x1137) = uVar1;
    iVar9 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar9 + iVar10 + 0x1135) = uVar3;
    iVar9 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar9 + iVar10 + 0x1138) = uVar4;
    iVar9 = net_ad_wrap_service(param_1);
    *(undefined1 *)(iVar9 + iVar10 + 0x1139) = uVar5;
    iVar9 = net_ad_wrap_service(param_1);
    *(undefined4 *)(iVar9 + iVar10 + 0x6dc) = uVar22;
    return uVar12;
  case 5:
    if (param_3 < 8) {
      if (local_88 != 0 && local_88 < uVar16) {
        local_90 = local_88;
        local_88 = uVar16;
      }
      puVar20 = auStack_28 + param_3 * 4;
      if (param_3 < 4) goto LAB_0028bfa8;
      uVar19 = local_68[param_3];
      uVar16 = local_88;
      goto LAB_0028bfb0;
    }
  }
  if (DebugLevel < 0) {
    return 0xffffffff;
  }
  printk("%s: Invalid pri_sel:%x, Set Channel Fail\n","MT_ATESetChannel",param_3);
  uVar19 = 0;
  local_78 = 0;
LAB_0028bf64:
  if (-1 < DebugLevel) {
    printk("%s: Invalid Control Channel:%u|%u, Set Channel Fail\n","MT_ATESetChannel",local_78,
           local_90 - uVar19);
  }
  return 0xffffffff;
}

