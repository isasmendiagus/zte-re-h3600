// module: mt7915.ko
// function: Set_AP_WscGetConf_Proc @ 0x31e38
// size: 1240 bytes
//

undefined4 Set_AP_WscGetConf_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char cVar6;
  int *piVar7;
  int iVar8;
  uint uVar9;
  uint *puVar10;
  undefined1 *puVar11;
  undefined4 local_2e;
  undefined2 local_2a;
  
  iVar1 = DebugLevel;
  uVar9 = (uint)*(byte *)(*param_1 + 0x3c);
  if (*(int *)(*param_1 + 0x38) == 0x400) {
    if ((char)param_1[uVar9 * 0x84dec + 0x1603a3] == '\0') {
      if (DebugLevel < 3) {
        return 0;
      }
      printk("IF(apcli%d) Set_AP_WscGetConf_Proc:: ApCli is disabled.\n",uVar9);
      return 0;
    }
    uVar9 = uVar9 & 0xcf;
    iVar8 = 1;
    param_1[0x29f46d] = 1;
    piVar7 = param_1 + uVar9 * 0x84dec + 0xdbb8f;
    if (2 < iVar1) {
      printk("IF(apcli%d) Set_AP_WscGetConf_Proc:: This command is from apcli interface now.\n",
             uVar9);
    }
  }
  else {
    iVar8 = 0;
    param_1[0x29f46d] = 0;
    piVar7 = param_1 + uVar9 * 0x160d + 0xae14b;
    if (2 < iVar1) {
      printk("IF(ra%d) Set_AP_WscGetConf_Proc:: This command is from ra interface now.\n",uVar9);
    }
  }
  __memzero(&local_2e,6);
  uVar4 = os_str_tol(param_2,0,10);
  iVar2 = DebugLevel;
  iVar1 = piVar7[2];
  if ((*piVar7 == 0) || (((char)piVar7[0xacc] == '\0' && (*(char *)((int)piVar7 + 0x2b31) != '\0')))
     ) {
    *(undefined1 *)(piVar7 + 0xa79) = 0;
    if (iVar2 < 3) {
      return 0;
    }
    printk("Set_WscGetConf_Proc: WPS is disabled.\n");
    return 0;
  }
  _WscStop(param_1,iVar8,piVar7,0);
  *(undefined1 *)(piVar7 + 0x106) = 1;
  cVar6 = '\0';
  if (piVar7[1] != 1) {
    cVar6 = '\x04';
  }
  puVar11 = (undefined1 *)((int)piVar7 + 0x357);
  WscInitRegistrarPair(param_1,piVar7,uVar9);
  do {
    uVar3 = RandomByte(param_1);
    puVar11 = puVar11 + 1;
    *puVar11 = uVar3;
  } while (puVar11 != (undefined1 *)((int)piVar7 + 0x417));
  if (iVar8 == 0) {
    iVar8 = uVar9 * 0x5834;
    WscBuildBeaconIE(param_1,(char)iVar1,1,cVar6,*(undefined2 *)((int)piVar7 + 10),uVar9,0,0,0);
    WscBuildProbeRespIE(param_1,3,(char)iVar1,1,cVar6,*(undefined2 *)((int)piVar7 + 10),uVar9,0,0,0)
    ;
    UpdateBeaconHandler(param_1,(char *)((int)param_1 +
                                        (int)(
                                             "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                             + iVar8 + 0xe0)),2);
    puVar10 = (uint *)((int)param_1 +
                      (int)(
                           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           + iVar8 + 0x101));
    local_2e = *puVar10;
    local_2a = *(undefined2 *)
                ((int)param_1 +
                (int)(
                     "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                     + iVar8 + 0x105));
    RTMPSetTimer(piVar7 + 0x717,120000);
    *(undefined1 *)((int)piVar7 + 0x1c5b) = 1;
    piVar7[3] = 3;
    *(undefined1 *)(piVar7 + 0xa79) = 1;
    *(undefined1 *)(piVar7 + 0xaf8) = 0;
    if (cVar6 == '\0') {
      WscAssignEntryMAC(param_1,piVar7);
      WscSendUPnPConfReqMsg
                (param_1,(uint)*(byte *)(piVar7 + 0x715),
                 param_1 + (uint)*(byte *)(piVar7 + 0x715) * 0x160d + 0xaecac,puVar10,3,0,0);
    }
    else {
      _raw_spin_lock_bh(piVar7 + 0xb00);
      WscClearPeerList(piVar7 + 0xb01);
      _raw_spin_unlock_bh(piVar7 + 0xb00);
    }
  }
  else {
    uVar3 = *(undefined1 *)((int)param_1 + uVar9 * 0x2137b0 + 0x580e8d);
    *(undefined1 *)((int)param_1 + uVar9 * 0x2137b0 + 0x580e8d) = 0;
    ApCliIfDown(param_1);
    *(undefined1 *)((int)param_1 + uVar9 * 0x2137b0 + 0x580e8d) = uVar3;
    if (cVar6 == '\0') {
      memmove((void *)((int)piVar7 + 0x82),(void *)((int)param_1 + uVar9 * 0x2137b0 + 0x36db73),6);
      piVar7[4] = 2;
      local_2e = *(uint *)((int)param_1 + uVar9 * 0x2137b0 + 0x36db73);
      local_2a = *(undefined2 *)((int)param_1 + uVar9 * 0x2137b0 + 0x36db77);
    }
    else {
      piVar7[10] = 0;
      __memzero(piVar7 + 10,0x24);
      *(undefined1 *)(piVar7 + 0x13) = 0;
      WscPushPBCAction(param_1,piVar7);
      local_2e = *(uint *)((int)param_1 + uVar9 * 0x2137b0 + 0x36db73);
      local_2a = *(undefined2 *)((int)param_1 + uVar9 * 0x2137b0 + 0x36db77);
      if (cVar6 == '\x04') {
        *(undefined1 *)(piVar7 + 0xaf8) = 0;
        goto LAB_00032214;
      }
    }
    RTMPSetTimer(piVar7 + 0x717,120000);
    *(undefined1 *)((int)piVar7 + 0x1c5b) = 1;
    piVar7[3] = 3;
    *(undefined1 *)(piVar7 + 0xa79) = 1;
    *(undefined1 *)(piVar7 + 0xaf8) = 0;
  }
LAB_00032214:
  uVar5 = HcGetBandByWdev(piVar7[0xa7b]);
  RTMPSetLED(param_1,8,uVar5);
  if (DebugLevel < 3) {
    return 1;
  }
  printk("IF(%02x:%02x:%02x:%02x:%02x:%02x) Set_WscGetConf_Proc trigger WSC state machine, wscGetConfMode=%d\n"
         ,local_2e & 0xff,local_2e._1_1_,local_2e._2_1_,local_2e >> 0x18,(undefined1)local_2a,
         local_2a._1_1_,uVar4);
  return 1;
}

