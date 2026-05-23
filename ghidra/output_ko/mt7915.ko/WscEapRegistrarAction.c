// module: mt7915.ko
// function: WscEapRegistrarAction @ 0x1f0010
// size: 3476 bytes
//

void WscEapRegistrarAction(int param_1,int param_2,int param_3,int param_4,undefined4 *param_5)

{
  uint uVar1;
  byte bVar2;
  bool bVar3;
  char cVar4;
  size_t __n;
  undefined4 uVar5;
  undefined1 uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  undefined4 uVar10;
  uint local_38;
  undefined1 uStack_2d;
  void *local_2c [2];
  
  local_2c[0] = (void *)0x0;
  if (2 < DebugLevel) {
    printk("WscEapRegistrarAction Enter!\n");
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar7 = 0;
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
    iVar7 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_2 + 0x92c));
    if (iVar7 == 0) {
      printk(&_LC309,0xc23);
      dump_stack();
      return;
    }
    iVar7 = 2;
  }
  else {
    iVar7 = 0xff;
  }
  bVar3 = *(int *)(param_2 + 0x904) == 0x24;
  uVar1 = (uint)bVar3;
  uVar9 = uVar1;
  if (uVar1 != 0) {
    if (param_3 != 4) {
      local_38 = 0x10;
      goto LAB_001f00b0;
    }
    if ((((param_5[0xa88] == 4) && (*(char *)(param_5 + 0x715) == -1)) && ((int)param_5[4] < 0xc))
       && (*(char *)(param_5 + 0x9e3) == '\0')) {
      *(undefined1 *)(param_5 + 0x9e3) = 1;
      param_5[4] = 0xc;
      RTMPSetTimer(param_5 + 0x9e5,15000);
      *(undefined1 *)((int)param_5 + 0x278d) = 1;
    }
    iVar8 = *(ushort *)((int)param_5 + 0x2b26) + 0x400;
    os_alloc_mem(0,local_2c,iVar8);
    if (local_2c[0] != (void *)0x0) {
      __memzero(local_2c[0],iVar8);
      local_38 = 0x10;
      goto switchD_001f00ec_caseD_4;
    }
LAB_001f06d0:
    if (2 < DebugLevel) {
      printk("WscData Allocate failed!\n");
      goto LAB_001f03c4;
    }
    goto LAB_001f03e0;
  }
  local_38 = 0;
  if (*(char *)(param_5 + 0x9f2) != '\0') {
    *(bool *)(param_5 + 0x9f2) = bVar3;
  }
