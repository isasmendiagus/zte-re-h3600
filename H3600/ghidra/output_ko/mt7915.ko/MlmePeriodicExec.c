// module: mt7915.ko
// function: MlmePeriodicExec @ 0x130bd8
// size: 2964 bytes
//

void MlmePeriodicExec(undefined4 param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  int extraout_r1;
  int extraout_r1_00;
  int extraout_r1_01;
  int *piVar9;
  int *piVar10;
  int extraout_r1_02;
  uint uVar11;
  int *piVar12;
  char cVar13;
  int *piVar14;
  int *piVar15;
  int *piVar16;
  undefined *puVar17;
  byte bVar18;
  uint uVar19;
  int *piVar20;
  byte bVar21;
  int *piVar22;
  int *piVar23;
  int *piVar24;
  int *piVar25;
  undefined8 uVar26;
  int *local_ac;
  int *local_a0;
  uint local_9c;
  char *local_98;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  undefined1 auStack_40 [28];
  
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_2 + 0xa797a0));
  iVar4 = hc_get_chip_ops(*(undefined4 *)(param_2 + 0xa797a0));
  if (((((*(uint *)(param_2 + 0xa39f84) & 0x8000140) != 0) ||
       (iVar5 = IsHcAllSupportedBandsRadioOff(param_2), iVar5 != 0)) ||
      ((*(uint *)(param_2 + 0xa39f84) & 0x10000000) == 0)) ||
     ((*(char *)(param_2 + 0x286285) == '\0' && ("hif_set_WPDMA"[param_2 + 0xc] == '\x01')))) {
    return;
  }
  *(undefined1 *)(param_2 + 0xa39fac) = 0;
  *(int *)(param_2 + 0x829214) = *(int *)(param_2 + 0x829214) + 1;
  *(int *)(param_2 + 0x829218) = *(int *)(param_2 + 0x829218) + 1;
  uVar11 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_2 + 0xc) & 0xffff;
  if (uVar11 == 0x7915 ||
      (uVar11 == 0x7663 ||
      (uVar11 == 0x7615 || (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_2 + 0xc) & 0xfffb) == 0x7622)
      )) {
    BcnCheck(param_2);
    uVar11 = *(uint *)(param_2 + 0x829214);
    if ((uVar11 == (uVar11 / 5) * 5) &&
       ((RTMP_UPDATE_MIB_COUNTER(param_2,uVar11,uVar11 * -0x33333333),
        (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_2 + 0xc) & 0xffff) != 0x7915 ||
        (*(uint *)(param_2 + 0x829214) == (*(uint *)(param_2 + 0x829214) / 10) * 10)))) {
      Smart_Carrier_Sense(param_2);
    }
  }
  if (*(code **)(iVar4 + 0x1c0) != (code *)0x0) {
    (**(code **)(iVar4 + 0x1c0))(param_2);
  }
  ba_timeout_monitor(param_2);
  uVar11 = *(uint *)(param_2 + 0x794b4c);
  iVar4 = extraout_r1;
  if (uVar11 == 0) {
LAB_00130db8:
    uVar19 = *(uint *)(param_2 + 0x829214);
  }
  else {
    uVar19 = *(uint *)(param_2 + 0x829214);
    __aeabi_uidivmod(uVar19,uVar11 / 100,uVar11 * 0x51eb851f);
    iVar4 = extraout_r1_00;
    if (extraout_r1_00 == 0) {
      uVar26 = RTMPAutoRateSwitchCheck(param_2);
      iVar4 = (int)((ulonglong)uVar26 >> 0x20);
      if ((int)uVar26 == 1) {
        if (*(char *)(iVar3 + 0x150) == '\x01') goto LAB_00130dbc;
        cVar13 = *(char *)(param_2 + 0x286285);
        if (cVar13 == '\x01') {
          APMlmeDynamicTxRateSwitching(param_2);
          cVar13 = *(char *)(param_2 + 0x286285);
          iVar4 = extraout_r1_02;
        }
        if (((cVar13 == '\0') && ((*(uint *)(&DAT_0057ffbc + param_2) & 0x80) != 0)) &&
           ((&DAT_00580018)[param_2] == '\0')) {
          MlmeDynamicTxRateSwitchingNew(param_2);
          iVar4 = extraout_r1_01;
        }
      }
      else {
        uVar26 = hc_get_hif_type(*(undefined4 *)(param_2 + 0xa797a0));
        iVar4 = (int)((ulonglong)uVar26 >> 0x20);
        if ((int)uVar26 == 2) {
          uVar11 = 0;
          while( true ) {
            uVar19 = uVar11 & 0xffff;
            uVar26 = HcGetMaxStaNum(param_2);
            iVar4 = (int)((ulonglong)uVar26 >> 0x20);
            if ((uint)uVar26 <= uVar19) break;
            uVar26 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_2 + 0xa797a0));
            iVar4 = (int)((ulonglong)uVar26 >> 0x20);
            if ((uint)uVar26 <= uVar19) break;
            iVar3 = uVar19 * 0x14c0 + param_2;
            iVar4 = *(int *)(iVar3 + 0xa1d20);
            if ((iVar4 != 0) &&
               (((((iVar4 != 0x20001 && (iVar4 != 2)) && (iVar4 != 0x40001)) ||
                 (*(int *)(iVar3 + 0xa1e1c) == 2)) && (param_2 + uVar19 * 0x14c0 + 0xa1d20 != 0))))
            {
              AsicTxCntUpdate(param_2,*(undefined2 *)(param_2 + uVar19 * 0x14c0 + 0xa1e00),
                              auStack_40);
            }
            uVar11 = uVar11 + 1;
          }
        }
      }
      goto LAB_00130db8;
    }
  }
