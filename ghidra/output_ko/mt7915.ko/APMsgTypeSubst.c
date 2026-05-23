// module: mt7915.ko
// function: APMsgTypeSubst @ 0x176b8
// size: 780 bytes
//

uint APMsgTypeSubst(int param_1,byte *param_2,undefined4 *param_3,uint *param_4)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  
  bVar1 = *param_2;
  uVar7 = bVar1 & 0xc;
  if ((param_2[1] & 3) == 3) {
    iVar8 = 0x1e;
  }
  else {
    iVar8 = 0x18;
  }
  if (uVar7 != 8) {
    if ((bVar1 & 0xc) != 0) {
      return 0;
    }
    switch(bVar1 >> 4) {
    case 0:
      uVar7 = 1;
      *param_3 = 1;
      *param_4 = 4;
      break;
    case 2:
      uVar7 = 1;
      *param_3 = 1;
      *param_4 = 6;
      break;
    case 4:
      uVar7 = 1;
      *param_3 = 4;
      *param_4 = 4;
      break;
    case 5:
      *param_3 = 4;
      uVar7 = 1;
      *param_4 = 5;
      break;
    case 8:
      *param_3 = 4;
      uVar7 = 1;
      *param_4 = 6;
      break;
    case 10:
      uVar7 = 1;
      *param_3 = 1;
      *param_4 = 3;
      break;
    case 0xb:
      sVar2 = *(short *)(param_2 + 0x1a);
      sVar3 = *(short *)(param_2 + 0x18);
      *param_3 = 2;
      if ((sVar2 == 1) || (sVar3 == 3 && sVar2 == 2)) {
        uVar7 = 1;
        *param_4 = 6;
      }
      else if (sVar2 == 3) {
        uVar7 = 1;
        *param_4 = 7;
      }
      else {
        if (DebugLevel < 3) {
          return 0;
        }
        printk("wrong AUTH seq=%d Octet=%02x %02x %02x %02x %02x %02x %02x %02x\n",sVar2,
               param_2[0x18],param_2[0x19],param_2[0x1a],param_2[0x1b],param_2[0x1c],param_2[0x1d],
               param_2[0x1e],param_2[0x1f]);
      }
      break;
    case 0xc:
      *param_3 = 2;
      uVar7 = 1;
      *param_4 = 4;
      break;
    case 0xd:
    case 0xe:
      *param_3 = 9;
      uVar6 = param_2[0x18] & 0x7f;
      if (uVar6 < 0x17) {
        if ((param_2[1] & 0x80) != 0) {
          uVar6 = param_2[0x1c] & 0x7f;
        }
        uVar7 = 1;
        *param_4 = uVar6;
      }
      else {
        uVar7 = 1;
        *param_4 = 0x1f;
      }
    }
    return uVar7;
  }
  piVar4 = (int *)MacTableLookup(param_1,param_2 + 10);
  if ((piVar4 != (int *)0x0) &&
     ((uVar7 = (uint)*(byte *)(piVar4 + 0x39), (char)piVar4[0x349] != '\0' ||
      ((*(uint *)(
                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + uVar7 * 0x5834 + param_1 + 0x10c) & 7) != 0)))) {
    iVar5 = memcmp("%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n" +
                   uVar7 * 0x5834 + param_1 + 0x31,piVar4 + 0x3b,6);
    if (((iVar5 == 0) ||
        (iVar5 = memcmp("%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"
                        + uVar7 * 0x5834 + param_1 + 0x31,&ZERO_MAC_ADDR,6), iVar5 == 0)) &&
       ((*piVar4 == 0x20001 &&
        (*(int *)(
                 "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                 + uVar7 * 0x5834 + param_1 + 0x2b) != 0)))) {
      *param_3 = 0x11;
      uVar7 = WscMsgTypeSubst(param_2[iVar8 + 9],param_2[iVar8 + 0xc],param_4);
      if (uVar7 != 0) {
        return uVar7;
      }
    }
  }
  *param_3 = 0x17;
  uVar7 = WpaMsgTypeSubst(param_2[iVar8 + 9],param_4);
  return uVar7;
}