LAB_001f00b0:
  iVar8 = *(ushort *)((int)param_5 + 0x2b26) + 0x400;
  os_alloc_mem(0,local_2c,iVar8);
  if (local_2c[0] == (void *)0x0) goto LAB_001f06d0;
  __memzero(local_2c[0],iVar8);
  switch(param_3) {
  case 4:
switchD_001f00ec_caseD_4:
    if (2 < DebugLevel) {
      printk("WscEapRegistrarAction : Rx M1\n");
    }
    param_5[3] = 0xb;
    if (param_5[4] == 0xc) {
      local_38 = local_38 | 4;
      iVar8 = ProcessMessageM1(param_1,param_5,param_2,*(undefined4 *)(param_2 + 0x908),
                               param_5 + 0x1c);
      if (iVar8 == 0) {
        if (((*(char *)(param_5 + 0xa79) == '\0') || (*(char *)(param_5 + 0xaf8) != '\0')) ||
           ((1 < param_5[1] - 2 && ((param_5[1] != 1 || (param_5[5] == 0)))))) {
          __n = BuildMessageM2D(param_1,param_5,local_2c[0]);
          param_5[4] = 0xe;
          param_5[0xb12] = param_5[0xb12] + 1;
          if (*(char *)(param_5 + 0xb11) == '\0') {
            RTMPSetTimer(param_5 + 0xb04,15000);
            *(undefined1 *)(param_5 + 0xb11) = 1;
          }
        }
        else {
          zte_wps_overlap_detected(param_1,*(byte *)(param_5 + 0x715) & 0xf);
          param_5[3] = 0xc;
          __n = BuildMessageM2(param_1,param_5,local_2c[0]);
          param_5[4] = 0x12;
          if ((iVar7 == 2) && (uVar1 < (*(uint *)(&DAT_0057ffbc + param_1) & 1))) {
            if (*(char *)(param_5 + 0x9e2) == '\0') {
              uVar6 = 2;
            }
            else {
              uVar6 = 1;
            }
            *(undefined1 *)(param_5 + 2) = uVar6;
          }
        }
        goto LAB_001f0238;
      }
      break;
    }
LAB_001f02c0:
    __n = 0;
    goto LAB_001f02c4;
  default:
    if (2 < DebugLevel) {
      printk("WscEapRegistrarAction : Unsupported Msg Type\n");
    }
    if (local_2c[0] == (void *)0x0) {
      return;
    }
    os_free_mem();
    return;
  case 7:
    if (2 < DebugLevel) {
      printk("WscEapRegistrarAction : Rx M3\n");
    }
    if (param_5[4] != 0x12) goto LAB_001f02c0;
    param_5[3] = 0x10;
    iVar8 = ProcessMessageM3(param_1,param_2,*(undefined4 *)(param_2 + 0x908),param_5 + 0x1c);
    if (iVar8 == 0) {
      local_38 = local_38 | 4;
      __n = BuildMessageM4(param_1,param_5,local_2c[0]);
      param_5[3] = 0x11;
      param_5[4] = 0x14;
      goto LAB_001f0238;
    }
    break;
  case 9:
    if (2 < DebugLevel) {
      printk("WscEapRegistrarAction : Rx M5\n");
    }
    if (param_5[4] != 0x14) goto LAB_001f02c0;
    param_5[3] = 0x14;
    iVar8 = ProcessMessageM5(param_1,param_5,param_2,*(undefined4 *)(param_2 + 0x908),param_5 + 0x1c
                            );
    if (iVar8 == 0) {
      local_38 = local_38 | 4;
      __n = BuildMessageM6(param_1,param_5,local_2c[0]);
      param_5[3] = 0x15;
      param_5[4] = 0x16;
      goto LAB_001f0238;
    }
    break;
  case 0xb:
    if (2 < DebugLevel) {
      printk("WscEapRegistrarAction : Rx M7\n");
    }
    if (param_5[4] != 0x16) goto LAB_001f02c0;
    param_5[3] = 0x18;
    iVar8 = ProcessMessageM7(param_1,param_5,param_2,*(undefined4 *)(param_2 + 0x908),param_5 + 0x1c
                            );
    if (iVar8 != 0) break;
    if (iVar7 == 0) {
      local_38 = local_38 | 4;
      __n = BuildMessageM8(param_1,param_5,local_2c[0]);
      param_5[4] = 0x18;
      param_5[3] = 0x19;
      if (*(char *)((int)param_5 + 0x2b31) != '\0') {
        WscAddEntryToAclList(param_1,*(undefined1 *)(param_4 + 0xe4),param_4 + 0xec);
      }
      if (param_4 != 0) {
        _raw_spin_lock_bh(param_5 + 0xb00);
        WscDelListEntryByMAC(param_5 + 0xb01,param_4 + 0xec);
        _raw_spin_unlock_bh(param_5 + 0xb00);
      }
    }
    else {
      if (iVar7 != 2) goto LAB_001f02c0;
      if ((*(char *)(param_5 + 0x9e2) == '\0') ||
         (((*(char *)((int)param_5 + 0x2b32) != '\0' && (*(char *)((int)param_5 + 0x2b31) != '\0'))
          && (*(char *)((int)param_5 + 0x1e5) != '\0')))) {
        local_38 = local_38 | 4;
        __n = BuildMessageM8(param_1,param_5,local_2c[0]);
        param_5[3] = 0x19;
        param_5[4] = 0x18;
      }
      else {
        if (*(char *)(param_5 + 0x9e2) != '\x01') goto LAB_001f02c0;
        local_38 = local_38 | 3;
        __n = BuildMessageNACK(param_1,param_5,local_2c[0]);
        param_5[4] = 4;
        param_5[3] = 0x22;
        *(undefined1 *)((int)param_5 + 0x1c52) = 0;
      }
    }
    goto LAB_001f0238;
  case 0xf:
    if (2 < DebugLevel) {
      printk("WscEapRegistrarAction : Rx DONE\n");
    }
    if (param_5[4] != 0x18) goto LAB_001f02c0;
    if (iVar7 == 0) {
      param_5[3] = 0x1d;
      WscSendEapFail(param_1,param_5,0);
      param_5[3] = 0x22;
      if (param_5[0xa39] != 0) {
        if (0 < DebugLevel) {
          printk("<----- WscConWpsStop\n");
        }
        param_5[0xa39] = 0;
      }
LAB_001f0a04:
      __n = 0;
    }
    else {
      if (iVar7 != 2) goto LAB_001f0a04;
      if ((*(uint *)(param_1 + 0x795124) & 2) == 0) {
        local_38 = local_38 | 2;
        __n = BuildMessageACK(param_1,param_5,local_2c[0]);
      }
      else {
        __n = 0;
        WscSendEapFail(param_1,param_5);
      }
      param_5[3] = 0x22;
    }
    param_5[4] = 4;
    *(undefined1 *)((int)param_5 + 0x1c52) = 0;
LAB_001f0238:
    if (local_38 < 0x11) {
LAB_001f02c4:
      if (local_38 - 1 < 0xf) {
        param_5[0xafc] = 0;
        param_5[0xaff] = 0;
        *(undefined1 *)(param_5 + 0xafe) = 1;
        if ((*(char *)((int)param_5 + 0x2be1) != '\0') &&
           ((int)(uint)*(ushort *)(param_5 + 0xafb) < (int)__n)) {
          if (0x8ff < (int)__n) {
            printk(&_LC325,0xddf);
            dump_stack();
          }
          memmove((void *)param_5[0xafd],local_2c[0],__n);
          param_5[0xafc] = __n;
          __memzero(local_2c[0],__n);
          *(undefined1 *)(param_5 + 0xafe) = 0;
          *(undefined1 *)((int)param_5 + 0x2bf9) = 1;
          memmove(local_2c[0],(void *)param_5[0xafd],(uint)*(ushort *)(param_5 + 0xafb));
          __n = (size_t)*(ushort *)(param_5 + 0xafb);
          param_5[0xafc] = param_5[0xafc] - __n;
          param_5[0xaff] = param_5[0xafd] + __n;
        }
        if (iVar7 == 0) {
          if (param_5[4] != 4) {
            WscSendMessage(param_1,local_38,local_2c[0],__n,param_5,0,1);
          }
        }
        else if (iVar7 == 2) {
          if ((*(uint *)(param_1 + 0x795124) & 2) == 0) {
            WscSendMessage(param_1,local_38,local_2c[0],__n,param_5,2,2);
          }
          else {
            WscSendMessage(param_1,local_38,local_2c[0],__n,param_5,2,1);
          }
        }
      }
      else {
        uVar9 = 0;
      }
    }
    else {
      cVar4 = WscSendUPnPMessage(param_1,*(byte *)(param_5 + 0x715) & 0xf,0x11,0,local_2c[0],__n,
                                 *(undefined4 *)(param_2 + 0x910),*(undefined4 *)(param_2 + 0x914),
                                 (int)param_5 + 0x1c55,iVar7);
      if (cVar4 != '\0') {
        uVar9 = 0;
      }
    }
    if ((uVar1 != 0) && (param_5[4] == 0xe)) {
      param_5[4] = 8;
      *(undefined1 *)(param_5 + 0x9e3) = 0;
    }
LAB_001f03c4:
    if (2 < DebugLevel) {
      printk("WscEapRegistrarAction : rv = %d\n",0);
    }
    goto LAB_001f03d0;
  }
  if (2 < DebugLevel) {
    printk("WscEapRegistrarAction : rv = %d\n",iVar8);
  }
  if (iVar8 < 0x13) {
    *(short *)(param_5 + 0x5e) = (short)iVar8;
  }
  else if (iVar8 - 0xfeU < 2) {
    *(undefined2 *)(param_5 + 0x5e) = 2;
  }
  if (iVar8 == 0xfe) {
    param_5[3] = 0x1f;
    if (uVar1 == 0) goto LAB_001f0958;
LAB_001f05b8:
    if (*(char *)((int)param_5 + 0x278d) == '\x01') {
      RTMPCancelTimer(param_5 + 0x9e5,&uStack_2d);
      *(undefined1 *)((int)param_5 + 0x278d) = 0;
    }
    *(undefined1 *)(param_5 + 0x9e3) = 0;
  }
  else {
    if (iVar8 == 0xff) {
      param_5[3] = 0x20;
    }
    else {
      param_5[3] = 2;
    }
    if (uVar1 != 0) goto LAB_001f05b8;
LAB_001f0958:
    uVar5 = BuildMessageNACK(param_1,param_5,local_2c[0]);
    if (iVar7 == 0) {
      WscSendMessage(param_1,3,local_2c[0],uVar5,param_5,0,1);
      *(undefined1 *)(param_4 + 0xd24) = 0;
    }
    else if (iVar7 == 2) {
      if ((*(uint *)(param_1 + 0x795124) & 2) == 0) {
        uVar10 = 2;
      }
      else {
        uVar10 = 1;
      }
      WscSendMessage(param_1,3,local_2c[0],uVar5,param_5,2,uVar10);
    }
    RTMPCancelTimer(param_5 + 0x9f3,&uStack_2d);
    *(undefined1 *)(param_5 + 0x9f2) = 0;
  }
  if (0x15 < (int)param_5[4]) {
    *(undefined1 *)(param_5 + 0xa7d) = 1;
    param_5[5] = 0;
  }
  param_5[4] = 0;
  param_5[3] = 1;