LAB_00130dbc:
  if (uVar19 != (uVar19 / 10) * 10) goto LAB_00130dd8;
  *(int *)(param_2 + 0x82921c) = *(int *)(param_2 + 0x82921c) + 1;
  uVar11 = hc_get_asic_cap(*(undefined4 *)(param_2 + 0xa797a0),iVar4,uVar19 * -0x33333333);
  if ((uVar11 & 0x10000) == 0) {
    mt_dynamic_wmm_be_tx_op(param_2,0x32);
  }
  else {
    MtCmdCr4QueryBssAcQPktNum(param_2,0x80ffffff);
  }
  if ((&DAT_0036b920)[param_2] != '\0') {
    BndStrg_UpdateChannelUtilization(param_2);
  }
  *(undefined4 *)(param_2 + 0x7960e8) = jiffies;
  RTMP_UPDATE_RAW_COUNTER(param_2);
  iVar3 = hc_get_chip_ops(*(undefined4 *)(param_2 + 0xa797a0));
  if (*(code **)(iVar3 + 0xa4) != (code *)0x0) {
    (**(code **)(iVar3 + 0xa4))(param_2);
  }
  ORIBATimerTimeout(param_2);
  if (*(char *)(param_2 + 0x829222) != '\0') {
    uVar11 = *(uint *)(param_2 + 0x82921c);
    if ((uint)(*(int *)(param_2 + 0xa39e24) + *(int *)(param_2 + 0xa39e20) +
              *(int *)(param_2 + 0xa39e1c)) < 0x33) {
      iVar3 = uVar11 * -0x55555555;
      uVar19 = (uVar11 / 3) * 3;
    }
    else {
      iVar3 = uVar11 * -0x33333333;
      uVar19 = (uVar11 / 10) * 10;
    }
    if (uVar11 == uVar19) {
      AsicEvaluateRxAnt(param_2,uVar11,iVar3);
    }
  }
  hc_get_hif_type(*(undefined4 *)(param_2 + 0xa797a0));
  RTMP_SET_UPDATE_RSSI(param_2);
  uVar11 = HcGetAmountOfBand(param_2);
  if (uVar11 != 0) {
    local_98 = (char *)(param_2 + 0xa7c303);
    piVar14 = (int *)(param_2 + 0xa7c318);
    piVar9 = (int *)(param_2 + 0xa7c310);
    piVar16 = (int *)(param_2 + 0xa7c320);
    piVar24 = (int *)(param_2 + 0xa7c328);
    piVar20 = (int *)(param_2 + 0xa7c308);
    piVar23 = (int *)(param_2 + 0xa7c330);
    local_9c = 0;
    local_ac = (int *)(param_2 + 0xa7c338);
    local_a0 = (int *)(param_2 + 0xa7c340);
    iVar3 = param_2;
    do {
      local_98 = local_98 + 1;
      if (*local_98 == '\x01') {
        piVar6 = (int *)(iVar3 + 0xa7c358);
        piVar7 = (int *)(iVar3 + 0xa7c348);
        *piVar9 = 0;
        piVar22 = (int *)(iVar3 + 0xa7c368);
        *piVar20 = 0;
        *piVar14 = 0;
        *piVar16 = 0;
        *piVar24 = 0;
        *piVar23 = 0;
        piVar15 = (int *)(iVar3 + 0xa7c378);
        *local_a0 = 0;
        *local_ac = 0;
        piVar12 = (int *)(iVar3 + 0xa7c3a8);
        local_88 = *piVar9;
        piVar25 = (int *)(iVar3 + 0xa7c388);
        piVar8 = (int *)(iVar3 + 0xa7c398);
        local_74 = 0;
        piVar10 = (int *)(iVar3 + 0xa7c3b8);
        local_8c = *piVar20;
        local_78 = 0;
        local_90 = *piVar14;
        local_84 = *piVar16;
        local_80 = *piVar24;
        local_7c = *piVar23;
        bVar2 = false;
        do {
          piVar6 = piVar6 + 1;
          piVar7 = piVar7 + 1;
          local_88 = local_88 + *piVar6;
          local_8c = local_8c + *piVar7;
          piVar22 = piVar22 + 1;
          piVar15 = piVar15 + 1;
          local_90 = local_90 + *piVar22;
          piVar25 = piVar25 + 1;
          local_84 = local_84 + *piVar15;
          piVar8 = piVar8 + 1;
          local_80 = local_80 + *piVar25;
          piVar10 = piVar10 + 1;
          local_7c = local_7c + *piVar8;
          piVar12 = piVar12 + 1;
          local_78 = local_78 + *piVar10;
          local_74 = local_74 + *piVar12;
          bVar1 = !bVar2;
          bVar2 = true;
        } while (bVar1);
        *piVar9 = local_88;
        *piVar20 = local_8c;
        *piVar14 = local_90;
        *piVar16 = local_84;
        *piVar24 = local_80;
        *piVar23 = local_7c;
        *local_a0 = local_78;
        *local_ac = local_74;
      }
      piVar9 = piVar9 + 1;
      piVar20 = piVar20 + 1;
      local_9c = local_9c + 1;
      piVar14 = piVar14 + 1;
      piVar16 = piVar16 + 1;
      piVar24 = piVar24 + 1;
      piVar23 = piVar23 + 1;
      iVar3 = iVar3 + 8;
      local_a0 = local_a0 + 1;
      local_ac = local_ac + 1;
    } while ((local_9c & 0xff) < uVar11);
  }
  if (*(char *)(param_2 + 0x286285) == '\x01') {
    APMlmePeriodicExec(param_2);
    if (*(char *)(param_2 + 0xa78ad2) != '\0') {
      ChannelQualityDetection(param_2);
    }
    iVar3 = hc_get_hif_type(*(undefined4 *)(param_2 + 0xa797a0));
    if (iVar3 == 2) {
      CCI_ACI_scenario_maintain(param_2);
      Mumimo_scenario_maintain(param_2);
    }
    if (((*(int *)(param_2 + 0xa39e0c) == 0) && ((*(uint *)(param_2 + 0xa39f84) & 0x4000) == 0)) &&
       (((*(uint *)(param_2 + 0x795124) & 0x80) != 0 &&
        ((*(char *)(param_2 + 0x795074) != '\x01' || (*(char *)(param_2 + 0xa37728) != '\x02'))))))
    {
      *(int *)(param_2 + 0xa39fb0) = *(int *)(param_2 + 0xa39fb0) + 1;
    }
    else {
      *(undefined4 *)(param_2 + 0xa39fb0) = 0;
    }
    if ((((*(int *)(param_2 + 0xa39e0c) == 0 && *(char *)(param_2 + 0x79504d) != '\0') &&
         ((*(uint *)(param_2 + 0xa39f84) & 0x4000) == 0)) &&
        ((*(uint *)(param_2 + 0x795124) & 0x80) != 0)) &&
       ((*(char *)(param_2 + 0x795074) != '\x01' || (*(char *)(param_2 + 0xa37728) != '\x02')))) {
      uVar11 = *(int *)(param_2 + 0xa39fb0) + 1;
      *(uint *)(param_2 + 0xa39fb0) = uVar11;
      if (1 < uVar11) {
        if (1 < DebugLevel) {
          printk("MAC specific condition\n");
        }
        AsicSetMacWD(param_2);
        Show_QoSLoad_Proc(param_2,0);
      }
    }
    else {
      *(undefined4 *)(param_2 + 0xa39fb0) = 0;
    }
    cVar13 = *(char *)(param_2 + 0x286285);
    if (cVar13 == '\0') goto LAB_001310b8;
LAB_00131108:
    if (cVar13 == '\x01') {
      if ((byte)(&DAT_003678f9)[param_2] < 2) {
        if ((&DAT_003678f9)[param_2] == 0) goto LAB_00131110;
        bVar18 = 1;
      }
      else {
        bVar18 = 2;
      }
      puVar17 = &DAT_0036db58 + param_2;
      bVar21 = 0;
      do {
        bVar21 = bVar21 + 1;
        if (puVar17[0x213336] != '\0') {
          if (*(char *)(param_2 + 0x79504c) != '\0') {
            sta_2040_coex_scan_check(param_2,puVar17);
          }
          MlmeCheckPsmChange(param_2,puVar17);
        }
        puVar17 = puVar17 + 0x2137b0;
      } while (bVar21 < bVar18);
    }
  }
  else if (*(char *)(param_2 + 0x286285) == '\0') {
LAB_001310b8:
    if (*(char *)(param_2 + 0x794ab8) != '\0') {
      if ((&DAT_0036e600)[param_2] != '\0') {
        STAMlmePeriodicExec(param_2,&DAT_0036db58 + param_2);
      }
      if ((1 < *(byte *)(param_2 + 0x794ab8)) && ((&DAT_00581db0)[param_2] != '\0')) {
        STAMlmePeriodicExec(param_2,&DAT_00581308 + param_2);
      }
    }
    cVar13 = *(char *)(param_2 + 0x286285);
    goto LAB_00131108;
  }
