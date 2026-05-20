// module: mt7915.ko
// function: bss_update_offload_bcn @ 0x1c3698
// size: 1536 bytes
//

void bss_update_offload_bcn(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  short sVar7;
  char *pcVar8;
  uint uVar9;
  int iVar10;
  short sVar11;
  int local_b0;
  int local_ac;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined2 local_78;
  undefined2 local_76;
  uint local_74;
  undefined2 local_70 [38];
  
  iVar4 = *(int *)(param_2 + 0x108);
  local_9c = 0;
  local_98 = 0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  local_94 = 0;
  local_90 = 0;
  local_8c = 0;
  local_88 = 0;
  memset(&local_78,0,0x50);
  local_84 = 0;
  local_80 = 0;
  local_7c = 0;
  if (iVar4 == 0) {
    if (DebugLevel < 2) {
      return;
    }
    printk("%s, wdev bss_info is not ready\n","bss_update_offload_bcn");
    return;
  }
  if (2 < DebugLevel) {
    printk("%s, wdev(%d) BCN Len = %d + %d\n","bss_update_offload_bcn",*(undefined1 *)(iVar4 + 0xc),
           *(undefined1 *)(iVar1 + 2),*(undefined2 *)(iVar4 + 0x958));
  }
  os_zero_mem(&local_9c,8);
  iVar5 = *(int *)(param_2 + 0x108);
  local_9c._0_2_ = 0xf;
  local_9c._2_2_ = 8;
  local_98._0_2_ = (ushort)*(byte *)(iVar4 + 0x950) << 8;
  if (iVar5 == 0) {
    local_b0 = 0;
    local_ac = 0;
  }
  else {
    if (*(char *)(iVar5 + 0x944) == '\0') {
      local_b0 = 0;
    }
    else {
      local_94 = 0x80000;
      local_90 = CONCAT31(local_90._1_3_,*(char *)(iVar5 + 0x944));
      if (DebugLevel < 3) {
        local_9c._2_2_ = 0x10;
      }
      else {
        printk("%s, BSS(%d), CsaCount = %d\n","bss_update_offload_bcn_csa",
               *(undefined1 *)(param_2 + 0xd));
        iVar5 = *(int *)(param_2 + 0x108);
        local_9c._2_2_ = local_9c._2_2_ + 8;
      }
      local_98._2_2_ = local_98._2_2_ + 1;
      local_b0 = 8;
    }
    if ((iVar5 == 0 || param_2 == -0xb0) || (*(short *)(iVar5 + 0x98a) == 0)) {
      local_ac = 0;
    }
    else {
      local_8c = 0x80001;
      local_88 = CONCAT31(local_88._1_3_,*(undefined1 *)(param_2 + 0xb8));
      if (2 < DebugLevel) {
        printk("%s, BSS(%d), BccCount = %d\n","bss_update_offload_bcn_bcc",
               *(undefined1 *)(param_2 + 0xd));
      }
      local_ac = 8;
      local_9c._2_2_ = local_9c._2_2_ + 8;
      local_98._2_2_ = local_98._2_2_ + 1;
    }
  }
  iVar5 = 0;
  if (*(int *)(param_1 + (*(byte *)(param_2 + 0x106) + 0xd9e3a) * 4) != 0) {
    local_78 = 2;
    local_76 = 0x50;
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        [param_1 + 0xda] != '\0') {
      uVar9 = 0;
      pcVar8 = "vow_watf_q_lv3: %d\n" + param_1 + 0x10;
      do {
        uVar2 = HcGetBandByWdev(pcVar8 + -0x980);
        if (*(byte *)(param_2 + 0x106) == uVar2) {
          if (2 < DebugLevel) {
            printk("%s, BSS(%d), IE Offset = %d\n","bss_update_offload_bcn_mbssid",uVar9,
                   *(undefined2 *)pcVar8);
          }
          local_70[uVar9] = *(undefined2 *)pcVar8;
        }
        puVar6 = (uint *)(pcVar8 + 0x36e4);
        pcVar8 = pcVar8 + 0x5834;
        if ((*(uint *)(param_1 + (uVar2 + 0xd9e3a) * 4) & 1 << (*puVar6 & 0xff)) != 0) {
          local_74 = local_74 | 1 << (uVar9 & 0xff);
        }
        uVar9 = uVar9 + 1;
      } while ((int)uVar9 <
               (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                [param_1 + 0xda]);
    }
    iVar5 = 0x50;
    local_9c._2_2_ = local_9c._2_2_ + 0x50;
    local_98._2_2_ = local_98._2_2_ + 1;
  }
  iVar10 = *(int *)(param_2 + 0x108);
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar10 == 0) {
    if (1 < DebugLevel) {
      printk("%s, wdev bss_info is not ready\n","bss_update_offload_bcn_content");
    }
LAB_001c3928:
    sVar11 = 0;
  }
  else {
    if ((*(char *)(iVar10 + 0x950) != '\x01') || (*(int *)(iVar10 + 0x954) == 0)) goto LAB_001c3928;
    local_80 = *(undefined4 *)(iVar10 + 0x980);
    sVar11 = (ushort)*(byte *)(iVar3 + 2) + *(short *)(iVar10 + 0x958) + 0xc;
    local_84 = CONCAT22(sVar11,3);
    sVar7 = *(short *)(iVar10 + 0x958) + (ushort)*(byte *)(iVar3 + 2);
    local_7c = CONCAT22(sVar7,*(undefined2 *)(iVar10 + 0x98a));
    if (DebugLevel < 3) {
      if (sVar11 == 0) goto LAB_001c3934;
LAB_001c3b24:
      local_9c._2_2_ = sVar11 + local_9c._2_2_;
      local_98._2_2_ = local_98._2_2_ + 1;
    }
    else {
      printk("%s, BSS(%d), BcnLength = %d, IE offset(TIM/CSA/BCC) = %d/%d/%d\n",
             "bss_update_offload_bcn_content",*(undefined1 *)(param_2 + 0xd),sVar7,
             *(undefined2 *)(iVar10 + 0x980),*(undefined2 *)(iVar10 + 0x982),
             *(undefined2 *)(iVar10 + 0x98a));
      if (sVar11 != 0) goto LAB_001c3b24;
    }
  }
  if (2 < DebugLevel) {
    printk("  BcnEn %d, FeuEn %d/%d/%d/%d, Len = %d, SubElmNum = %d\n",
           *(undefined1 *)(iVar4 + 0x950),local_b0,local_ac,iVar5,sVar11,local_9c._2_2_,
           local_98._2_2_);
  }