LAB_001f03d0:
  if (local_2c[0] != (void *)0x0) {
    os_free_mem();
  }
LAB_001f03e0:
  if (uVar9 != 0) {
    WscUPnPErrHandle(param_1,param_5,*(undefined4 *)(param_2 + 0x910));
  }
  if (param_5[4] != 4) {
    return;
  }
  *(undefined1 *)(param_5 + 0xa79) = 0;
  if (*(char *)((int)param_5 + 0x1c5b) != '\0') {
    *(undefined1 *)((int)param_5 + 0x1c5b) = 0;
    RTMPCancelTimer(param_5 + 0x717,&uStack_2d);
  }
  if (uVar1 == 0) {
    if (iVar7 != 0) goto LAB_001f0658;
    bVar2 = *(byte *)(param_4 + 0xe4);
    WscBuildBeaconIE(param_1,2,0,0,0,(uint)bVar2,0,0,0);
    WscBuildProbeRespIE(param_1,3,2,0,0,0,*(undefined1 *)(param_5 + 0x715),0,0,0);
    UpdateBeaconHandler(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                + (uint)bVar2 * 0x5834 + param_1 + 0xe0,2);
    __memzero(param_1 + 0x795a84,0x88);
    if (*(char *)(param_5 + 2) != '\x01') goto LAB_001f0680;
  }
  else {
    if (*(char *)((int)param_5 + 0x278d) == '\x01') {
      RTMPCancelTimer(param_5 + 0x9e5,&uStack_2d);
      *(undefined1 *)((int)param_5 + 0x278d) = 0;
    }
    *(undefined1 *)(param_5 + 0x9e3) = 0;
    param_5[0x9e4] = 0;
LAB_001f0658:
    __memzero(param_1 + 0x795a84,0x88);
    if (iVar7 == 2) {
      *param_5 = 0;
      if (s__RB_FULL__Free_Queue_List___00371ba4[param_1 + 0x14] == '\x01') {
        param_5[4] = 0x1a;
      }
      if ((*(char *)(param_5 + 2) == '\x01') && ((*(uint *)(param_1 + 0x795124) & 2) != 0)) {
        *(undefined1 *)(param_5 + 2) = 2;
        (&DAT_00580cca)[param_1] = 1;
        if ((*(char *)(param_5 + 0x9e2) != '\0') &&
           (((*(char *)((int)param_5 + 0x2b32) == '\0' || (*(char *)((int)param_5 + 0x2b31) == '\0')
             ) || (*(char *)((int)param_5 + 0x1e5) == '\0')))) {
          RTMPMoveMemory(param_5 + 0x724,param_5 + 0x8f8,0x3a8);
        }
        WscWriteConfToPortCfg(param_1,param_5,param_5 + 0x726,1);
        RtmpOsTaskWakeUp(param_1 + 0x794ae8);
      }
      goto LAB_001f0680;
    }
    if (*(char *)(param_5 + 2) != '\x01') goto LAB_001f0680;
    if (iVar7 != 0) {
      if ((*(uint *)(param_1 + 0x795124) & 2) != 0) {
        *(undefined1 *)(param_5 + 2) = 2;
      }
      goto LAB_001f0680;
    }
  }
  *(undefined1 *)(param_5 + 2) = 2;
  param_5[0x725] = param_5[0x725] | 0x8000;
  RTMPSetTimer(param_5 + 0xacd,1000);
  *(undefined1 *)(param_5 + 0xada) = 1;
LAB_001f0680:
  uVar5 = HcGetBandByWdev(param_5[0xa7b]);
  RTMPSetLED(param_1,0xb,uVar5);
  param_5[5] = 0;
  RTMPCancelTimer(param_5 + 0x9f3,&uStack_2d);
  *(undefined1 *)(param_5 + 0x9f2) = 0;
  return;
}

