// module: mt7915.ko
// function: operate_loader_phy @ 0x107068
// size: 1416 bytes
//

void operate_loader_phy(int param_1,undefined1 *param_2)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  int extraout_r1;
  int extraout_r1_00;
  ushort uVar6;
  ushort uVar7;
  uint uVar8;
  int iVar9;
  ushort uVar10;
  int *piVar11;
  int *piVar12;
  int iVar13;
  undefined1 *puVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined1 local_40 [4];
  undefined1 *local_3c;
  undefined1 local_36;
  bool local_35;
  byte local_34;
  byte local_33;
  char local_32;
  char local_31;
  char local_30;
  undefined1 local_2f;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 auStack_2b [3];
  byte local_28;
  undefined1 local_27;
  char local_26;
  undefined1 local_25;
  undefined1 local_24;
  
  if (param_1 == 0) {
    return;
  }
  iVar13 = *(int *)(param_1 + 8);
  if (2 < DebugLevel) {
    printk("%s(): oper_cfg: prim_ch(%d), ht_bw(%d), extcha(%d), vht_bw(%d), cen_ch_2(%d), PhyMode=%d!\n"
           ,"operate_loader_phy",param_2[4],param_2[1],param_2[3],param_2[2],param_2[5],
           *(undefined2 *)(param_1 + 0x18));
  }
  os_zero_mem(&local_36,0xb);
  cVar1 = param_2[4];
  if (cVar1 == '\0') {
    if (-1 < DebugLevel) {
      printk("%s : no prim_ch value for adjust!\n","phy_freq_adjust");
    }
    goto LAB_001070bc;
  }
  uVar3 = *(ushort *)(param_1 + 0x18);
  local_36 = *param_2;
  local_2d = param_2[6];
  uVar10 = uVar3 & 0x118;
  local_2c = param_2[7];
  local_35 = false;
  local_32 = '\0';
  local_34 = 0;
  local_2f = 0;
  local_31 = cVar1;
  local_30 = cVar1;
  if ((uVar3 & 0x118) == 0) {
    uVar7 = uVar3 & 0x120;
    uVar6 = uVar10;
    if ((uVar3 & 0x120) == 0) goto LAB_00107208;
LAB_0010737c:
    local_34 = (byte)uVar6;
    if (uVar10 == 1) goto LAB_0010738c;
    local_33 = 0;
  }
  else {
    local_35 = (bool)param_2[1];
    local_32 = param_2[3];
    iVar4 = is_testmode_wdev(*(undefined4 *)(param_1 + 0x14));
    if (iVar4 == 0) {
      ht_ext_cha_adjust(*(undefined4 *)(param_1 + 8),local_31,&local_35,&local_32,param_1);
    }
    uVar7 = (ushort)local_35;
    if ((*(ushort *)(param_1 + 0x18) & 0x120) != 0) {
      uVar10 = uVar7;
      uVar6 = 0;
      if (uVar7 != 0) {
        uVar6 = (ushort)(byte)param_2[2];
      }
      goto LAB_0010737c;
    }
LAB_00107208:
    uVar6 = (ushort)local_34;
    if (uVar7 == 1) {
LAB_0010738c:
      if (uVar6 == 1) {
        local_33 = 2;
      }
      else if (uVar6 == 2) {
        local_33 = 3;
      }
      else if (uVar6 == 3) {
        local_33 = 6;
      }
      else {
        local_33 = 1;
      }
    }
    else {
      local_33 = 0;
    }
  }
  iVar4 = is_testmode_wdev(*(undefined4 *)(param_1 + 0x14));
  if (iVar4 == 0) {
    uVar5 = get_channel_bw_cap(param_1,local_31);
    uVar8 = (uint)local_33;
    if (uVar8 <= uVar5) goto LAB_00107230;
    if ((uVar8 != 6) || (1 < (uVar5 - 2 & 0xff))) {
      local_35 = uVar5 != 0;
      local_33 = (byte)uVar5;
      local_34 = rf_bw_2_vht_bw();
      uVar8 = (uint)local_33;
      goto LAB_00107230;
    }
LAB_00107240:
    iVar4 = is_testmode_wdev(*(undefined4 *)(param_1 + 0x14));
    if (iVar4 == 0) {
      local_30 = vht_cent_ch_freq(local_31,local_34,local_36);
    }
    else {
LAB_00107250:
      local_30 = local_31 - local_32;
    }
LAB_00107264:
    if (local_33 == 6) {
      local_2f = param_2[5];
    }
  }
  else {
    uVar8 = (uint)local_33;
LAB_00107230:
    if (uVar8 == 1) {
      iVar4 = is_testmode_wdev(*(undefined4 *)(param_1 + 0x14));
      if (iVar4 != 0) goto LAB_00107250;
      iVar4 = cal_ht_cent_ch(local_31,local_33,local_32,&local_30);
      if (iVar4 != 1) {
        if (-1 < DebugLevel) {
          printk("%s : buggy here.\n","phy_freq_adjust");
        }
        goto LAB_001070bc;
      }
      goto LAB_00107264;
    }
    if (1 < uVar8) goto LAB_00107240;
  }
  if (2 < DebugLevel) {
    printk("%s(): oper_dev after adjust: bw(%d), prim_ch(%d), cen_ch_1(%d), cen_ch_2(%d),ext_cha(%d)!\n"
           ,"operate_loader_phy");
  }
  iVar4 = *(int *)(param_1 + 8);
  piVar11 = (int *)(iVar4 + 8);
  os_move_mem(auStack_2b,&local_36,0xb);
  piVar12 = (int *)(iVar4 + 0x1a8);
  do {
    while( true ) {
      piVar11 = piVar11 + 1;
      iVar4 = *piVar11;
      if ((((iVar4 == 0) || (iVar9 = wlan_operate_get_state(iVar4), iVar9 == 0)) ||
          (iVar9 = wmode_band_equal(*(undefined2 *)(param_1 + 0x18),*(undefined2 *)(iVar4 + 0x18)),
          iVar9 == 0)) ||
         ((iVar4 = *(int *)(iVar4 + 0xb14), *(char *)(iVar4 + 1) != local_26 ||
          (bVar2 = *(byte *)(iVar4 + 2), bVar2 <= local_28)))) break;
      local_25 = *(undefined1 *)(iVar4 + 3);
      local_27 = *(undefined1 *)(iVar4 + 8);
      local_24 = *(undefined1 *)(iVar4 + 4);
      local_28 = bVar2;
      if (piVar11 == piVar12) goto LAB_00107320;
    }
  } while (piVar11 != piVar12);
