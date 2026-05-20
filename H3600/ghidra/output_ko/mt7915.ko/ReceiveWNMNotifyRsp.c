// module: mt7915.ko
// function: ReceiveWNMNotifyRsp @ 0x229f50
// size: 708 bytes
//

void ReceiveWNMNotifyRsp(int param_1,int param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  byte bVar5;
  char *pcVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  undefined *puVar10;
  char *pcVar11;
  undefined1 uStack_2d;
  byte *local_2c [2];
  
  printk(&_LC4,"ReceiveWNMNotifyRsp");
  bVar1 = 0;
  do {
    bVar5 = bVar1;
    uVar8 = (uint)bVar5;
    uVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    iVar9 = uVar8 * 0x5834;
    if (uVar4 <= uVar8) goto LAB_00229fc8;
    iVar3 = memcmp((void *)(param_2 + 0x10),
                   "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   + param_1 + iVar9 + 0x101,6);
    bVar1 = bVar5 + 1;
  } while (iVar3 != 0);
  if (param_1 + iVar9 == -0x2bbeb4) {
LAB_00229fc8:
    if (-1 < DebugLevel) {
      printk("%s Can not find Peer Control\n","ReceiveWNMNotifyRsp");
    }
  }
  else {
    puVar10 = &_LC170 + param_1 + iVar9;
    down_interruptible(puVar10);
    pcVar11 = "RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar9 + 4;
    pcVar6 = *(char **)("RT_OID_WSC_SET_MODE::WscMode = %d\n" + param_1 + iVar9 + 4);
    if (pcVar6 != pcVar11) {
      do {
        iVar9 = memcmp(pcVar6 + 0xd,(void *)(param_2 + 10),6);
        if (iVar9 == 0) {
          up(puVar10);
          RTMPCancelTimer(pcVar6 + 0x18,&uStack_2d);
          RTMPReleaseTimer(pcVar6 + 0x18,&uStack_2d);
          os_alloc_mem(0,local_2c,0xd);
          if (local_2c[0] != (byte *)0x0) {
            __memzero(local_2c[0],0xd);
            pbVar2 = local_2c[0];
            *local_2c[0] = bVar5;
            memmove(local_2c[0] + 1,(void *)(param_2 + 10),6);
            pbVar2[8] = 0;
            pbVar2[7] = 1;
            bVar1 = *(byte *)(param_2 + 0x1a);
            pbVar2[10] = 1;
            pbVar2[0xb] = 0;
            pbVar2[9] = bVar1;
            pbVar2[0xc] = *(byte *)(param_2 + 0x1b);
            MlmeEnqueue(param_1,0x29,1,0xd,local_2c[0],0);
            os_free_mem(local_2c[0]);
            return;
          }
          if (DebugLevel < 0) {
            return;
          }
          printk("%s Not available memory\n","ReceiveWNMNotifyRsp");
          return;
        }
        pcVar6 = *(char **)pcVar6;
      } while (pcVar6 != pcVar11);
    }
    up(puVar10);
    if (-1 < DebugLevel) {
      printk("Not found peer entry in list\n");
    }
    printk("client mac:%02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(param_2 + 10),
           *(undefined1 *)(param_2 + 0xb),*(undefined1 *)(param_2 + 0xc),
           *(undefined1 *)(param_2 + 0xd),*(undefined1 *)(param_2 + 0xe),
           *(undefined1 *)(param_2 + 0xf));
    for (piVar7 = *(int **)("RT_OID_WSC_SET_MODE::WscMode = %d\n" + uVar8 * 0x5834 + param_1 + 4);
        (int *)pcVar11 != piVar7; piVar7 = (int *)*piVar7) {
      printk("list=> %02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)((int)piVar7 + 0xd),
             *(undefined1 *)((int)piVar7 + 0xe),*(undefined1 *)((int)piVar7 + 0xf),
             *(undefined1 *)(piVar7 + 4),*(undefined1 *)((int)piVar7 + 0x11),
             *(undefined1 *)((int)piVar7 + 0x12));
    }
    printk(&_LC84);
  }
  return;
}