LAB_00131110:
  iVar3 = hc_get_chip_ops(*(undefined4 *)(param_2 + 0xa797a0));
  if (*(code **)(iVar3 + 0xa4) != (code *)0x0) {
    (**(code **)(iVar3 + 0xa4))(param_2);
  }
  *(undefined4 *)(param_2 + 0xa39e84) = *(undefined4 *)(param_2 + 0xa39e28);
  if ((*(uint *)(param_2 + 0xa3ac14) & 1) == 0) {
    FUN_001288b4(param_2);
  }
  ZTE_Intereface_Throughput(param_2);
  iVar3 = ZTE_WLAN_Temperature_Protection_Enable();
  if ((((iVar3 != 0) && ((*(uint *)(param_2 + 0xa3ac14) & 1) == 0)) &&
      ((*(int *)(param_2 + 0xa77bb4) != 1 ||
       ((*(uint *)(*(int *)(param_2 + 0xa77bb8) + 0x4e0) & 1) == 0)))) &&
     ((*(uint *)(param_2 + 0x82921c) & 3) == 0)) {
    ZTE_Temperature_Protection_Work_Schedule();
  }
  if (*(char *)(param_2 + 0xa7d164) != '\0') {
    MlmeEnqueue(param_2,0x34,0,0,0,0);
  }
  RtmpOsMlmeUp(param_2 + 0x286298);
LAB_00130dd8:
  scan_partial_trigger_checker(param_2);
  if (*(char *)(param_2 + 0x794b24) != '\0') {
    WSC_HDR_BTN_CheckHandler(param_2);
  }
  *(undefined1 *)(param_2 + 0xa39fac) = 0;
  return;
}