LAB_001c3934:
  AndesAppendCmdMsg(param_3,&local_9c,8);
  if (local_b0 != 0) {
    hex_dump_with_cat_and_lvl(&_LC38,&local_94,8,8,1,4);
    AndesAppendCmdMsg(param_3,&local_94,8);
  }
  if (local_ac != 0) {
    hex_dump_with_cat_and_lvl(&_LC39,&local_8c,8,8,1,4);
    AndesAppendCmdMsg(param_3,&local_8c,8);
  }
  if (iVar5 != 0) {
    hex_dump_with_cat_and_lvl("MBSS:",&local_78,0x50,8,1,4);
    AndesAppendCmdMsg(param_3,&local_78,0x50);
  }
  if (sVar11 != 0) {
    hex_dump_with_cat_and_lvl("BCN_CONT:",&local_84,0xc,8,1,4);
    AndesAppendCmdMsg(param_3,&local_84,0xc);
    hex_dump_with_cat_and_lvl
              ("BCN_PKT:",*(undefined4 *)(*(int *)(iVar4 + 0x954) + 0xcc),
               (uint)*(byte *)(iVar1 + 2) + (uint)*(ushort *)(iVar4 + 0x958),8,1,4);
    AndesAppendCmdMsg(param_3,*(undefined4 *)(*(int *)(iVar4 + 0x954) + 0xcc),
                      (uint)*(byte *)(iVar1 + 2) + (uint)*(ushort *)(iVar4 + 0x958));
  }
  return;
}

