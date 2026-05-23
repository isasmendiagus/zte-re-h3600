// module: mt7915.ko
// function: ReceiveGASInitReq @ 0x22bb88
// size: 1520 bytes
//

void ReceiveGASInitReq(int param_1,int param_2)

{
  char cVar1;
  int *piVar2;
  byte *pbVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  size_t __n;
  undefined4 uVar7;
  int *piVar8;
  byte bVar9;
  int *piVar10;
  uint uVar11;
  int *piVar12;
  byte *__dest;
  int *piVar13;
  int *piVar14;
  bool bVar15;
  undefined1 uStack_33;
  ushort local_32;
  int *local_30;
  byte *local_2c [2];
  
  if (2 < DebugLevel) {
    printk(&_LC1,"ReceiveGASInitReq");
  }
  bVar4 = 0;
  do {
    bVar9 = bVar4;
    uVar11 = (uint)bVar9;
    uVar6 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    piVar13 = (int *)(uVar11 * 0x5834);
    if (uVar6 <= uVar11) goto LAB_0022bc0c;
    iVar5 = memcmp((void *)(param_2 + 4),
                   (char *)((int)piVar13 +
                           (int)(
                                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                + param_1 + 0x101)),6);
    bVar4 = bVar9 + 1;
  } while (iVar5 != 0);
  uVar7 = *(undefined4 *)
           ((int)piVar13 +
           (int)(
                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                + param_1 + 0xe0));
  piVar12 = (int *)((int)piVar13 +
                   (int)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + 0x1c));
  if (piVar12 == (int *)0x0) {
LAB_0022bc0c:
    if (2 < DebugLevel) {
      printk("%s Can not find Peer Control DA=%02x:%02x:%02x:%02x:%02x:%02x\n","ReceiveGASInitReq",
             *(undefined1 *)(param_2 + 4),*(undefined1 *)(param_2 + 5),*(undefined1 *)(param_2 + 6),
             *(undefined1 *)(param_2 + 7),*(undefined1 *)(param_2 + 8),*(undefined1 *)(param_2 + 9))
      ;
    }
  }
  else {
    piVar8 = piVar12 + 2;
    _raw_spin_lock_bh(piVar8);
    piVar10 = *(int **)((int)piVar13 +
                       (int)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + 0x1c));
    local_30 = piVar10;
    if (piVar12 != piVar10) {
LAB_0022bc94:
      local_30 = piVar10;
      iVar5 = memcmp((char *)((int)piVar10 + 0xd),(void *)(param_2 + 10),6);
      if (iVar5 != 0) goto LAB_0022bc80;
      *(char *)(piVar10 + 0x41) = (char)piVar10[0x41] + '\x01';
      _raw_spin_unlock_bh(piVar8);
      if (0 < DebugLevel) {
        printk("%s Q %d, old 0x%x, 0x%x, %02x:%02x:%02x:%02x:%02x:%02x remove peer\n",
               "ReceiveGASInitReq",(char)local_30[0x41],*(char *)((int)local_30 + 0x13),
               *(undefined1 *)(param_2 + 0x1a),*(char *)((int)local_30 + 0xd),
               *(char *)((int)local_30 + 0xe),*(char *)((int)local_30 + 0xf),(char)local_30[4],
               *(char *)((int)local_30 + 0x11),*(char *)((int)local_30 + 0x12));
      }
      _raw_spin_lock_bh(piVar8);
      local_30 = *(int **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" +
                          uVar11 * 0x5834 + param_1 + 0x1c);
      bVar15 = piVar12 != local_30;
      if (bVar15) {
        piVar10 = (int *)0x0;
        piVar13 = local_30;
      }
      piVar14 = (int *)*local_30;
      while (piVar2 = piVar14, bVar15) {
        iVar5 = memcmp((char *)((int)piVar13 + 0xd),(void *)(param_2 + 10),6);
        if (iVar5 == 0) {
          piVar13 = (int *)piVar13[0x42];
          piVar14 = (int *)*piVar13;
          if (piVar13 != local_30 + 0x42) {
            do {
              if (piVar14 != (int *)0x0) {
                piVar14[1] = piVar13[1];
              }
              if ((int *)piVar13[1] != (int *)0x0) {
                *(int *)piVar13[1] = *piVar13;
              }
              *piVar13 = (int)piVar10;
              piVar13[1] = (int)piVar10;
              os_free_mem(piVar13[3]);
              os_free_mem(piVar13);
              bVar15 = piVar14 != local_30 + 0x42;
              piVar13 = piVar14;
              piVar14 = (int *)*piVar14;
            } while (bVar15);
          }
          if (*local_30 != 0) {
            *(int *)(*local_30 + 4) = local_30[1];
          }
          if ((int *)local_30[1] != (int *)0x0) {
            *(int *)local_30[1] = *local_30;
          }
          *local_30 = (int)piVar10;
          local_30[1] = (int)piVar10;
          local_30[0x42] = (int)(local_30 + 0x42);
          local_30[0x43] = (int)(local_30 + 0x42);
          if ((char)local_30[0x14] != '\0') {
            RTMPCancelTimer(local_30 + 7,&uStack_33);
            *(char *)(local_30 + 0x14) = (char)piVar10;
          }
          RTMPReleaseTimer(local_30 + 7,&uStack_33);
          if ((char)local_30[0x22] != '\0') {
            RTMPCancelTimer(local_30 + 0x15,&uStack_33);
            *(char *)(local_30 + 0x22) = (char)piVar10;
          }
          RTMPReleaseTimer(local_30 + 0x15,&uStack_33);
          local_30[0x40] = local_30[0x40] + 1;
          os_free_mem(local_30);
        }
        bVar15 = piVar12 != piVar2;
        local_30 = piVar2;
        piVar14 = (int *)*piVar2;
        piVar13 = piVar2;
      }
    }
