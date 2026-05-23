// module: mt7915.ko
// function: ZTE_Show_ChannelStat @ 0x157400
// size: 1004 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 ZTE_Show_ChannelStat(int *param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 uVar9;
  int iVar10;
  bool bVar11;
  undefined1 auStack_60 [4];
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  undefined1 auStack_48 [12];
  undefined4 local_3c [3];
  undefined4 *******local_30;
  undefined4 *******local_2c;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 == 0) {
    return 1;
  }
  piVar3 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,0);
  if (piVar3 == (int *)0x0) {
    return 1;
  }
  iVar10 = *piVar3;
  if (iVar10 == 0) {
    return 1;
  }
  iVar4 = HcGetBandByWdev(iVar2);
  local_50 = (uint)*(byte *)(iVar2 + 0x1a);
  local_5c = (uint)*(byte *)((int)param_1 + 0x36b861);
  iVar2 = Get_OBSS_AirTime(param_1,iVar4);
  iVar5 = Get_My_Tx_AirTime(param_1,iVar4);
  iVar6 = Get_My_Rx_AirTime(param_1,iVar4);
  if (iVar2 == 0) {
    local_4c = 0;
  }
  else {
    local_4c = (uint)((int)((ulonglong)(uint)(iVar2 * 100) * 0x431bde83 >> 0x20) << 6) >> 0x18;
  }
  if (iVar6 == 0 && iVar5 == 0) {
    uVar8 = 0;
    local_58 = 0;
    local_54 = 0;
  }
  else {
    bVar11 = iVar5 != 0;
    uVar8 = (iVar6 + iVar5) * 0x19;
    if (bVar11) {
      iVar2 = iVar5 * 0x19;
    }
    else {
      iVar2 = 0;
      local_58 = 0;
    }
    if (bVar11) {
      uVar8 = iVar2 << 2;
    }
    if (bVar11) {
      local_58 = (uint)((int)((ulonglong)uVar8 * 0x431bde83 >> 0x20) << 6) >> 0x18;
    }
    uVar8 = (uint)((iVar6 + iVar5) * 100) / 1000000 & 0xff;
    local_54 = 0;
    if (iVar6 != 0) {
      local_54 = (uint)((int)((ulonglong)(uint)(iVar6 * 100) * 0x431bde83 >> 0x20) << 6) >> 0x18;
    }
  }
  if (iVar4 == 0) {
    mac_io_write32(param_1[0x29e5e8],0x83082004,0);
    mac_io_write32(param_1[0x29e5e8],0x83082004,0xa00);
  }
  else if (iVar4 == 1) {
    mac_io_write32(param_1[0x29e5e8],0x83092004,0);
    mac_io_write32(param_1[0x29e5e8],0x83092004,0xa00);
  }
  AsicGetChBusyCnt(param_1,iVar4,0,0);
  if ((*(uint *)(((uint)auStack_60 & 0xffffe000) + 4) & 0x1fff00) == 0) {
    iVar2 = 0x28;
    __init_waitqueue_head(auStack_48,"&_wait",&_LANCHOR2);
    do {
      local_3c[0] = 0;
      local_30 = &local_30;
      local_2c = &local_30;
      for (iVar5 = 1; iVar6 = prepare_to_wait_event(auStack_48,local_3c,1), iVar5 != 0 && iVar6 == 0
          ; iVar5 = schedule_timeout(iVar5)) {
      }
      finish_wait(auStack_48,local_3c);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  else {
    RtmpusecDelay(400000);
  }
  uVar7 = AsicGetCCACnt(param_1,iVar4);
  iVar2 = AsicGetChBusyCnt(param_1,iVar4,0,0);
  uVar9 = *(undefined4 *)(iVar10 + (local_5c + 0x3c) * 4);
  if ((((((-1 < DebugLevel) &&
         (printk("Channel:%d channel_idx=%d\n",local_50,local_5c), uVar1 = local_4c, -1 < DebugLevel
         )) && (printk("ChannelUtilization:%d\n",uVar8 + local_4c), -1 < DebugLevel)) &&
       ((printk("ObssAirOccupyPercentage:%d\n",uVar1), -1 < DebugLevel &&
        (printk("MyAirOccupyPercentage:%d\n",uVar8), -1 < DebugLevel)))) &&
      ((printk("MyTxAirOccupyPercentage:%d\n",local_58), -1 < DebugLevel &&
       ((printk("MyRxAirOccupyPercentage:%d\n",local_54), -1 < DebugLevel &&
        (printk("busy_time:%d\n",(uint)(iVar2 * 100) / 400,iVar2 * 0x1c), -1 < DebugLevel)))))) &&
     (printk("cca_cnt:%d\n",uVar7), -1 < DebugLevel)) {
    printk("ap_cnt:%d\n",uVar9);
  }
  return 1;
}

