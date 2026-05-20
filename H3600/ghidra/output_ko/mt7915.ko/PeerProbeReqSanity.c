// module: mt7915.ko
// function: PeerProbeReqSanity @ 0x1124c4
// size: 1372 bytes
//

undefined4 PeerProbeReqSanity(int param_1,int param_2,int param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  byte bVar3;
  undefined1 uVar4;
  void *pvVar5;
  char *__s2;
  uint uVar6;
  void *pvVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  undefined4 *__src;
  int iVar12;
  size_t local_58;
  void *local_54;
  void *local_3c;
  int local_38;
  void *local_34;
  undefined4 local_2e;
  undefined2 local_2a;
  
  __src = (undefined4 *)(param_2 + 10);
  *param_4 = *__src;
  local_3c = (void *)0x0;
  local_38 = 0;
  *(undefined2 *)(param_4 + 1) = *(undefined2 *)(param_2 + 0xe);
  if (*(char *)(param_2 + 0x18) != '\0') {
LAB_00112514:
    if (2 < DebugLevel) {
      printk("%s(): sanity fail - wrong SSID IE\n","PeerProbeReqSanity");
    }
    return 0;
  }
  bVar3 = *(byte *)(param_2 + 0x19);
  if (0x20 < bVar3) goto LAB_00112514;
  pvVar5 = (void *)(param_2 + 0x1a);
  *(byte *)((int)param_4 + 0x26) = bVar3;
  iVar12 = param_2 + 0x18;
  memmove((void *)((int)param_4 + 6),pvVar5,(uint)bVar3);
  local_2e = *(undefined4 *)(param_2 + 4);
  local_2a = *(undefined2 *)(param_2 + 8);
  os_alloc_mem(0,&local_3c,0x200);
  uVar6 = (uint)*(byte *)(param_2 + 0x19);
  bVar3 = *(byte *)(param_2 + 0x18);
  iVar9 = uVar6 + 2;
  if ((int)pvVar5 + uVar6 <= (uint)(param_2 + param_3)) {
    local_54 = (void *)0x1;
    local_58 = 0;
    iVar8 = iVar12;
    do {
      if (bVar3 == 0xbf) {
        if (uVar6 < 0xc) {
          if (1 < DebugLevel) {
            printk("%s() - wrong IE_VHT_CAP. eid_len = %d\n","PeerProbeReqSanity",uVar6);
          }
        }
        else {
          if ((&DAT_0036b920)[param_1] != '\0') {
            *(undefined1 *)((int)param_4 + 0x29) = 1;
          }
          *(byte *)((int)param_4 + 0x31) =
               (byte)(((uint)*(byte *)((int)pvVar5 + 1) << 0x1c) >> 0x1f);
          *(byte *)((int)param_4 + 0x32) =
               (byte)(((uint)*(byte *)((int)pvVar5 + 2) << 0x1d) >> 0x1d);
        }
      }
      else if (bVar3 < 0xc0) {
        if (bVar3 == 0x2d) {
          if (uVar6 < 0x1a) {
            if (1 < DebugLevel) {
              printk("%s() - wrong IE_HT_CAP. eid_len = %d\n","PeerProbeReqSanity",uVar6);
            }
          }
          else if ((&DAT_0036b920)[param_1] != '\0') {
            *(undefined1 *)(param_4 + 10) = 1;
            param_4[0xb] = *(undefined4 *)((int)pvVar5 + 3);
          }
        }
      }
      else if (bVar3 == 0xdd) {
        if ((4 < uVar6) && (iVar1 = memcmp(pvVar5,&WPS_OUI,4), iVar1 == 0)) {
          uVar2 = HcGetBandByChannel(param_1,*(undefined1 *)(param_2 + 0x91f));
          WscCheckPeerDPID(param_1,param_2,pvVar5,uVar6,uVar2);
          if (local_3c == (void *)0x0) {
            if (DebugLevel < 0) {
              local_54 = local_3c;
            }
            else {
              local_54 = local_3c;
              printk("%s: Error!!! pPeerWscIe is empty!\n","PeerProbeReqSanity");
            }
          }
          else if (*(char *)((int)pvVar5 + 4) == '\x10') {
            local_58 = uVar6 - 4;
            memmove(local_3c,(void *)((int)pvVar5 + 4),local_58);
          }
          else {
            uVar10 = (local_58 - 4) + uVar6;
            if (uVar10 < 0x201) {
              memmove((void *)((int)local_3c + local_58),(void *)((int)pvVar5 + 4),uVar6 - 4);
              local_58 = uVar10;
            }
            else {
              local_54 = (void *)0x0;
              if (-1 < DebugLevel) {
                printk("%s: Error!Sum of All PeerWscIeLen = %d (> 512)\n","PeerProbeReqSanity",
                       uVar10);
              }
            }
          }
        }
      }
      else if (bVar3 == 0xff) {
        os_alloc_mem(0,&local_38,0x310);
        if (local_38 == 0) {
          *(undefined1 *)((int)param_4 + 0x33) = 0;
        }
        else {
          __memzero(local_38,0x310);
          parse_he_probe_req_ies(iVar8,local_38);
          uVar6 = *(uint *)(local_38 + 0x240) & 0x10;
          uVar4 = (undefined1)uVar6;
          if (uVar6 != 0) {
            uVar4 = 1;
          }
          *(undefined1 *)((int)param_4 + 0x33) = uVar4;
          os_free_mem();
        }
      }
      pvVar7 = local_3c;
      bVar3 = *(byte *)(iVar12 + iVar9);
      pvVar5 = (void *)(iVar12 + iVar9 + 2);
      uVar6 = (uint)((byte *)(iVar12 + iVar9))[1];
      iVar8 = iVar8 + *(byte *)(iVar8 + 1) + 2;
      iVar9 = iVar9 + uVar6 + 2;
    } while ((int)pvVar5 + uVar6 <= (uint)(param_2 + param_3));
    if (local_3c == (void *)0x0) {
      return 1;
    }
    if (local_58 == 0) {
      uVar6 = 0;
    }
    else {
      uVar6 = (uint)local_54 & 1;
    }
    if (uVar6 == 0) goto LAB_001128e8;
    *(undefined1 *)(param_4 + 0xc) = 1;
    uVar6 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        [param_1 + 0xda];
    if (uVar6 == 0) {
      uVar10 = 0;
      uVar11 = 0;
    }
    else {
      uVar11 = 0;
      __s2 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + param_1 + 0x101;
      uVar10 = 0;
      do {
        iVar9 = memcmp(&local_2e,__s2,6);
        __s2 = __s2 + 0x5834;
        if (iVar9 == 0) {
          if (uVar6 <= uVar11) {
            uVar10 = 0;
            uVar11 = 0;
          }
          goto LAB_00112870;
        }
        uVar11 = uVar10 + 1 & 0xff;
        uVar10 = uVar10 + 1;
      } while (uVar11 < uVar6);
      uVar10 = 0;
      uVar11 = 0;
    }
LAB_00112870:
    if ((*(uint *)(
                  "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                  + uVar10 * 0x5834 + param_1 + 0x2b) & 2) == 0) goto LAB_001128e8;
    iVar9 = local_58 + 0x28;
    local_34 = (void *)0x0;
    os_alloc_mem(0,&local_34,iVar9);
    if (local_34 != (void *)0x0) {
      if (iVar9 != 0) {
        __memzero(local_34,iVar9);
      }
      pvVar5 = local_34;
      if (*(byte *)((int)param_4 + 0x26) < 0x21) {
        memmove(local_34,(void *)((int)param_4 + 6),(uint)*(byte *)((int)param_4 + 0x26));
        memmove((void *)((int)pvVar5 + 0x20),__src,6);
        pvVar7 = local_34;
        *(char *)((int)pvVar5 + 0x27) = (char)local_58;
        *(char *)((int)pvVar5 + 0x26) = (char)(local_58 >> 8);
        memmove((void *)((int)local_34 + 0x28),local_3c,local_58);
        WscSendUPnPMessage(param_1,uVar11,0x12,1,pvVar7,iVar9,0,0,__src,0);
      }
      os_free_mem(local_34);
    }
  }
  pvVar7 = local_3c;
  if (local_3c == (void *)0x0) {
    return 1;
  }
LAB_001128e8:
  os_free_mem(pvVar7);
  return 1;
}