LAB_00107320:
  if (2 < DebugLevel) {
    printk("%s(): oper_radio after decision: bw(%d), prim_ch(%d), cen_ch_1(%d), cen_ch_2(%d)!\n",
           "operate_loader_phy",local_28,local_26,local_25,local_24);
  }
  local_40[0] = 0;
  local_3c = auStack_2b;
  iVar4 = RadarChannelCheck(iVar13,local_26);
  if (iVar4 != 0) {
    DfsCacNormalStart(iVar13,param_1,2);
  }
  iVar4 = hc_radio_res_request(param_1,local_40);
  if (iVar4 != 1) {
    if (DebugLevel < 3) {
      return;
    }
    printk("%s(): oper_dev request radio fail! bw(%d), prim_ch(%d), cen_ch_1(%d), cen_ch_2(%d)!\n",
           "operate_loader_phy",local_33,local_31,local_30,local_2f);
    return;
  }
  DfsCacNormalStart(iVar13,param_1,0);
  iVar4 = RadarChannelCheck(iVar13,local_26);
  if (iVar4 != 0) {
    WrapDfsRadarDetectStart(iVar13,param_1);
  }
LAB_001070bc:
  wdev_sync_prim_ch(iVar13,param_1);
  uVar15 = HcGetBandByWdev(param_1);
  iVar4 = (int)((ulonglong)uVar15 >> 0x20);
  piVar11 = (int *)(iVar13 + 8);
  do {
    piVar11 = piVar11 + 1;
    iVar9 = *piVar11;
    if (iVar9 != 0) {
      uVar16 = HcIsRadioAcq(iVar9,iVar4);
      iVar4 = (int)((ulonglong)uVar16 >> 0x20);
      if ((int)uVar16 != 0) {
        uVar16 = HcGetBandByWdev(iVar9);
        iVar4 = (int)((ulonglong)uVar16 >> 0x20);
        if ((int)uVar16 == (int)uVar15) {
          puVar14 = *(undefined1 **)(iVar9 + 0xb14);
          *puVar14 = local_36;
          puVar14[1] = local_31;
          puVar14[0x20] = local_31;
          puVar14[3] = local_30;
          puVar14[9] = local_35;
          puVar14[4] = local_2f;
          puVar14[2] = local_33;
          operate_loader_ht_bw(puVar14);
          puVar14[8] = local_32;
          operate_loader_ext_cha(puVar14);
          puVar14[0x52] = local_34;
          operate_loader_vht_bw(puVar14);
          uVar16 = OS_TEST_BIT(1,iVar9 + 0x88c);
          iVar4 = (int)((ulonglong)uVar16 >> 0x20);
          if ((((int)uVar16 != 0) && (iVar4 = iVar9, *(int *)(iVar9 + 8) != 0)) &&
             (RTMPResumeMsduTransmission(), iVar4 = extraout_r1, -1 < DebugLevel)) {
            printk("%s : forbid_data_tx MSDU_FORBID_CHANNEL_MISMATCH Recovery.\n",
                   "operate_loader_phy");
            iVar4 = extraout_r1_00;
          }
        }
      }
    }
  } while (piVar11 != (int *)(iVar13 + 0x1a8));
  return;
}

