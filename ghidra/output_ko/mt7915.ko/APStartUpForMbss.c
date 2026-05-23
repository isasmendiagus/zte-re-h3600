// module: mt7915.ko
// function: APStartUpForMbss @ 0x10a34
// size: 1180 bytes
//

void APStartUpForMbss(int param_1,int param_2)

{
  undefined1 uVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  ushort uVar7;
  ushort uVar8;
  ushort uVar9;
  int iVar10;
  
  uVar1 = *(undefined1 *)(param_1 + 0x794c48);
  iVar3 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("===> %s(), CfgMode:%d\n","APStartUpForMbss",uVar1);
  }
  iVar4 = HcGetBandByWdev(param_2);
  if (0x1f < *(byte *)(param_2 + 0x4089) - 1) {
    *(undefined4 *)(param_2 + 0x4068) = 0x415f5448;
    *(undefined1 *)(param_2 + 0x406c) = 0x50;
    *(undefined1 *)(param_2 + 0x4089) = 6;
    *(char *)(param_2 + 0x406d) = (char)*(undefined4 *)(param_2 + 0x4060) + '0';
  }
  if (*(char *)(param_2 + 0xe) == '\0') {
    MgmtTableSetMcastEntry(param_1);
  }
  APSecInit(param_1,param_2);
  if (*(char *)(param_2 + 0x3f58) == '\x01') {
    MWDSEnable(param_1,*(undefined1 *)(param_2 + 0x4060),1,1);
  }
  calc_mldv2_gen_query_chksum(param_1,param_2);
  if (*(byte *)(param_2 + 0x1a) < 0xf) {
    uVar6 = 0;
  }
  else {
    uVar6 = *(byte *)(param_1 + 0x795074) - 1;
  }
  if (0xe < *(byte *)(param_2 + 0x1a)) {
    uVar6 = (uint)(uVar6 == 0);
  }
  if (*(int *)(param_2 + 0x2c) == 1) {
    if (*(int *)(param_2 + 0x174) == 1) {
      uVar7 = 1;
    }
    else {
      uVar7 = 0x11;
    }
  }
  else {
    uVar7 = 0x11;
  }
  if (*(int *)(param_1 + 0x795064) == 0) {
    uVar9 = 0;
  }
  else {
    uVar9 = 0x20;
  }
  if (*(char *)(param_1 + 0x795070) == '\0') {
    uVar8 = 0;
  }
  else {
    uVar8 = 0x400;
  }
  uVar7 = uVar9 | uVar7 | uVar8 | (ushort)(uVar6 << 8);
  *(ushort *)(param_2 + 0x408c) = uVar7;
  if (*(char *)(param_2 + 0xb21) == '\x01') {
    *(ushort *)(param_2 + 0x408c) = uVar7 | 0x1000;
  }
  if (*(char *)(param_2 + 0x3e15) == '\0') goto LAB_00010b74;
  if ((*(uint *)(param_2 + 0x174) & 0x1e) == 0) {
    cVar2 = *(char *)(param_2 + 0x408a);
joined_r0x00010dc8:
    if (cVar2 == '\0') {
      WscOnOff(param_1,*(undefined1 *)(param_2 + 0xe));
      goto LAB_00010b74;
    }
  }
  else if (0x1f < *(uint *)(param_2 + 0x174)) {
    cVar2 = *(char *)(param_2 + 0x408a);
    goto joined_r0x00010dc8;
  }
  WscOnOff(param_1,*(undefined1 *)(param_2 + 0xe),1);
LAB_00010b74:
  if ((*(char *)(param_2 + 0x8d4) != '\0') || ((*(ushort *)(param_2 + 0x18) & 0x18) != 0)) {
    iVar10 = param_1 + (uint)*(byte *)(param_2 + 0x8d7) * 0x24;
    if (*(char *)(iVar10 + 0x795084) == '\0') {
      set_default_ap_edca_param(iVar10 + 0x795084);
    }
    pcVar5 = (char *)wlan_config_get_ht_edca(param_2);
    if ((pcVar5 != (char *)0x0) && (*pcVar5 == '\0')) {
      set_default_sta_edca_param();
    }
  }
  BuildChannelList(param_1,param_2);
  RTMPSetPhyMode(param_1,param_2,*(undefined2 *)(param_2 + 0x18));
  RTMPUpdateRateInfo(*(undefined2 *)(param_2 + 0x18),param_2 + 0xade);
  if ((*(ushort *)(param_2 + 0x18) & 0x118) == 0) {
    wlan_config_set_ht_bw(param_2);
    cVar2 = *(char *)(param_1 + 0x795947);
  }
  else {
    cVar2 = *(char *)(param_1 + 0x795947);
  }
  if (cVar2 == '\x01') {
    if (2 < DebugLevel) {
      printk("Disable 20/40 BSSCoex Channel Scan(BssCoex=%d, 40MHzIntolerant=%d)\n",
             *(undefined1 *)(param_1 + 0x79564e));
    }
  }
  else if ((*(char *)(param_1 + 0x79564e) == '\x01') && (0 < DebugLevel)) {
    printk("Enable 20/40 BSSCoex Channel Scan(BssCoex=%d)\n");
  }
  MlmeUpdateTxRates(param_1,0,*(undefined1 *)(param_2 + 0xe));
  if ((*(ushort *)(param_2 + 0x18) & 0x18) != 0) {
    MlmeUpdateHtTxRates(param_1,param_2);
  }
  iVar10 = *(int *)(param_2 + 0x14);
  if (((((iVar10 - 0x10U & 0xffffffef) == 0 || (iVar10 == 1 || iVar10 == 4)) &&
       (*(char *)(param_2 + 0xb1c) != '\0')) && (iVar10 = wdev_do_linkup(param_2,0), iVar10 != 1))
     && (-1 < DebugLevel)) {
    printk("%s: link up fail!!\n","APStartUpForMbss");
  }
  iVar10 = param_1 + iVar4;
  TxPowerSKUCtrl(param_1,*(undefined1 *)(iVar10 + 0x794eaa),iVar4);
  TxPowerBfBackoffCtrl(param_1,*(undefined1 *)(iVar10 + 0x795037),iVar4);
  TxPowerPercentCtrl(param_1,*(undefined1 *)(iVar10 + 0x795035),iVar4);
  TxPowerDropCtrl(param_1,*(undefined1 *)(iVar10 + 0x794cd8),iVar4);
  TxCCKStreamCtrl(param_1,*(undefined1 *)(iVar10 + 0x795039),iVar4);
  if ((iVar3 != 0) && (*(code **)(iVar3 + 0x1f0) != (code *)0x0)) {
    (**(code **)(iVar3 + 0x1f0))(param_1,iVar4);
  }
  hc_set_rrm_init(param_2);
  *(undefined1 *)(param_1 + 0x79540a) = 0;
  vow_mbss_init(param_1,param_2);
  greenap_check_when_ap_bss_change(param_1);
  *(undefined1 *)(param_2 + 0x4c58) = 1;
  muru_update_he_cfg(param_1);
  SrMbssInit(param_1,param_2);
  pp_mbss_init(param_1,param_2);
  Set_CpuUtilEn_Proc(param_1,&_LC24);
  ZTE_wlan_edcca_setting(param_1,iVar4);
  return;
}

