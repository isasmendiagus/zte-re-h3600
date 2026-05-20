// module: mt7915.ko
// function: wlan_dbg_show_radio_statistics @ 0x1585cc
// size: 608 bytes
//

undefined4 wlan_dbg_show_radio_statistics(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  undefined4 uVar23;
  undefined4 uVar24;
  undefined4 uVar25;
  undefined4 uVar26;
  undefined4 uVar27;
  undefined4 uVar28;
  undefined4 local_30;
  char *local_2c [2];
  
  local_30 = 0;
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  iVar2 = 0;
  if (iVar1 != 0) {
    iVar2 = HcGetBandByWdev();
  }
  iVar1 = 0;
  if (param_2 != 0) {
    iVar1 = os_str_tol(param_2,0,10);
  }
  os_alloc_mem(0,local_2c,0x400);
  if (local_2c[0] == (char *)0x0) {
    printk("\nwlan_dbg_show_radio_statistics Memory malloc failed\n");
    return 1;
  }
  RTMP_GET_TEMPERATURE(param_1,iVar2,&local_30);
  uVar3 = ZTE_Get_ChannelUtilization(param_1,iVar2);
  uVar9 = g_stWlanRadioStat._32_4_;
  uVar8 = g_stWlanRadioStat._28_4_;
  uVar10 = g_stWlanRadioStat._12_4_;
  uVar7 = g_stWlanRadioStat._4_4_;
  uVar6 = g_stWlanRadioStat._0_4_;
  *(undefined4 *)(g_stWlanRadioStat + iVar2 * 0x74 + 0x6c) = uVar3;
  uVar5 = *(undefined4 *)(g_stWlanRadioStat + iVar2 * 0x74 + 0x58);
  uVar11 = g_stWlanRadioStat._16_4_;
  uVar12 = g_stWlanRadioStat._20_4_;
  uVar13 = g_stWlanRadioStat._24_4_;
  uVar14 = g_stWlanRadioStat._36_4_;
  uVar15 = g_stWlanRadioStat._40_4_;
  uVar16 = g_stWlanRadioStat._44_4_;
  uVar17 = g_stWlanRadioStat._48_4_;
  uVar18 = g_stWlanRadioStat._52_4_;
  uVar19 = g_stWlanRadioStat._56_4_;
  uVar20 = g_stWlanRadioStat._60_4_;
  uVar21 = g_stWlanRadioStat._64_4_;
  uVar22 = g_stWlanRadioStat._68_4_;
  uVar23 = g_stWlanRadioStat._72_4_;
  uVar24 = g_stWlanRadioStat._76_4_;
  uVar25 = g_stWlanRadioStat._112_4_;
  uVar26 = g_stWlanRadioStat._80_4_;
  uVar27 = g_stWlanRadioStat._84_4_;
  uVar28 = g_stWlanRadioStat._8_4_;
  uVar4 = snprintf(local_2c[0],0x400,
                   "Temperature:        %d\nChannelUtilization: %lu\nTxDataPacketNum:    %lu\nTxFailPacketNum:    %lu\nTxFlowDiscardNum:   %lu\nTxPSDiscardNum:     %lu\nTxDataSuccPacketNum:%lu\nTxAllSuccPacketNum: %lu\nTxForbidPacketNum:  %lu\nTxQueueFullNum:     %lu\nRxAllPacketNum:     %lu\nRxDataPacketNum:    %lu\nRxMgmtPacketNum:    %lu\nRxCtrlPacketNum:    %lu\nRxNullPacketNum:    %lu\nRxFailPacketNum:    %lu\nRxDupDropPacketNum: %lu\nRxSeqSmallPacketNum:%lu\nRxSuccPacketIDMNum: %lu\nRxSuccPacketOSNum: %lu\nAllocMemFailNum:    %lu\nAllocMemFailSize:   %lu\nAPrestart:   %lu\nSER ERR:   %lu\nMem ERR:   %lu\nMem Num:   %lu\n"
                   ,local_30,uVar3,uVar6,uVar7,uVar8,uVar9,uVar10,g_stWlanRadioStat._16_4_,
                   g_stWlanRadioStat._20_4_,g_stWlanRadioStat._24_4_,g_stWlanRadioStat._36_4_,
                   g_stWlanRadioStat._40_4_,g_stWlanRadioStat._44_4_,g_stWlanRadioStat._48_4_,
                   g_stWlanRadioStat._52_4_,g_stWlanRadioStat._56_4_,g_stWlanRadioStat._60_4_,
                   g_stWlanRadioStat._64_4_,g_stWlanRadioStat._68_4_,g_stWlanRadioStat._72_4_,
                   g_stWlanRadioStat._76_4_,g_stWlanRadioStat._112_4_,uVar5,g_stWlanRadioStat._80_4_
                   ,g_stWlanRadioStat._84_4_,g_stWlanRadioStat._8_4_);
  if (uVar4 < 0x3ff) {
    if (g_stWlanRadioStat._96_4_ != 0) {
      iVar2 = snprintf(local_2c[0] + uVar4,0x400 - uVar4,
                       "TxFailLine:         %lu\npTxFailFunc:        %s\n",g_stWlanRadioStat._92_4_,
                       g_stWlanRadioStat._96_4_,uVar6,uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13,
                       uVar14,uVar15,uVar16,uVar17,uVar18,uVar19,uVar20,uVar21,uVar22,uVar23,uVar24,
                       uVar25,uVar5,uVar26,uVar27,uVar28);
      uVar4 = uVar4 + iVar2;
      if (0x3fe < uVar4) goto LAB_001587e0;
    }
    if (((g_stWlanRadioStat._104_4_ == 0) ||
        (iVar2 = snprintf(local_2c[0] + uVar4,0x400 - uVar4,
                          "RxFailLine:         %lu\npRxFailFunc:        %s\n",
                          g_stWlanRadioStat._100_4_,g_stWlanRadioStat._104_4_,uVar6,uVar7,uVar8,
                          uVar9,uVar10,uVar11,uVar12,uVar13,uVar14,uVar15,uVar16,uVar17,uVar18,
                          uVar19,uVar20,uVar21,uVar22,uVar23,uVar24,uVar25,uVar5,uVar26,uVar27,
                          uVar28), iVar2 + uVar4 < 0x3ff)) &&
       (printk(&_LC10,local_2c[0]), iVar1 != 0)) {
      __memzero(g_stWlanRadioStat,0xe8);
    }
  }
LAB_001587e0:
  os_free_mem(local_2c[0]);
  return 1;
}

