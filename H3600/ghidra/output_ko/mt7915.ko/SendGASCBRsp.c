// module: mt7915.ko
// function: SendGASCBRsp @ 0x22b4b8
// size: 1384 bytes
//

void SendGASCBRsp(int param_1,byte *param_2)

{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  char *pcVar10;
  int *piVar11;
  int *piVar12;
  byte *__s2;
  int *piVar13;
  undefined1 uStack_39;
  int local_38;
  uint local_34;
  undefined4 local_2e;
  undefined2 local_2a;
  
  bVar1 = *param_2;
  iVar9 = (uint)bVar1 * 0x5834;
  iVar7 = param_1 + iVar9;
  local_2e = 0xffffffff;
  local_2a = 0xffff;
  local_34 = 0;
  os_alloc_mem(0,&local_38,*(int *)(&_LC167 + iVar7) + 0x26);
  if (local_38 == 0) {
    if (-1 < DebugLevel) {
      printk("%s Not available memory\n","SendGASCBRsp");
      return;
    }
    return;
  }
  if (*(int *)(&_LC167 + iVar7) != -0x26) {
    __memzero();
  }
  if (2 < DebugLevel) {
    printk(&_LC1,"SendGASCBRsp");
  }
  iVar7 = (uint)bVar1 * 0x5834;
  pcVar10 = "RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar7 + 0x24;
  _raw_spin_lock_bh(pcVar10);
  piVar11 = *(int **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar7 + 0x1c);
  if ((int *)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar9 + 0x1c) != piVar11) {
    __s2 = param_2 + 1;
    do {
      iVar6 = memcmp((char *)((int)piVar11 + 0xd),__s2,6);
      iVar7 = local_38;
      if (iVar6 == 0) {
        piVar13 = piVar11 + 0x42;
        piVar12 = (int *)*piVar13;
        if (piVar12 == piVar13) goto LAB_0022b5fc;
        cVar2 = (char)piVar12[2];
        goto joined_r0x0022b5dc;
      }
      piVar11 = (int *)*piVar11;
    } while ((int *)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar9 + 0x1c) !=
             piVar11);
  }
  uVar8 = 0;
LAB_0022b600:
  if (2 < DebugLevel) {
    printk("%s bPeerFound =%d bGASQueryRspFragFound=%d\n","SendGASCBRsp",uVar8,0);
  }
LAB_0022b60c:
  _raw_spin_unlock_bh(pcVar10);
  os_free_mem(local_38);
  return;
joined_r0x0022b5dc:
  if (*(char *)((int)piVar11 + 0xfa) == cVar2) goto LAB_0022b634;
  piVar12 = (int *)*piVar12;
  if (piVar12 == piVar13) goto LAB_0022b5fc;
  cVar2 = (char)piVar12[2];
  goto joined_r0x0022b5dc;
LAB_0022b5fc:
  uVar8 = 1;
  goto LAB_0022b600;
