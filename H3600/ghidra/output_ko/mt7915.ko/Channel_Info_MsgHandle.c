// module: mt7915.ko
// function: Channel_Info_MsgHandle @ 0x37194
// size: 924 bytes
//

undefined4 Channel_Info_MsgHandle(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  char *pcVar4;
  undefined1 *puVar5;
  byte *pbVar6;
  undefined1 *puVar7;
  int iVar8;
  byte *pbVar9;
  char *pcVar10;
  char *pcVar11;
  char *pcVar12;
  uint local_d8;
  char *local_d4;
  char local_cc;
  undefined4 local_cb;
  undefined4 local_c7;
  undefined4 local_c3;
  undefined4 local_bf;
  byte local_a4 [5];
  char local_9f [5];
  byte local_9a [6];
  uint local_94;
  undefined1 uStack_68;
  undefined1 local_67 [67];
  
  iVar8 = *(int *)(param_3 + 0x3c);
  iVar1 = param_1;
  if (*(int *)(param_3 + 0x38) == 0x200) {
    iVar1 = iVar8 * 0x5834 + param_1;
  }
  pcVar4 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + iVar1 + 0xe0;
  iVar1 = get_scan_ctrl_by_wdev(param_1,pcVar4);
  if (3 < DebugLevel) {
    printk("[%d][%s] : Ioctl : %d !!\n",0x1d3f,"Channel_Info_MsgHandle",iVar8);
  }
  if (*(short *)(param_2 + 0x14) == 0xa4) {
    uVar3 = *(uint *)(((uint)&local_d8 & 0xffffe000) + 8);
    if (*(uint *)(param_2 + 0x10) < 0xffffff5c && *(uint *)(param_2 + 0x10) + 0xa4 <= uVar3) {
      uVar3 = 0;
    }
    if (uVar3 == 0) {
      uVar2 = __copy_from_user(&local_cc);
    }
    else {
      __memzero(&local_cc,0xa4);
      uVar2 = 0xa4;
    }
    *(undefined4 *)(iVar1 + 0x2a) = local_cb;
    *(undefined4 *)(iVar1 + 0x2e) = local_c7;
    *(undefined4 *)(iVar1 + 0x32) = local_c3;
    *(undefined4 *)(iVar1 + 0x36) = local_bf;
    if (local_cc == '$') {
      uVar2 = rtmp_set_channel(param_1,pcVar4,local_a4[0]);
      return uVar2;
    }
    if (local_cc == '%') {
      if (2 < DebugLevel) {
        printk("%s num of channels in sorted channel list received from App =%d\n",
               "Channel_Info_MsgHandle",local_a4[0]);
      }
      uVar3 = (uint)local_a4[0];
      if (uVar3 != 0) {
        pbVar6 = (byte *)(param_1 + 0x2859a4);
        puVar5 = (undefined1 *)(param_1 + 0x2859e0);
        pbVar9 = local_a4;
        puVar7 = &uStack_68;
        iVar1 = 0;
        *(byte *)(param_1 + 0x2859a4) = local_a4[0];
        do {
          pbVar9 = pbVar9 + 1;
          pbVar6 = pbVar6 + 1;
          *pbVar6 = *pbVar9;
          if (0 < DebugLevel) {
            printk("%s channel[%d] = %d\n","Channel_Info_MsgHandle",iVar1);
            uVar3 = (uint)local_a4[0];
          }
          iVar1 = iVar1 + 1;
          puVar7 = puVar7 + 1;
          puVar5 = puVar5 + 1;
          *puVar5 = *puVar7;
        } while (iVar1 < (int)uVar3);
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s num of channels in sorted channel list received is invalid\n",
               "Channel_Info_MsgHandle");
        return 0;
      }
    }
    else {
      if (local_cc != '\"') {
        if (DebugLevel < 2) {
          return uVar2;
        }
        printk("%s: unknown action code. (%d)\n","Channel_Info_MsgHandle");
        return uVar2;
      }
      iVar8 = scan_in_run_state(param_1,pcVar4);
      if (iVar8 == 1) {
        if (-1 < DebugLevel) {
          printk("Scan in running State\n");
          return 0;
        }
      }
      else {
        if (*(int *)(iVar1 + 0x5c) == 0) {
          if (2 < DebugLevel) {
            printk("[%s][%d] : num of away channel to scan = %d\n","Channel_Info_MsgHandle",0x1d55,
                   local_94);
          }
          if (5 < local_94) {
            if (-1 < DebugLevel) {
              printk("Invalid Argument\n");
              return 2;
            }
            return 2;
          }
          *(char *)(iVar1 + 0x55) = (char)local_94;
          if (local_94 != 0) {
            pcVar12 = (char *)(iVar1 + 0x49);
            pcVar11 = (char *)(iVar1 + 0x55);
            pbVar6 = (byte *)(iVar1 + 0x4e);
            uVar3 = 0;
            pcVar10 = &local_cc;
            do {
              uVar3 = uVar3 + 1;
              pcVar12 = pcVar12 + 1;
              *pcVar12 = pcVar10[0x28];
              pcVar11 = pcVar11 + 1;
              *pcVar11 = pcVar10[0x2d];
              local_d8 = (uint)(byte)pcVar10[0x32];
              pbVar6 = pbVar6 + 1;
              *pbVar6 = pcVar10[0x32];
              if (2 < DebugLevel) {
                printk("[%s] channel = %d:scan type = %d:scan time = %d\n","Channel_Info_MsgHandle")
                ;
              }
              pcVar10 = pcVar10 + 1;
            } while (uVar3 < local_94);
          }
          local_d8 = 0;
          local_d4 = pcVar4;
          uVar2 = ApSiteSurveyNew_by_wdev(param_1,local_a4[0],local_9a[0],local_9f[0]);
          return uVar2;
        }
        if (2 < DebugLevel) {
          printk("%s:failed because offchannel scan is still ongoing\n","Channel_Info_MsgHandle");
          return 0;
        }
      }
    }
  }
  else if (-1 < DebugLevel) {
    printk("[%d][%s] error\n",0x1d41,"Channel_Info_MsgHandle");
  }
  return 0;
}

