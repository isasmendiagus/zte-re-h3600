// module: mt7915.ko
// function: scan_next_channel @ 0x1435f4
// size: 2172 bytes
//

undefined4 scan_next_channel(int param_1,int param_2,undefined1 *param_3)

{
  byte bVar1;
  undefined1 uVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  ushort uVar7;
  bool bVar8;
  uint uVar9;
  int iVar10;
  ushort uVar11;
  bool bVar12;
  uint local_e0;
  undefined4 local_d8;
  undefined4 uStack_d4;
  undefined1 local_cc;
  undefined4 local_cb;
  undefined4 local_c7;
  undefined4 local_c3;
  undefined4 local_bf;
  undefined1 local_a4;
  byte local_a3;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  byte local_8b;
  
  if (param_2 == 0) {
LAB_00143a2c:
    printk(&_LC0,0x3b1);
    dump_stack();
    return 0;
  }
  pbVar3 = (byte *)get_scan_ctrl_by_wdev();
  iVar10 = *(int *)(param_2 + 0x14);
  iVar4 = GetStaCfgByWdev(param_1,param_2);
  if (iVar10 == 0x10 || (iVar10 - 2U & 0xfffffffd) == 0) {
    if (iVar4 == 0) goto LAB_00143a2c;
    iVar4 = 0;
  }
  else {
    iVar4 = 1;
  }
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
    return 0;
  }
  if ((*(int *)(param_1 + 0xa77bb4) == 1) &&
     ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)) {
    return 0;
  }
  if ((*(char *)(param_1 + 0x286285) == '\0') && ("hif_set_WPDMA"[param_1 + 0xc] == '\x01')) {
    return 0;
  }
  bVar12 = false;
  *param_3 = 0;
  local_e0 = (uint)*pbVar3;
  if (local_e0 == 0x85) {
joined_r0x00143898:
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s():Incorrect ScanType!\n","scan_next_channel");
    return 0;
  }
  if ((local_e0 - 7 < 2) && (bVar12 = false, pbVar3[2] != 0)) {
    if (local_e0 == 7) {
      bVar12 = false;
      if (*(char *)(param_2 + 0xbb4) != '\0') {
        bVar12 = 6 < *(byte *)(param_2 + 0xbb5);
      }
    }
    else {
      bVar12 = false;
      if (pbVar3[0x17c] != 0) {
        bVar12 = pbVar3[0x17d] <= *(byte *)(param_2 + 0xbb5);
      }
    }
  }
  iVar10 = IsHcRadioCurStatOffByWdev(param_2);
  if (iVar10 != 0) {
    pbVar3[2] = 0;
LAB_001438d0:
    param_3[1] = bVar12;
    *param_3 = 1;
    scan_ch_restore(param_1,iVar4,param_2);
    ZTE_BStaBeaconProbeRssiReport(param_1,param_2,pbVar3 + 0x1c8);
    if (2 < DebugLevel) {
      printk("%s: Scan complete for band %d channel:%d pending:%d \n","scan_next_channel",
             *(undefined1 *)(param_1 + 0x28608c),pbVar3[2],bVar12);
    }
    pbVar3[0x61] = 0;
    if (*(int *)(pbVar3 + 0x5c) == 2) {
      if (2 < DebugLevel) {
        printk("[%s] in finish path channel no : %d : obss time :%d channel_idx = %d\n",
               "scan_next_channel",*(undefined4 *)(param_1 + 0x286074),
               *(undefined4 *)(param_1 + 0x286084),(&DAT_0036b861)[param_1]);
      }
      local_a3 = (&DAT_0036b861)[param_1];
      local_cb = *(undefined4 *)(pbVar3 + 0x2a);
      local_8b = pbVar3[0x78];
      local_c7 = *(undefined4 *)(pbVar3 + 0x2e);
      local_90 = *(undefined4 *)(param_1 + (local_a3 + 0xa1824) * 4 + 4);
      local_c3 = *(undefined4 *)(pbVar3 + 0x32);
      local_bf = *(undefined4 *)(pbVar3 + 0x36);
      local_cc = 0x23;
      local_a0 = *(undefined4 *)(param_1 + 0x286088);
      local_98 = *(undefined4 *)(param_1 + 0x286080);
      local_9c = *(undefined4 *)(param_1 + 0x28607c);
      local_a4 = (undefined1)*(undefined4 *)(param_1 + 0x286074);
      local_94 = *(undefined4 *)(param_1 + 0x286084);
      RtmpOSWrielessEventSend(*(undefined4 *)(param_1 + 4),1,0x955,0,&local_cc,0xa4);
      *(undefined1 *)(param_1 + 0xa7c349) = 1;
      bVar1 = pbVar3[0x54];
      pbVar3[bVar1 + 0x4f] = 0;
      pbVar3[0x5c] = 0;
      pbVar3[0x5d] = 0;
      pbVar3[0x5e] = 0;
      pbVar3[0x5f] = 0;
      pbVar3[0x55] = 0;
      pbVar3[bVar1 + 0x4a] = 0;
      pbVar3[0x54] = 0;
    }
    if ((bVar12 == false) && (*(undefined1 *)(param_2 + 0xbb6) = 0, local_e0 == 8)) {
      pbVar3[0x17c] = 0;
      if (*(int *)(pbVar3 + 0x184) == 0) {
        pbVar3[0x1bc] = 0;
        pbVar3[0x1bd] = 0;
        pbVar3[0x1be] = 0;
        pbVar3[0x1bf] = 0;
      }
      else {
        RTMPSetTimer(pbVar3 + 0x188);
      }
    }
    iVar4 = DebugLevel;
    pbVar3[0x61] = 0;
    if (iVar4 < 3) {
      if (*(int *)(pbVar3 + 0x5c) != 2) {
        return 1;
      }
    }
    else {
      printk("%s: Scan complete  \n","scan_next_channel");
      if (*(int *)(pbVar3 + 0x5c) != 2) {
        return 1;
      }
      if (2 < DebugLevel) {
        printk("[%s] in finish path channel no : %d : obss time :%d channel_idx = %d\n",
               "scan_next_channel",*(undefined4 *)(param_1 + 0x286074),
               *(undefined4 *)(param_1 + 0x286084),(&DAT_0036b861)[param_1]);
      }
    }
    local_a3 = (&DAT_0036b861)[param_1];
    local_cb = *(undefined4 *)(pbVar3 + 0x2a);
    local_c7 = *(undefined4 *)(pbVar3 + 0x2e);
    local_90 = *(undefined4 *)(param_1 + (local_a3 + 0xa1824) * 4 + 4);
    local_bf = *(undefined4 *)(pbVar3 + 0x36);
    local_c3 = *(undefined4 *)(pbVar3 + 0x32);
    local_cc = 0x23;
    local_8b = pbVar3[0x78];
    local_a0 = *(undefined4 *)(param_1 + 0x286088);
    local_98 = *(undefined4 *)(param_1 + 0x286080);
    local_9c = *(undefined4 *)(param_1 + 0x28607c);
    local_94 = *(undefined4 *)(param_1 + 0x286084);
    local_a4 = (undefined1)*(undefined4 *)(param_1 + 0x286074);
    RtmpOSWrielessEventSend(*(undefined4 *)(param_1 + 4),1,0x955,0,&local_cc,0xa4);
    *(undefined1 *)(param_1 + 0xa7c349) = 1;
    bVar1 = pbVar3[0x54];
    pbVar3[bVar1 + 0x4f] = 0;
    pbVar3[0x54] = bVar1 + 1;
    pbVar3[0x5c] = 0;
    pbVar3[0x5d] = 0;
    pbVar3[0x5e] = 0;
    pbVar3[0x5f] = 0;
    return 1;
  }
  bVar8 = bVar12;
  if (pbVar3[2] == 0) {
    bVar8 = true;
  }
  if (bVar8 != false) goto LAB_001438d0;
  *(byte *)(param_2 + 0xbb6) = pbVar3[2];
  if (iVar4 == 0) {
    HcCrossChannelCheck(param_1,param_2,pbVar3[2]);
  }
  if (*(int *)(pbVar3 + 0x5c) == 1) {
    if (2 < DebugLevel) {
      printk("%s : Performing Scan Without changing BW\n","scan_next_channel");
    }
    uVar2 = wlan_operate_get_prim_ch(param_2);
    *(undefined1 *)(param_2 + 0x902) = uVar2;
    wlan_operate_set_prim_ch(param_2,pbVar3[2]);
  }
  else {
    if (2 < DebugLevel) {
      printk("%s Performing Scan in 20 Mhz\n","scan_next_channel");
    }
    wlan_operate_scan(param_2,pbVar3[2]);
  }
  iVar10 = get_scan_ctrl_by_wdev(param_1,param_2);
  iVar5 = HcGetBandByWdev(param_2);
  iVar6 = CHAN_PropertyCheck(param_1,*(undefined1 *)(iVar10 + 2),2);
  if (iVar6 == 1) {
    local_e0 = 0x80;
    if (*(byte *)(iVar10 + 2) < 0xf) {
      uVar7 = 0x5a;
    }
    else {
      uVar7 = 0x6e;
    }
  }
  else {
    uVar7 = 0x5a;
  }
  if (iVar10 + 0x148 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s():ScanTimer not assigned!\n","scan_type_stay_time_checker");
    goto joined_r0x00143898;
  }
  if (*(char *)(iVar10 + 0x1c0) != '\0') {
    if (*(byte *)(iVar10 + 2) < 0xf) {
      uVar11 = *(ushort *)(iVar10 + 0x1c4);
    }
    else {
      uVar11 = *(ushort *)(iVar10 + 0x1c2);
    }
    if (uVar11 != 0) goto LAB_00143784;
  }
  if (local_e0 == 2) {
    uVar11 = 0x1e;
  }
  else if ((&DAT_0036b824)[param_1 + iVar5] == '\x01') {
    uVar11 = 400;
  }
  else if (((*(ushort *)(param_2 + 0x18) & 0x4e) == 0) ||
          ((*(ushort *)(param_2 + 0x18) & 0xb1) == 0)) {
    uVar11 = 0x8c;
  }
  else {
    uVar11 = uVar7;
    if (*(byte *)(iVar10 + 2) < 0xf) {
      uVar11 = 0x6e;
    }
  }
  if (*(int *)(iVar10 + 0x5c) == 1) {
    if (DebugLevel < 3) {
      uVar11 = (ushort)*(byte *)(iVar10 + (uint)*(byte *)(iVar10 + 0x54) + 0x4f);
      *(undefined1 *)(iVar10 + 0x60) = 1;
      *(undefined1 *)(iVar10 + 0x61) = 1;
    }
    else {
      printk("offchannel scan setting stay time current state = %d\n");
      uVar9 = (uint)*(byte *)(iVar10 + 0x54);
      iVar6 = iVar10 + uVar9;
      if (DebugLevel < 3) {
        uVar9 = *(uint *)(iVar10 + 0x5c);
      }
      uVar11 = (ushort)*(byte *)(iVar6 + 0x4f);
      if (2 < DebugLevel) {
        printk("[%s][%d] stay time configured of channel index = %d time = %d\n",
               "scan_type_stay_time_checker",800,uVar9,uVar11);
        uVar9 = *(uint *)(iVar10 + 0x5c);
      }
      *(undefined1 *)(iVar10 + 0x60) = 1;
      *(undefined1 *)(iVar10 + 0x61) = 1;
      if (uVar9 != 1) goto LAB_00143784;
    }
    ktime_get(&local_d8);
    *(undefined4 *)(iVar10 + 0x68) = local_d8;
    *(undefined4 *)(iVar10 + 0x6c) = uStack_d4;
    AsicGetChBusyCnt(param_1,0,0,0);
    AsicGetCCACnt(param_1,iVar5);
  }
  else {
    *(undefined1 *)(iVar10 + 0x60) = 1;
    *(undefined1 *)(iVar10 + 0x61) = 1;
  }