LAB_0022b634:
  *(char *)((int)piVar11 + 0xfa) = *(char *)((int)piVar11 + 0xfa) + '\x01';
  if ((piVar12 != (int *)0x0) && (piVar12[3] != 0)) {
    iVar9 = MacTableLookup(param_1,(char *)((int)piVar11 + 0xd));
    if (iVar9 == 0) {
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
    *(undefined1 *)(iVar7 + 0x19) = 0xd;
    *(undefined1 *)(iVar7 + 0x18) = 4;
    iVar9 = DebugLevel;
    if (*(short *)(param_2 + 7) == 6) {
      *(byte *)(iVar7 + 0x1a) = param_2[9];
      *(undefined2 *)(iVar7 + 0x1b) = *(undefined2 *)(param_2 + 0xb);
      *(byte *)(iVar7 + 0x1d) = *(byte *)(piVar12 + 2) & 0x7f;
      if (2 < iVar9) {
        printk("GASRspFragID = %d\n");
      }
      *(undefined1 *)(iVar7 + 0x1e) = 0;
      *(undefined1 *)(iVar7 + 0x1f) = 0;
      *(undefined1 *)(iVar7 + 0x22) = 0;
      *(undefined1 *)(iVar7 + 0x20) = 0x6c;
      *(undefined1 *)(iVar7 + 0x21) = 2;
      *(byte *)(iVar7 + 0x23) = param_2[10];
      if (*(short *)(param_2 + 0xb) == 0) {
        local_34 = (uint)*(ushort *)((int)piVar12 + 10);
        *(ushort *)(iVar7 + 0x24) = *(ushort *)((int)piVar12 + 10);
        memmove((void *)(iVar7 + 0x26),(void *)piVar12[3],(uint)*(ushort *)((int)piVar12 + 10));
        iVar9 = *(ushort *)((int)piVar12 + 10) + 0x26;
      }
      else {
        iVar9 = 0x26;
        *(undefined2 *)(iVar7 + 0x24) = (undefined2)local_34;
      }
      if (*piVar11 != 0) {
        *(int *)(*piVar11 + 4) = piVar11[1];
      }
      if ((int *)piVar11[1] != (int *)0x0) {
        *(int *)piVar11[1] = *piVar11;
      }
      *piVar11 = 0;
      piVar11[1] = 0;
      piVar5 = *(int **)piVar11[0x42];
      piVar12 = (int *)piVar11[0x42];
      while (piVar4 = piVar5, piVar13 != piVar12) {
        if (piVar4 != (int *)0x0) {
          piVar4[1] = piVar12[1];
        }
        if ((int *)piVar12[1] != (int *)0x0) {
          *(int *)piVar12[1] = *piVar12;
        }
        *piVar12 = 0;
        piVar12[1] = 0;
        os_free_mem(piVar12[3]);
        os_free_mem(piVar12);
        piVar11[0x40] = piVar11[0x40] + 2;
        piVar5 = (int *)*piVar4;
        piVar12 = piVar4;
      }
      piVar11[0x42] = (int)piVar13;
      piVar11[0x43] = (int)piVar13;
      _raw_spin_unlock_bh(pcVar10);
      if ((char)piVar11[0x14] != '\0') {
        RTMPCancelTimer(piVar11 + 7,&uStack_39);
        *(char *)(piVar11 + 0x14) = '\0';
      }
      if ((char)piVar11[0x22] != '\0') {
        RTMPCancelTimer(piVar11 + 0x15,&uStack_39);
        *(char *)(piVar11 + 0x22) = '\0';
      }
      RTMPReleaseTimer(piVar11 + 7,&uStack_39);
      piVar11[0x40] = piVar11[0x40] + 1;
      RTMPReleaseTimer(piVar11 + 0x15,&uStack_39);
      os_free_mem(piVar11);
    }
    else if (*(short *)(param_2 + 7) == 7) {
      *(byte *)(iVar7 + 0x1a) = param_2[9];
      *(undefined2 *)(iVar7 + 0x1b) = *(undefined2 *)(param_2 + 0xb);
      *(byte *)(iVar7 + 0x1d) = *(byte *)(piVar12 + 2) | 0x80;
      if (iVar9 < 3) {
        *(undefined1 *)(iVar7 + 0x1e) = 0;
        *(undefined1 *)(iVar7 + 0x1f) = 0;
        *(undefined1 *)(iVar7 + 0x22) = 0;
        *(undefined1 *)(iVar7 + 0x20) = 0x6c;
        *(undefined1 *)(iVar7 + 0x21) = 2;
        *(byte *)(iVar7 + 0x23) = param_2[10];
      }
      else {
        printk("GASRspFragID = %d\n");
        *(undefined1 *)(iVar7 + 0x1e) = 0;
        *(undefined1 *)(iVar7 + 0x1f) = 0;
        *(undefined1 *)(iVar7 + 0x22) = 0;
        *(undefined1 *)(iVar7 + 0x20) = 0x6c;
        *(undefined1 *)(iVar7 + 0x21) = 2;
        *(byte *)(iVar7 + 0x23) = param_2[10];
      }
      local_34 = (uint)*(ushort *)((int)piVar12 + 10);
      *(ushort *)(iVar7 + 0x24) = *(ushort *)((int)piVar12 + 10);
      memmove((void *)(iVar7 + 0x26),(void *)piVar12[3],(uint)*(ushort *)((int)piVar12 + 10));
      uVar3 = *(ushort *)((int)piVar12 + 10);
      GASSetPeerCurrentState(param_1,param_2,4);
      iVar9 = uVar3 + 0x26;
      _raw_spin_unlock_bh(pcVar10);
    }
    else {
      iVar9 = 0x1a;
    }
    MiniportMMRequest(param_1,0,local_38,iVar9);
    os_free_mem(local_38);
    return;
  }
  if (2 < DebugLevel) {
    printk("%s GASQueryRspFrag->FragQueryRsp is Null\n","SendGASCBRsp");
  }
  goto LAB_0022b60c;
}

