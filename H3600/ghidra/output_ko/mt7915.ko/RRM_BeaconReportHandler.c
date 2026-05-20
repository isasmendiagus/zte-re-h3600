// module: mt7915.ko
// function: RRM_BeaconReportHandler @ 0x22285c
// size: 1220 bytes
//

void RRM_BeaconReportHandler
               (int param_1,undefined4 param_2,undefined1 *param_3,int param_4,int param_5)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  undefined1 uVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  undefined4 *__s1;
  undefined4 *puVar8;
  uint uVar9;
  void *__s2;
  int iVar10;
  int iVar11;
  uint uVar12;
  undefined2 local_36;
  int local_34;
  undefined4 local_30;
  undefined4 *local_2c [2];
  
  local_36 = 0;
  local_34 = 0;
  local_2c[0] = (undefined4 *)0x0;
  os_alloc_mem(0,&local_34,0x400);
  if (local_34 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): Alloc VarIE failed!\n","RRM_BeaconReportHandler");
    }
  }
  else {
    __memzero(local_34,0x400);
    os_alloc_mem(0,local_2c,0x180);
    if (local_2c[0] == (undefined4 *)0x0) {
      if (local_34 != 0) {
        os_free_mem();
      }
      if (-1 < DebugLevel) {
        printk("%s(): Alloc ie_list failed!\n","RRM_BeaconReportHandler");
      }
    }
    else {
      __memzero(local_2c[0],0x180);
      uVar12 = (uint)*(byte *)(param_5 + 9);
      wext_send_bcn_rsp_event
                (*(undefined4 *)
                  (
                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                  + (uint)*(byte *)(param_5 + 0x4e) * 0x5834 + param_1 + 0xe0),param_5 + 0x48,
                 param_3,0x1a,uVar12);
      local_30 = *(undefined4 *)(param_3 + 0x16);
      bVar1 = param_3[0xc];
      if ((2 < DebugLevel) &&
         (printk("%s:: ReqClass=%d, Channel=%d\n","RRM_BeaconReportHandler",*param_3,param_3[1]),
         2 < DebugLevel)) {
        uVar12 = (uint)(byte)param_3[0x12];
        pcVar7 = "beacon, probe resp";
        if ((bVar1 & 0x80) != 0) {
          pcVar7 = "measurement pilot";
        }
        printk("Bssid=%02x:%02x:%02x:%02x:%02x:%02x, FrameType=%s\n",param_3[0xf],param_3[0x10],
               param_3[0x11],uVar12,param_3[0x13],param_3[0x14],pcVar7);
      }
      param_4 = param_4 + -0x1a;
      cVar2 = param_3[0xd];
      pcVar7 = param_3 + 0x1a;
      cVar3 = "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x12];
      if (param_4 < 1) {
        iVar11 = 0;
        iVar10 = 0;
      }
      else {
        uVar9 = bVar1 & 0xffffff80;
        iVar11 = 0;
        iVar10 = 0;
        do {
          iVar5 = local_34;
          if (*pcVar7 == '\x01') {
            if ((bVar1 & 0x80) == 0) {
              *(char *)(local_34 + 1) = (char)uVar9;
              uVar12 = (uint)(byte)param_3[1];
              iVar11 = PeerBeaconAndProbeRspSanity
                                 (param_1,param_2,pcVar7 + 2,pcVar7[1],uVar12,local_2c[0],&local_36,
                                  local_34,uVar9,1);
              iVar10 = iVar5;
              if (2 < DebugLevel) {
                printk("%s:: bFrameBody=%d\n","RRM_BeaconReportHandler",iVar11);
              }
            }
          }
          else if ((*pcVar7 == -0x23) && (2 < DebugLevel)) {
            printk("%s:: SubIe: ID=%x, Len=%d\n","RRM_BeaconReportHandler",0xdd,pcVar7[1],uVar12);
          }
          uVar6 = (uint)(byte)pcVar7[1];
          param_4 = param_4 + (-2 - uVar6);
          pcVar7 = pcVar7 + uVar6 + 2;
        } while ((uVar6 != 0) && (0 < param_4));
      }
      puVar8 = local_2c[0];
      __s1 = (undefined4 *)(param_3 + 0xf);
      __s2 = (void *)((int)local_2c[0] + 6);
      iVar5 = memcmp(__s1,__s2,6);
      if (iVar5 != 0) {
        if (2 < DebugLevel) {
          uVar12 = (uint)(byte)param_3[0x11];
          printk("%s():BcnReq->BSSID=%02x:%02x:%02x:%02x:%02x:%02x not equal ie_list->Bssid=%02x:%02x:%02x:%02x:%02x:%02x!\n"
                 ,"RRM_BeaconReportHandler",param_3[0xf],param_3[0x10],uVar12,param_3[0x12],
                 param_3[0x13],param_3[0x14],*(undefined1 *)((int)puVar8 + 6),
                 *(undefined1 *)((int)puVar8 + 7),*(undefined1 *)(puVar8 + 2),
                 *(undefined1 *)((int)puVar8 + 9),*(undefined1 *)((int)puVar8 + 10),
                 *(undefined1 *)((int)puVar8 + 0xb));
          __s2 = (void *)((int)local_2c[0] + 6);
          puVar8 = local_2c[0];
        }
        iVar5 = memcmp(__s2,&ZERO_MAC_ADDR,6);
        if (iVar5 == 0) {
          *puVar8 = *__s1;
          *(undefined2 *)(puVar8 + 1) = *(undefined2 *)(param_3 + 0x13);
          *(undefined4 *)((int)local_2c[0] + 6) = *__s1;
          *(undefined2 *)((int)local_2c[0] + 10) = *(undefined2 *)(param_3 + 0x13);
          puVar8 = local_2c[0];
        }
      }
      if (*(char *)(puVar8 + 0xc) == '\0') {
        *(undefined1 *)(puVar8 + 0xc) = param_3[1];
      }
      if (2 < DebugLevel) {
        printk("%s():ie_list->Channel=%d\n","RRM_BeaconReportHandler",*(undefined1 *)(puVar8 + 0xc),
               DebugLevel,uVar12);
      }
      if (iVar11 != 0) {
        iVar11 = get_scan_tab_by_wdev(param_1,param_2);
        *(undefined1 *)(local_2c[0] + 0x29) = 1;
        iVar10 = BssTableSetEntry(param_1,param_2,iVar11,local_2c[0],(int)(char)(cVar2 + cVar3),
                                  local_36,iVar10);
        if (iVar10 != -1) {
          iVar11 = iVar11 + iVar10 * 0xaf4;
          *(undefined4 *)(iVar11 + 0x4fe) = local_30;
          uVar4 = *param_3;
          *(byte *)(iVar11 + 0x6c8) = (byte)(((uint)bVar1 << 0x19) >> 0x19);
          *(undefined1 *)(iVar11 + 0x6c7) = uVar4;
          *(undefined1 *)(iVar11 + 0x6c9) = param_3[0xe];
        }
      }
      if (local_2c[0] != (undefined4 *)0x0) {
        os_free_mem();
      }
      if (local_34 != 0) {
        os_free_mem();
        return;
      }
    }
  }
  return;
}