LAB_0022be20:
    _raw_spin_unlock_bh(piVar8);
    os_alloc_mem(0,&local_30,0x110);
    if (local_30 == (int *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s Not available memory\n","ReceiveGASInitReq");
      }
    }
    else {
      __memzero(local_30,0x110);
      piVar13 = local_30;
      local_30[2] = 2;
      local_30[0x3f] = local_30[0x3f] + 1;
      *(char *)(local_30 + 0x41) = (char)local_30[0x41] + '\x01';
      memmove((char *)((int)local_30 + 0xd),(void *)(param_2 + 10),6);
      cVar1 = *(char *)(param_2 + 0x1a);
      piVar13[6] = param_1;
      *(char *)((int)piVar13 + 0x13) = cVar1;
      RTMPInitTimer(param_1,piVar13 + 7,rtmp_timer_PostReplyTimeout,piVar13,0);
      local_30[0x3f] = local_30[0x3f] + 1;
      RTMPInitTimer(param_1,local_30 + 0x15,rtmp_timer_GASRspBufferingTimeout,local_30,0);
      local_30[0x42] = (int)(local_30 + 0x42);
      local_30[0x43] = (int)(local_30 + 0x42);
      local_30[0x3f] = local_30[0x3f] + 1;
      _raw_spin_lock_bh(piVar8);
      piVar13 = (int *)piVar12[1];
      *local_30 = *piVar13;
      local_30[1] = (int)piVar13;
      *(int **)(*piVar13 + 4) = local_30;
      *piVar13 = (int)local_30;
      _raw_spin_unlock_bh(piVar8);
      local_32 = *(ushort *)(param_2 + 0x1f);
      uVar6 = (uint)local_32;
      os_alloc_mem(0,local_2c,uVar6 + 0x11);
      if (local_2c[0] != (byte *)0x0) {
        __memzero(local_2c[0],uVar6 + 0x11);
        pbVar3 = local_2c[0];
        __dest = local_2c[0] + 1;
        *local_2c[0] = bVar9;
        memmove(__dest,(void *)(param_2 + 10),6);
        pbVar3[8] = 0;
        pbVar3[7] = 3;
        pbVar3[9] = *(byte *)(param_2 + 0x1a);
        pbVar3[10] = *(byte *)(param_2 + 0x1e);
        *(char *)(local_30 + 5) = *(char *)(param_2 + 0x1e);
        memmove(pbVar3 + 0xb,(ushort *)(param_2 + 0x1f),2);
        __n = (size_t)*(ushort *)(pbVar3 + 0xb);
        if (pbVar3[10] == 0) {
          wext_send_anqp_req_event(uVar7,__dest,param_2 + 0x18,__n + 9 & 0xffff);
          __n = (size_t)*(ushort *)(pbVar3 + 0xb);
        }
        memmove(pbVar3 + 0xd,(void *)(param_2 + 0x21),__n);
        SendGASIndication(param_1,local_2c[0]);
        os_free_mem(local_2c[0]);
        return;
      }
      if (-1 < DebugLevel) {
        printk("%s Not available memory\n","ReceiveGASInitReq");
      }
      if (*local_30 != 0) {
        *(int *)(*local_30 + 4) = local_30[1];
      }
      if ((int *)local_30[1] != (int *)0x0) {
        *(int *)local_30[1] = *local_30;
      }
      *local_30 = 0;
      local_30[1] = 0;
      os_free_mem(local_30);
    }
  }
  return;
LAB_0022bc80:
  piVar10 = (int *)*piVar10;
  local_30 = piVar10;
  if (piVar12 == piVar10) goto LAB_0022be20;
  goto LAB_0022bc94;
}