LAB_00143784:
  RTMPSetTimer(iVar10 + 0x148,uVar11);
  if (2 < DebugLevel) {
    printk("SYNC - %s:[%d], stay_time:%d\n","scan_type_stay_time_checker",0x331,uVar11);
  }
  *(char *)(param_2 + 0xbb5) = *(char *)(param_2 + 0xbb5) + '\x01';
  if ((local_e0 & 0x80) != 0) {
    return 1;
  }
  iVar10 = FUN_00142a84(param_1,iVar4,local_e0,param_2);
  if (iVar10 == 0) {
    return 0;
  }
  if ((*(byte *)(param_1 + 0x286294) & 3) == 3) {
    if (*(int *)(param_2 + 0x14) != 2) {
      return 1;
    }
    iVar10 = param_1 + (uint)*(byte *)(param_2 + 0xe) * 0x2137b0;
    if ((&DAT_00580e5a)[iVar10] != '\0') {
      if ((&DAT_00580ee8)[iVar10] != '\0') {
        scan_extra_probe_req
                  (param_1,iVar4,local_e0,param_2,
                   (uint)*(byte *)(param_2 + 0xe) * 0x2137b0 + param_1 + 0x580e3a,
                   (&DAT_00580e5a)[iVar10]);
        return 1;
      }
      return 1;
    }
    return 1;
  }
  return 1;
}

