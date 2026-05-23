// module: mt7915.ko
// function: ap_rx_pkt_allowed @ 0x1e94c
// size: 1172 bytes
//

undefined4 ap_rx_pkt_allowed(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  byte bVar7;
  byte *pbVar8;
  void *__s2;
  char *__s2_00;
  byte *pbVar9;
  int iVar10;
  int iVar11;
  char *pcVar12;
  bool bVar13;
  int local_2c;
  
  pbVar8 = *(byte **)(param_3 + 0x1c);
  pbVar9 = *(byte **)(param_3 + 0x10);
  iVar2 = PACInquiry(param_1,*(undefined2 *)(param_3 + 0x4e));
  if ((pbVar8[1] & 3) == 3) {
    if ((iVar2 != 0) ||
       (iVar2 = MacTableLookup(param_1,*(undefined4 *)(param_3 + 0x2c)), iVar2 != 0)) {
      if (*(char *)(iVar2 + 0xe8) != '\0') {
        __s2 = *(void **)(param_3 + 0x34);
        local_2c = 0;
        iVar10 = *(int *)(param_3 + 0x3c);
        iVar3 = memcmp((void *)(iVar2 + 0xec),__s2,6);
        iVar11 = *(int *)(param_3 + 0x38);
        bVar13 = *(short *)(iVar10 + 0xc) == 0x608;
        iVar4 = iVar3;
        if (bVar13) {
          iVar4 = *(int *)(iVar10 + 0x1c);
        }
        pbVar8 = *(byte **)(iVar11 + 0xcc);
        if (bVar13) {
          local_2c = iVar4;
        }
        if (((*pbVar8 & 1) == 0) || (iVar4 = memcmp(pbVar8 + 0xe,&_LANCHOR1,3), iVar4 != 0)) {
          iVar4 = memcmp(__s2,&br0Addr,6);
          if (iVar4 == 0) {
            pcVar12 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      + param_1 + 0x101;
            iVar4 = 0;
            while( true ) {
              __s2_00 = pcVar12;
              iVar10 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
              iVar11 = iVar4 + 1;
              if (iVar10 <= iVar4) break;
              pcVar12 = __s2_00 + 0x5834;
              iVar4 = iVar11;
              if (((__s2_00[0x3f3c] & 0x40U) != 0) &&
                 (iVar10 = memcmp(*(void **)(param_3 + 0x28),__s2_00,6), iVar10 == 0)) {
                if (DebugLevel < 2) {
                  return 0;
                }
                printk("recv data pkt from own, drop!!!!\n");
                return 0;
              }
            }
            __s2 = *(void **)(param_3 + 0x34);
            bVar13 = false;
          }
          else {
            bVar13 = false;
          }
        }
        else {
          if ((0x19 < *(uint *)(iVar11 + 100)) &&
             (cVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      [param_1 + 0xda], cVar1 != '\0')) {
            pcVar12 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      + param_1 + 0x101;
            do {
              iVar4 = memcmp(pcVar12,pbVar8 + 0x14,6);
              pcVar12 = pcVar12 + 0x5834;
              if (iVar4 == 0) {
                if (DebugLevel < 2) {
                  return 0;
                }
                printk("recv pkt from own, drop!!!\n");
                return 0;
              }
            } while (pcVar12 !=
                     "printing range e2p value\n" + (uint)(byte)(cVar1 - 1) * 0x5834 + param_1 + 0xd
                    );
          }
          bVar13 = true;
        }
        if (iVar3 != 0) {
          piVar5 = (int *)MacTableLookup(param_1,__s2);
          if (piVar5 != (int *)0x0) {
            if (*piVar5 != 0x20001) {
              bVar13 = false;
            }
            if (bVar13) {
              if ((*(ushort *)(piVar5 + 0x38) < 0x120) && (piVar5[0x3f] == 2)) {
                ZTE_Notify_Node_AD(0,piVar5);
              }
              __ZTE_STA_Assoc_Process(param_1,0x11,0,0,3,0,piVar5,"ap_rx_pkt_allowed",0xd34);
              mac_entry_delete(param_1,piVar5);
            }
          }
          __s2 = *(void **)(param_3 + 0x34);
        }
        a4_proxy_update(param_1,*(undefined1 *)(iVar2 + 0xe4),*(undefined2 *)(iVar2 + 0xe0),__s2,
                        local_2c);
LAB_0001ebc0:
        *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 0x800;
        iVar2 = *(int *)(iVar2 + 0xf4);
        if (iVar2 != 0) {
          *(uint *)(iVar2 + 0x43e8) = (uint)*(ushort *)(param_3 + 0x48) + *(int *)(iVar2 + 0x43e8);
          *(int *)(iVar2 + 0x43e4) = *(int *)(iVar2 + 0x43e4) + 1;
          return 0x1e;
        }
        return 0x1e;
      }
      if ((*(char *)(iVar2 + 0xea) != '\0') &&
         ((*(int *)(iVar2 + 8) == 0 || (*(char *)(*(int *)(iVar2 + 8) + 0x3f59) != '\0'))))
      goto LAB_0001ebc0;
    }
    if (2 < DebugLevel) {
      printk("%s[band%d]WDS packet dropped due to entry not valid!\n","ap_rx_pkt_allowed",
             *(undefined1 *)(param_3 + 0x4c));
    }
  }
  else if (((iVar2 != 0 && (pbVar8[1] & 3) == 1) &&
           ((((*pbVar8 & 0x70) == 0x40 || (*(char *)(iVar2 + 0xe8) != '\x01')) &&
            (iVar4 = ap_chk_cl2_cl3_err(param_1,param_3), iVar4 == 0)))) &&
          ((&DAT_003687e5)[param_1] != '\x01')) {
    if ((((pbVar8[1] & 2) == 0) && ((*pbVar9 & 0x10) != 0)) &&
       (iVar4 = *(int *)(iVar2 + 0xf4), iVar4 != 0)) {
      *(uint *)(iVar4 + 0x43e8) = (uint)*(ushort *)(param_3 + 0x48) + *(int *)(iVar4 + 0x43e8);
      *(int *)(iVar4 + 0x43e4) = *(int *)(iVar4 + 0x43e4) + 1;
    }
    if (**(byte **)(param_3 + 0x30) == 0xff) {
      bVar7 = 0;
    }
    else {
      bVar7 = **(byte **)(param_3 + 0x30) & 1;
    }
    if (bVar7 != 0) {
      uVar6 = *(uint *)(param_1 + 0xa39c50);
      *(uint *)(param_1 + 0xa39c50) = uVar6 + 1;
      *(uint *)(param_1 + 0xa39c54) = *(int *)(param_1 + 0xa39c54) + (uint)(0xfffffffe < uVar6);
    }
    *(uint *)(param_3 + 0x44) = *(uint *)(param_3 + 0x44) | 0x200;
    if (*(short *)(iVar2 + 0xe0) == *(short *)(param_3 + 0x4e)) {
      return 0x18;
    }
    printk(&_LC37,0xe11);
    dump_stack();
    return 0x18;
  }
  return 0;
}

