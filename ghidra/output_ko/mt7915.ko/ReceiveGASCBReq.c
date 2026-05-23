// module: mt7915.ko
// function: ReceiveGASCBReq @ 0x22c17c
// size: 916 bytes
//

void ReceiveGASCBReq(int param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  byte bVar7;
  int *piVar8;
  uint uVar9;
  int iVar10;
  int *piVar11;
  byte *__dest;
  int *local_30;
  byte *local_2c [2];
  
  if (2 < DebugLevel) {
    printk(&_LC1,"ReceiveGASCBReq");
  }
  bVar2 = 0;
  do {
    bVar7 = bVar2;
    uVar9 = (uint)bVar7;
    uVar5 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    iVar10 = uVar9 * 0x5834;
    if (uVar5 <= uVar9) goto LAB_0022c1fc;
    iVar4 = memcmp((void *)(param_2 + 4),
                   "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   + param_1 + iVar10 + 0x101,6);
    bVar2 = bVar7 + 1;
  } while (iVar4 != 0);
  piVar8 = (int *)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar10 + 0x1c);
  if (piVar8 == (int *)0x0) {
LAB_0022c1fc:
    if (2 < DebugLevel) {
      printk("%s Can not find Peer Control DA=%02x:%02x:%02x:%02x:%02x:%02x\n","ReceiveGASCBReq",
             *(undefined1 *)(param_2 + 4),*(undefined1 *)(param_2 + 5),*(undefined1 *)(param_2 + 6),
             *(undefined1 *)(param_2 + 7),*(undefined1 *)(param_2 + 8),*(undefined1 *)(param_2 + 9))
      ;
    }
  }
  else {
    os_alloc_mem(0,local_2c,0x11);
    if (local_2c[0] != (byte *)0x0) {
      __memzero(local_2c[0],0x11);
      pbVar3 = local_2c[0];
      piVar6 = piVar8 + 2;
      __dest = local_2c[0] + 1;
      *local_2c[0] = bVar7;
      memmove(__dest,(void *)(param_2 + 10),6);
      _raw_spin_lock_bh(piVar6);
      piVar11 = *(int **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar10 + 0x1c);
      do {
        local_30 = piVar11;
        if (piVar8 == piVar11) {
          _raw_spin_unlock_bh(piVar6);
          os_alloc_mem(0,&local_30,0x110);
          if (local_30 == (int *)0x0) {
            if (-1 < DebugLevel) {
              printk("%s Not available memory\n","ReceiveGASCBReq");
            }
          }
          else {
            __memzero(local_30,0x110);
            piVar11 = local_30;
            local_30[2] = 4;
            *(byte *)(local_30 + 3) = *pbVar3;
            memmove((char *)((int)local_30 + 0xd),(void *)(param_2 + 10),6);
            cVar1 = *(char *)(param_2 + 0x1a);
            piVar11[0x42] = (int)(piVar11 + 0x42);
            piVar11[0x43] = (int)(piVar11 + 0x42);
            *(char *)((int)piVar11 + 0x13) = cVar1;
            piVar11[6] = param_1;
            *(char *)(piVar11 + 5) = '\0';
            _raw_spin_lock_bh(piVar6);
            piVar8 = (int *)piVar8[1];
            *local_30 = *piVar8;
            local_30[1] = (int)piVar8;
            *(int **)(*piVar8 + 4) = local_30;
            *piVar8 = (int)local_30;
            _raw_spin_unlock_bh(piVar6);
            pbVar3[8] = 0;
            pbVar3[7] = 6;
            bVar2 = *(byte *)(param_2 + 0x1a);
            pbVar3[10] = 0;
            pbVar3[0xc] = 0;
            pbVar3[9] = bVar2;
            pbVar3[0xb] = 0x3c;
            SendGASCBRsp(param_1,local_2c[0]);
          }
LAB_0022c424:
          os_free_mem(local_2c[0]);
          return;
        }
        iVar10 = memcmp((char *)((int)piVar11 + 0xd),__dest,6);
        if (iVar10 == 0) {
          if (*(byte *)((int)piVar11 + 0xfa) + 1 < (uint)*(byte *)((int)piVar11 + 0xf9)) {
            _raw_spin_unlock_bh(piVar6);
            pbVar3[7] = 7;
            pbVar3[8] = 0;
            pbVar3[9] = *(byte *)(param_2 + 0x1a);
            bVar2 = *(byte *)(local_30 + 5);
            pbVar3[0xb] = 0;
            pbVar3[0xc] = 0;
            pbVar3[10] = bVar2;
            SendGASCBRsp(param_1,local_2c[0]);
          }
          else {
            _raw_spin_unlock_bh(piVar6);
            pbVar3[7] = 6;
            pbVar3[8] = 0;
            pbVar3[9] = *(byte *)(param_2 + 0x1a);
            pbVar3[10] = *(byte *)(local_30 + 5);
            if ("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n"[uVar9 * 0x5834 + param_1 + 0x28] ==
                '\x02') {
              pbVar3[0xc] = 0;
              pbVar3[0xb] = 0x41;
            }
            else {
              pbVar3[0xb] = 0;
              pbVar3[0xc] = 0;
            }
            SendGASCBRsp(param_1,local_2c[0]);
          }
          goto LAB_0022c424;
        }
        piVar11 = (int *)*piVar11;
      } while( true );
    }
    if (-1 < DebugLevel) {
      printk("%s Not available memory\n","ReceiveGASCBReq");
    }
  }
  return;
}

