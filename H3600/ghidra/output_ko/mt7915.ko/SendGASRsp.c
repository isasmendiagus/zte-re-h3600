// module: mt7915.ko
// function: SendGASRsp @ 0x22aad8
// size: 1320 bytes
//

void SendGASRsp(int param_1,byte *param_2)

{
  byte bVar1;
  undefined2 uVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  byte *__s2;
  char *pcVar10;
  undefined1 uStack_39;
  int local_38;
  uint local_34;
  undefined4 local_2e;
  undefined2 local_2a;
  
  bVar1 = *param_2;
  local_2e = 0xffffffff;
  local_2a = 0xffff;
  local_34 = 0;
  if (2 < DebugLevel) {
    printk(&_LC1,"SendGASRsp");
  }
  iVar7 = (uint)bVar1 * 0x5834;
  pcVar10 = "RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar7 + 0x24;
  _raw_spin_lock_bh(pcVar10);
  piVar8 = *(int **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar7 + 0x1c);
  if ((int *)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + (uint)bVar1 * 0x5834 + param_1 + 0x1c)
      != piVar8) {
    __s2 = param_2 + 1;
    do {
      iVar7 = memcmp((char *)((int)piVar8 + 0xd),__s2,6);
      if (iVar7 == 0) {
        _raw_spin_unlock_bh(pcVar10);
        if (param_2[0xe] == 0) {
          iVar7 = 6;
        }
        else {
          iVar7 = 0;
        }
        if (*(short *)(param_2 + 7) == 1) {
          iVar7 = iVar7 + (uint)*(ushort *)(param_2 + 0xf);
        }
        os_alloc_mem(0,&local_38,iVar7 + 0x20);
        if (local_38 == 0) {
          if (-1 < DebugLevel) {
            printk("%s Not available memory\n","SendGASRsp");
          }
          _raw_spin_lock_bh(pcVar10);
          if (*(short *)(param_2 + 7) == 2) {
            piVar9 = (int *)piVar8[0x42];
            piVar4 = (int *)*piVar9;
            while (piVar3 = piVar4, piVar9 != piVar8 + 0x42) {
              if (piVar3 != (int *)0x0) {
                piVar3[1] = piVar9[1];
              }
              if ((int *)piVar9[1] != (int *)0x0) {
                *(int *)piVar9[1] = *piVar9;
              }
              *piVar9 = 0;
              piVar9[1] = 0;
              os_free_mem(piVar9[3]);
              os_free_mem(piVar9);
              piVar4 = (int *)*piVar3;
              piVar9 = piVar3;
            }
          }
          if (*piVar8 != 0) {
            *(int *)(*piVar8 + 4) = piVar8[1];
          }
          if ((int *)piVar8[1] != (int *)0x0) {
            *(int *)piVar8[1] = *piVar8;
          }
          piVar8[0x42] = (int)(piVar8 + 0x42);
          piVar8[0x43] = (int)(piVar8 + 0x42);
          *piVar8 = 0;
          piVar8[1] = 0;
          _raw_spin_unlock_bh(pcVar10);
          GASSetPeerCurrentState(param_1,param_2,2);
          if ((char)piVar8[0x14] != '\0') {
            RTMPCancelTimer(piVar8 + 7,&uStack_39);
            *(char *)(piVar8 + 0x14) = '\0';
          }
          RTMPReleaseTimer(piVar8 + 7,&uStack_39);
          if ((char)piVar8[0x22] != '\0') {
            RTMPCancelTimer(piVar8 + 0x15,&uStack_39);
            *(char *)(piVar8 + 0x22) = '\0';
          }
          RTMPReleaseTimer(piVar8 + 0x15,&uStack_39);
          os_free_mem(piVar8);
          return;
        }
        __memzero(local_38,iVar7 + 0x20);
        iVar7 = local_38;
        iVar5 = MacTableLookup(param_1,(char *)((int)piVar8 + 0xd));
        if (iVar5 == 0) {
          ActHeaderInit(param_1,iVar7,__s2,
                        "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + (uint)*param_2 * 0x5834 + param_1 + 0x101,&local_2e);
        }
        else {
          ActHeaderInit(param_1,iVar7,__s2,
                        "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + (uint)*param_2 * 0x5834 + param_1 + 0x101,
                        "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + (uint)*param_2 * 0x5834 + param_1 + 0x101);
        }
        *(undefined1 *)(iVar7 + 0x19) = 0xb;
        *(undefined1 *)(iVar7 + 0x18) = 4;
        if (*(short *)(param_2 + 7) == 1) {
          *(byte *)(iVar7 + 0x1a) = param_2[9];
          *(undefined2 *)(iVar7 + 0x1b) = *(undefined2 *)(param_2 + 10);
          uVar2 = *(undefined2 *)(param_2 + 0xc);
          *(undefined1 *)(iVar7 + 0x1f) = 0x6c;
          *(undefined1 *)(iVar7 + 0x20) = 2;
          *(undefined2 *)(iVar7 + 0x1d) = uVar2;
          *(undefined1 *)(iVar7 + 0x21) = 0;
          *(byte *)(iVar7 + 0x22) = param_2[0xe];
          local_34 = (uint)*(ushort *)(param_2 + 0xf);
          *(ushort *)(iVar7 + 0x23) = *(ushort *)(param_2 + 0xf);
          uVar6 = 0;
          if (*(ushort *)(param_2 + 0xf) != 0) {
            memmove((void *)(iVar7 + 0x25),param_2 + 0x11,(uint)*(ushort *)(param_2 + 0xf));
            uVar6 = (uint)*(ushort *)(param_2 + 0xf);
          }
          iVar5 = uVar6 + 0x25;
          GASSetPeerCurrentState(param_1,param_2,2);
          _raw_spin_lock_bh(pcVar10);
          if (*piVar8 != 0) {
            *(int *)(*piVar8 + 4) = piVar8[1];
          }
          if ((int *)piVar8[1] != (int *)0x0) {
            *(int *)piVar8[1] = *piVar8;
          }
          *piVar8 = 0;
          piVar8[0x42] = (int)(piVar8 + 0x42);
          piVar8[0x43] = (int)(piVar8 + 0x42);
          piVar8[1] = 0;
          _raw_spin_unlock_bh(pcVar10);
          if ((char)piVar8[0x14] != '\0') {
            RTMPCancelTimer(piVar8 + 7,&uStack_39);
            *(char *)(piVar8 + 0x14) = '\0';
          }
          RTMPReleaseTimer(piVar8 + 7,&uStack_39);
          piVar8[0x40] = piVar8[0x40] + 1;
          if ((char)piVar8[0x22] != '\0') {
            RTMPCancelTimer(piVar8 + 0x15,&uStack_39);
            *(char *)(piVar8 + 0x22) = '\0';
          }
          RTMPReleaseTimer(piVar8 + 0x15,&uStack_39);
          piVar8[0x40] = piVar8[0x40] + 2;
          os_free_mem(piVar8);
        }
        else if (*(short *)(param_2 + 7) == 2) {
          *(byte *)(iVar7 + 0x1a) = param_2[9];
          *(undefined2 *)(iVar7 + 0x1b) = *(undefined2 *)(param_2 + 10);
          uVar2 = *(undefined2 *)(param_2 + 0xc);
          *(undefined1 *)(iVar7 + 0x20) = 2;
          *(undefined1 *)(iVar7 + 0x1f) = 0x6c;
          *(undefined2 *)(iVar7 + 0x1d) = uVar2;
          *(undefined1 *)(iVar7 + 0x21) = 0;
          bVar1 = param_2[0xe];
          *(undefined2 *)(iVar7 + 0x23) = (undefined2)local_34;
          *(byte *)(iVar7 + 0x22) = bVar1;
          GASSetPeerCurrentState(param_1,param_2);
          if ((char)piVar8[0x22] == '\0') {
            iVar5 = 0x25;
            RTMPSetTimer(piVar8 + 0x15,*(ushort *)(iVar7 + 0x1d) + 0x1400);
            *(char *)(piVar8 + 0x22) = '\x01';
          }
          else {
            iVar5 = 0x25;
          }
        }
        else {
          iVar5 = 0x1a;
        }
        MiniportMMRequest(param_1,0,local_38,iVar5);
        os_free_mem(local_38);
        return;
      }
      piVar8 = (int *)*piVar8;
    } while ((int *)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" +
                    (uint)bVar1 * 0x5834 + param_1 + 0x1c) != piVar8);
  }
  _raw_spin_unlock_bh(pcVar10);
  return;
}

