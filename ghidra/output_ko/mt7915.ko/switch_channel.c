// module: mt7915.ko
// function: switch_channel @ 0x17f150
// size: 444 bytes
//

void switch_channel(int param_1,uint param_2,undefined4 param_3,uint param_4,undefined4 param_5,
                   undefined4 param_6)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char cStack_a;
  undefined1 uStack_9;
  char local_6;
  undefined2 local_4;
  
  cStack_a = (char)(param_2 >> 0x10);
  uVar3 = param_4 & 0xff;
  local_4._1_1_ = (char)(param_4 >> 8);
  cVar1 = local_4._1_1_;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uStack_9 = (undefined1)(param_2 >> 0x18);
  *(undefined1 *)(iVar2 + 0x224) = uStack_9;
  MtPwrLimitTblChProc(param_1,uVar3,local_4._1_1_,param_2 & 0xff,cStack_a);
  mt7915_apply_dpd_flatness_data(param_1,param_2,param_3,param_4,param_5,param_6);
  if (*(char *)(param_1 + 0x79504d) != '\x01') {
LAB_0017f1d4:
    MtCmdChannelSwitch(param_1,param_2,param_3,param_4,param_5,param_6);
    MtCmdSetTxRxPath(param_1,param_2,param_3,param_4,param_5,param_6);
    "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x20] = cStack_a;
    local_6 = (char)((uint)param_3 >> 0x10);
    if (local_6 != '\0') {
      return;
    }
    ZTE_wlan_edcca_setting(param_1,uVar3);
    return;
  }
  if (local_4._1_1_ == '\0' || uVar3 != 0) {
    local_4 = (short)param_4;
    if (local_4 != 1) goto LAB_0017f1d4;
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC361,"switch_channel",uVar3);
    if (DebugLevel < 0) {
      return;
    }
  }
  else {
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC359,"switch_channel",0);
    if (DebugLevel < 0) {
      return;
    }
    uVar3 = 0;
  }
  printk(&_LC360,"switch_channel",uVar3,cVar1);
  return;
}

