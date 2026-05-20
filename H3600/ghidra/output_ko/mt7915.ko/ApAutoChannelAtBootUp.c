// module: mt7915.ko
// function: ApAutoChannelAtBootUp @ 0x10114
// size: 1120 bytes
//

undefined4 ApAutoChannelAtBootUp(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  bool bVar5;
  undefined1 local_29 [5];
  
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk(&_LC3,"ApAutoChannelAtBootUp");
    if (0 < DebugLevel) {
      printk("%s<-----------------\n","ApAutoChannelAtBootUp");
      return 0;
    }
    return 0;
  }
  iVar1 = wlan_config_get_vht_bw(param_2);
  if (0 < DebugLevel) {
    printk("%s----------------->\n","ApAutoChannelAtBootUp");
  }
  iVar2 = HcGetBandByWdev(param_2);
  if (0 < DebugLevel) {
    printk("%s: AutoChannelBootup[%d] = %d\n","ApAutoChannelAtBootUp",iVar2,
           (&DAT_0036b824)[param_1 + iVar2]);
  }
  iVar3 = HcGetAutoChCtrlbyBandIdx(param_1,iVar2);
  RTMPEnableRxTx(param_1);
  if (2 < DebugLevel) {
    printk("%s: PhyMode: %d\n","ApAutoChannelAtBootUp",*(undefined2 *)(param_2 + 0x18));
  }
  bVar5 = (*(ushort *)(param_2 + 0x18) & 0xb1) != 0;
  if (*(char *)(param_2 + 0x1a) == '\0') {
    if ((&DAT_0036b824)[param_1 + iVar2] == '\0') {
      if (DebugLevel < 1) {
        return 0;
      }
      printk("%s<-----------------\n","ApAutoChannelAtBootUp");
      return 0;
    }
    if (*(int *)(iVar3 + 0x10) == 1) {
      local_29[0] = *(undefined1 *)(iVar3 + 0xd);
      if (0 < DebugLevel) {
        printk("[ApAutoChannelAtBootUp] ACS of BandIdx = %d is already DONE, Channel = %d\n",iVar2);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0xa7c349) = 0;
      *(undefined1 *)(param_1 + iVar2 + 0xa7c304) = 0;
      uVar4 = APAutoSelectChannel(param_1,param_2,*(undefined4 *)(param_1 + (iVar2 + 0xdae0a) * 4),
                                  bVar5);
      local_29[0] = (undefined1)uVar4;
      if (0 < DebugLevel) {
        printk("%s : Auto channel selection: Selected channel = %d, IsAband = %d\n",
               "ApAutoChannelAtBootUp",uVar4,bVar5);
      }
    }
    zero_wait_dfs_update_ch(param_1,param_2,local_29);
    AutoChSelUpdateChannel(param_1,local_29[0],bVar5,param_2);
    *(undefined1 *)(param_1 + 0xa7c349) = 1;
    *(undefined1 *)(param_1 + iVar2 + 0xa7c304) = 1;
    if (!bVar5) goto LAB_00010264;
  }
  else {
    if (*(char *)(param_1 + 0x795404) == '\0') {
      if (DebugLevel < 3) {
        return 0;
      }
      printk("%s(): zero-wait DFS is not enabled\n","ApAutoChannelAtBootUp");
      return 0;
    }
    if (!bVar5) {
      if (DebugLevel < 1) {
        return 0;
      }
      printk("%s(): not A band\n","ApAutoChannelAtBootUp");
      return 0;
    }
    iVar3 = zero_wait_dfs_update_ch(param_1,param_2,param_2 + 0x1a);
    if (iVar3 == 0) {
      zero_wait_dfs_switch_ch(param_1,param_2,2);
      if (DebugLevel < 1) {
        return 0;
      }
      printk("%s<-------\n","ApAutoChannelAtBootUp");
      return 0;
    }
    if (0 < DebugLevel) {
      printk("%s(): DFS ch %d is set, use non-DFS ch %d\n","ApAutoChannelAtBootUp",
             *(undefined1 *)(param_1 + 0x7953fb),*(undefined1 *)(param_2 + 0x1a));
    }
    AutoChSelUpdateChannel(param_1,*(undefined1 *)(param_2 + 0x1a),1,param_2);
  }
  RadarStateCheck(param_1,param_2);
LAB_00010264:
  if ((&DAT_0036b824)[param_1 + iVar2] == '\x01' && iVar1 == 3) {
    wlan_config_set_cen_ch_2(param_2,*(undefined1 *)(param_2 + 0x3fe1));
    wlan_operate_set_cen_ch_2(param_2,*(undefined1 *)(param_2 + 0x3fe1));
  }
  wdev_sync_prim_ch(param_1,param_2);
  wlan_operate_set_prim_ch(param_2,*(undefined1 *)(param_2 + 0x1a));
  DfsBuildChannelList(param_1,param_2);
  zero_wait_dfs_switch_ch(param_1,param_2,2);
  if (0 < DebugLevel) {
    printk("%s<-----------------\n","ApAutoChannelAtBootUp");
  }
  return 1;
}

