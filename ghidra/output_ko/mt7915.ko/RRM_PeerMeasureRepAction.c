// module: mt7915.ko
// function: RRM_PeerMeasureRepAction @ 0x222d24
// size: 1116 bytes
//

void RRM_PeerMeasureRepAction(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  char *pcVar5;
  uint uVar6;
  char *__src;
  int iVar7;
  uint uVar8;
  char *pcVar9;
  undefined1 uStack_35;
  undefined4 *local_34;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  
  iVar7 = *(int *)(param_2 + 0x908);
  local_2e = 0;
  local_2d = 0;
  local_2c = 0;
  local_2b = 0;
  local_2a = 0;
  local_29 = 0;
  os_alloc_mem(0,&local_34,0x40c);
  if (local_34 == (undefined4 *)0x0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("RRM_PeerMeasureRepAction alloc memory failed sizeof=%d",0x40c);
    return;
  }
  __memzero(local_34,0x40c);
  if (DebugLevel < 3) {
    cVar4 = *(char *)(param_2 + 0x1a);
    if (cVar4 == '\0') {
      cVar4 = *(char *)(param_2 + 0x1d);
      if (cVar4 == '\0') {
LAB_00222e8c:
        if (-1 < DebugLevel) {
          printk("Both DialogToken and MeasurementToken are zero, drop this packet!\n");
        }
        goto LAB_00222e94;
      }
LAB_00222e2c:
      iVar2 = MeasureReqLookUp(param_1,cVar4);
      if (iVar2 == 0) {
        if (-1 < DebugLevel) {
          printk("MeasurementToken invalid(%d)!",*(undefined1 *)(param_2 + 0x1d));
        }
        goto LAB_00222e94;
      }
      cVar4 = '\0';
      goto LAB_00222db8;
    }
  }
  else {
    printk("%s::\n","RRM_PeerMeasureRepAction");
    cVar4 = *(char *)(param_2 + 0x1a);
    if (cVar4 == '\0') {
      cVar4 = *(char *)(param_2 + 0x1d);
      if (cVar4 == '\0') goto LAB_00222e8c;
      if (2 < DebugLevel) {
        printk("DialogToken is zere, MeasurementToken is non-zero, check MeasurementToken!\n");
        cVar4 = *(char *)(param_2 + 0x1d);
      }
      goto LAB_00222e2c;
    }
    if (2 < DebugLevel) {
      printk("DialogToken is non-zere, check DialogToken!\n");
    }
  }
  iVar2 = MeasureReqLookUp(param_1,cVar4);
  if (iVar2 == 0) {
    if (0 < DebugLevel) {
      printk("DialogToken invalid(%d)!",cVar4);
    }
LAB_00222e94:
    os_free_mem(local_34);
    return;
  }
LAB_00222db8:
  __src = (char *)(param_2 + 0x1b);
  RTMPCancelTimer(iVar2 + 0x50,&uStack_35);
  RTMPReleaseTimer(iVar2 + 0x50,&uStack_35);
  iVar3 = MacTableLookup(param_1,param_2 + 10);
  if (((iVar3 == 0) || (*(int *)(iVar3 + 0xfc) != 2)) || (*(int *)(iVar3 + 8) == 0)) {
    uVar8 = 0;
  }
  else {
    pcVar9 = __src + iVar7 + -3;
    uVar8 = 0;
    *local_34 = *(undefined4 *)(iVar2 + 0x48);
    *(undefined2 *)(local_34 + 1) = *(undefined2 *)(iVar2 + 0x4c);
    uVar6 = (uint)*(byte *)(param_2 + 0x1c);
    pcVar5 = __src + uVar6 + 1;
    while (pcVar5 < pcVar9) {
      if (*__src == '\'') {
        bVar1 = __src[3];
        if (uVar6 - 3 == 0) {
          if ((bVar1 & 4) == 0) {
            if ((bVar1 & 2) == 0) {
              if ((bVar1 & 1) == 0) {
                if (2 < DebugLevel) {
                  printk("STA has no beacon report(%02x:%02x:%02x:%02x:%02x:%02x) info to report",
                         *(undefined1 *)(param_2 + 10),*(undefined1 *)(param_2 + 0xb),
                         *(undefined1 *)(param_2 + 0xc),*(undefined1 *)(param_2 + 0xd),
                         *(undefined1 *)(param_2 + 0xe),*(undefined1 *)(param_2 + 0xf));
                }
              }
              else if (2 < DebugLevel) {
                printk("the request to do the mesurement with type(%d) is too late");
              }
            }
            else if (2 < DebugLevel) {
              printk("STA do not support the mesurement with type(%d)");
            }
          }
          else if (2 < DebugLevel) {
            printk("STA refuse to do the mesurement with type(%d)");
          }
          wext_send_bcn_rsp_event
                    (*(undefined4 *)
                      (
                      "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      + (uint)*(byte *)(iVar2 + 0x4e) * 0x5834 + param_1 + 0xe0),
                     (undefined4 *)(iVar2 + 0x48),__src + 2,3,cVar4);
          goto LAB_00222f8c;
        }
        if (__src[4] == '\x05') {
          RRM_BeaconReportHandler(param_1,*(undefined4 *)(iVar3 + 8),__src + 5,uVar6 - 3,iVar2);
        }
        iVar7 = memcmp(__src + 0x14,&local_2e,6);
        if ((iVar7 == 0) && (__src[0x12] == '\0')) goto LAB_00222f8c;
        uVar6 = (uint)(byte)__src[1];
        if (0x3ff < uVar8 + uVar6 + 2) goto LAB_00222f90;
        *(char *)((int)local_34 + 6) = *(char *)((int)local_34 + 6) + '\x01';
        memcpy((void *)((int)local_34 + uVar8 + 0xc),__src,(byte)__src[1] + 2);
        iVar7 = (byte)__src[1] + 2;
        uVar8 = uVar8 + iVar7 & 0xffff;
      }
      else {
LAB_00222f8c:
        uVar6 = (uint)(byte)__src[1];
LAB_00222f90:
        iVar7 = uVar6 + 2;
      }
      __src = __src + iVar7;
      uVar6 = (uint)(byte)__src[1];
      pcVar5 = __src + uVar6 + 1;
    }
  }
  if (*(char *)((int)local_34 + 6) != '\0') {
    local_34[2] = uVar8;
    Kernel_ASEND("multiapd.map.slave",0xa2bc,local_34,0x40c,0,0);
  }
  os_free_mem(local_34);
  MeasureReqDelete(param_1,*(undefined1 *)(iVar2 + 9));
  return;
}

