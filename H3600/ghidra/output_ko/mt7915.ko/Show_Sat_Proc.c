// module: mt7915.ko
// function: Show_Sat_Proc @ 0x2ede8
// size: 1672 bytes
//

undefined4 Show_Sat_Proc(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined *puVar5;
  char *pcVar6;
  int iVar7;
  char *pcVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int *piVar13;
  int *piVar14;
  bool bVar15;
  
  if ((2 < DebugLevel) &&
     (printk("TransmitCountFromOS = %d\n",*(undefined4 *)(param_1 + 0xa39c70)), 2 < DebugLevel)) {
    uVar3 = *(uint *)(param_1 + 0xa39c00);
    printk("TransmittedFragmentCount = %lld\n",uVar3,*(uint *)(param_1 + 0xa39c08) + uVar3,
           *(int *)(param_1 + 0xa39c0c) + (uint)CARRY4(*(uint *)(param_1 + 0xa39c08),uVar3));
    if ((((2 < DebugLevel) &&
         (((((printk("MulticastTransmittedFrameCount = %d\n",*(undefined4 *)(param_1 + 0xa39c08)),
             2 < DebugLevel &&
             (printk("FailedCount = %d\n",*(undefined4 *)(param_1 + 0xa39c10)), 2 < DebugLevel)) &&
            (printk("RetryCount = %d\n",*(undefined4 *)(param_1 + 0xa39c18)), 2 < DebugLevel)) &&
           ((printk("MultipleRetryCount = %d\n",*(undefined4 *)(param_1 + 0xa39c20)), 2 < DebugLevel
            && (printk("RTSSuccessCount = %d\n",*(undefined4 *)(param_1 + 0xa39c28)), 2 < DebugLevel
               )))) &&
          (printk("RTSFailureCount = %d\n",*(undefined4 *)(param_1 + 0xa39c30)), 2 < DebugLevel))))
        && (((printk("ACKFailureCount = %d\n",*(undefined4 *)(param_1 + 0xa39c38)), 2 < DebugLevel
             && (printk("FrameDuplicateCount = %d\n",*(undefined4 *)(param_1 + 0xa39c40)),
                2 < DebugLevel)) &&
            (printk("ReceivedFragmentCount = %d\n",*(undefined4 *)(param_1 + 0xa39c48)),
            2 < DebugLevel)))) &&
       ((((((printk("MulticastReceivedFrameCount = %d\n",*(undefined4 *)(param_1 + 0xa39c50)),
            2 < DebugLevel &&
            (printk("Rx drop due to out of resource  = %u\n",*(undefined4 *)(param_1 + 0xa39bf4)),
            2 < DebugLevel)) &&
           (printk("RealFcsErrCount = %d\n",*(undefined4 *)(param_1 + 0xa39e70)), 2 < DebugLevel))
          && ((printk("TransmittedFrameCount = %d\n",*(undefined4 *)(param_1 + 0xa39c00)),
              2 < DebugLevel &&
              (printk("WEPUndecryptableCount = %d\n",*(undefined4 *)(param_1 + 0xa39c68)),
              2 < DebugLevel)))) &&
         (((printk("\n===Some 11n statistics variables:\n"), 2 < DebugLevel &&
           ((printk("TxAMSDUCount = %u\n",*(undefined4 *)(param_1 + 0xa39ed8)), 2 < DebugLevel &&
            (printk("RxAMSDUCount = %u\n",*(undefined4 *)(param_1 + 0xa39ee0)), 2 < DebugLevel))))
          && (printk("TransmittedAMPDUCount = %u\n",*(undefined4 *)(param_1 + 0xa39ee8)),
             2 < DebugLevel)))) &&
        (((printk("TransmittedMPDUsInAMPDUCount = %u\n",*(undefined4 *)(param_1 + 0xa39ef0)),
          2 < DebugLevel &&
          (printk("TransmittedOctetsInAMPDUCount = %u\n",*(undefined4 *)(param_1 + 0xa39ef8)),
          2 < DebugLevel)) &&
         (printk("MPDUInReceivedAMPDUCount = %u\n",*(undefined4 *)(param_1 + 0xa39f00)),
         2 < DebugLevel)))))) {
      printk("fAnyStaFortyIntolerant=%d\n",*(undefined1 *)(param_1 + 0x285948));
    }
  }
  if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] != '\0') {
    pcVar6 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
             + param_1 + 0x33;
    pcVar8 = "[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n" + param_1 + 0x2c;
    iVar11 = 0;
    do {
      if (((2 < DebugLevel) && (printk("-- IF-ra%d --\n",iVar11), 2 < DebugLevel)) &&
         (printk("Packets Received = %u\n",*(undefined4 *)(pcVar8 + -0xc)), 2 < DebugLevel)) {
        printk("Packets Sent = %u\n",*(undefined4 *)(pcVar8 + -0x10));
        if (DebugLevel < 3) {
          if (*(int *)(pcVar6 + -8) == 0) goto LAB_0002f3f4;
        }
        else {
          printk("Bytes Received = %u\n",*(undefined4 *)(pcVar8 + -8));
          if (((2 < DebugLevel) &&
              (printk("Byte Sent = %u\n",*(undefined4 *)(pcVar8 + -4)), 2 < DebugLevel)) &&
             (printk("Error Packets Received = %u\n",*(undefined4 *)pcVar8), 2 < DebugLevel)) {
            printk("Drop Received Packets = %u\n",*(undefined4 *)(pcVar8 + 4));
            if (*(int *)(pcVar6 + -8) != 0) {
              if (DebugLevel < 3) goto LAB_0002ee54;
              puVar5 = &_LC334;
              if (*(int *)(pcVar6 + -4) != 1) {
                puVar5 = &_LC335;
              }
              printk("WscInfo:\n\tWscConfMode=%d\n\tWscMode=%s\n\tWscConfStatus=%d\n\tWscPinCode=%d\n\tWscState=0x%x\n\tWscStatus=0x%x\n"
                     ,*(int *)(pcVar6 + -8),puVar5,*pcVar6,*(undefined4 *)(pcVar6 + 0x14),
                     *(undefined4 *)(pcVar6 + 8),*(undefined4 *)(pcVar6 + 4));
            }
LAB_0002f3f4:
            if (2 < DebugLevel) {
              printk("-- IF-ra%d end --\n",iVar11);
            }
          }
        }
      }
LAB_0002ee54:
      iVar11 = iVar11 + 1;
      pcVar6 = pcVar6 + 0x5834;
      pcVar8 = pcVar8 + 0x5834;
    } while (iVar11 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                       [param_1 + 0xda]);
  }
  iVar11 = 0;
  piVar12 = (int *)(param_1 + 0xa1d20);
  do {
    iVar1 = HcGetMaxStaNum(param_1);
    if (iVar1 <= iVar11) {
      DisplayTxAgg(param_1);
      return 1;
    }
    if ((*piVar12 == 0x20001) && (piVar12[0x3f] == 2)) {
      if ((2 < DebugLevel) &&
         (printk("\n%02x:%02x:%02x:%02x:%02x:%02x - ",(char)piVar12[0x3b],
                 *(undefined1 *)((int)piVar12 + 0xed),*(undefined1 *)((int)piVar12 + 0xee),
                 *(undefined1 *)((int)piVar12 + 0xef),(char)piVar12[0x3c],
                 *(undefined1 *)((int)piVar12 + 0xf1)), 2 < DebugLevel)) {
        printk("%-4d\n",(short)piVar12[0x3e]);
      }
      piVar14 = piVar12 + 0x47a;
      iVar1 = 0xf;
      piVar9 = piVar12 + 0x35a;
      do {
        piVar13 = piVar9 + -1;
        iVar7 = *piVar13;
        if (iVar7 == 0) {
          iVar4 = piVar9[0x1f];
          if (iVar4 != 0) {
            if (2 < DebugLevel) {
              iVar10 = piVar9[0xf];
              uVar2 = 0;
              goto LAB_0002eff0;
            }
            goto LAB_0002ef24;
          }
        }
        else {
          if (2 < DebugLevel) {
            iVar10 = piVar9[0xf];
            uVar2 = __aeabi_uidiv(iVar10 * 100,iVar7);
            iVar4 = piVar9[0x1f];
LAB_0002eff0:
            printk("MCS[%02d]: Expected %u, Successful %u (%d%%), Failed %u\n",iVar1,iVar7,iVar10,
                   uVar2,iVar4);
          }
LAB_0002ef24:
          iVar7 = 0xf;
          piVar9 = piVar14;
          do {
            piVar9 = piVar9 + -1;
            iVar4 = *piVar9;
            if ((iVar4 != 0) && (2 < DebugLevel)) {
              uVar2 = __aeabi_uidiv(iVar4 * 100,*piVar13);
              printk("\t\t\tAutoMCS[%02d]: %u (%d%%)\n",iVar7,iVar4,uVar2);
            }
            bVar15 = iVar7 != 0;
            iVar7 = iVar7 + -1;
          } while (bVar15);
        }
        iVar1 = iVar1 + -1;
        piVar14 = piVar14 + -0x10;
        piVar9 = piVar13;
      } while (iVar1 != -1);
    }
    iVar11 = iVar11 + 1;
    piVar12 = piVar12 + 0x530;
  } while( true );
}

