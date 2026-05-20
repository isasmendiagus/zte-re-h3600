// module: mt7915.ko
// function: PeerPairMsg4Action @ 0x120c84
// size: 1408 bytes
//

void PeerPairMsg4Action(int param_1,int param_2,uint *param_3,int param_4)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined1 *puVar8;
  uint uVar9;
  undefined1 uStack_a1;
  undefined1 auStack_a0 [20];
  char local_8c [8];
  uint local_84;
  undefined2 local_80;
  undefined4 local_7e;
  undefined2 local_7a;
  undefined1 local_78;
  undefined1 local_77;
  undefined1 local_76;
  undefined1 local_75;
  undefined1 local_74;
  undefined1 local_73;
  
  log_time_begin(1,auStack_a0);
  if (2 < DebugLevel) {
    printk("===> %s\n","PeerPairMsg4Action");
  }
  if ((byte)param_3[0xe6] < 9) {
    return;
  }
  if ((byte)param_3[0xe6] == 10) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: reject the Replayed Msg4\n","PeerPairMsg4Action");
    return;
  }
  if ((*(byte *)(param_4 + 1) & 3) == 3) {
    iVar6 = 0x1e;
    uVar2 = 0x89;
  }
  else {
    iVar6 = 0x18;
    uVar2 = 0x83;
  }
  if (*(uint *)(param_4 + 0x908) < uVar2) {
    return;
  }
  puVar8 = (undefined1 *)((int)param_3 + 0x1ce);
  iVar6 = WpaMessageSanity(param_1,param_4 + iVar6 + 8,(*(uint *)(param_4 + 0x908) - 8) - iVar6,4,
                           param_3,param_2,puVar8);
  if (iVar6 == 0) {
    return;
  }
  bVar1 = *(byte *)(param_2 + 0xe4);
  uVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar2 <= bVar1) {
    return;
  }
  if (0x1f < *(byte *)(param_2 + 0xe4)) {
    return;
  }
  RTMPCancelTimer(param_3 + 0xe9,&uStack_a1);
  uVar2 = (uint)*(ushort *)(param_2 + 0xe0);
  *(undefined4 *)(param_2 + 0xadc) = 0;
  *(undefined1 *)((int)param_3 + 0x399) = 1;
  *(undefined1 *)(param_3 + 0xe6) = 10;
  *(undefined1 *)(param_1 + uVar2 * 0x620 + 0x2f762) = 1;
  ZTE_Notify_Node_AD(1,param_2);
  __ZTE_STA_Assoc_Process(param_1,8,0,0,0,0,param_2,"PeerPairMsg4Action",0x177b);
  if ((&DAT_0036b920)[param_1] != '\0') {
    BndStrg_NotifyStaConnectedMsg(param_1,param_2);
  }
  WifiSysUpdatePortSecur(param_1,param_2,0);
  if (2 < DebugLevel) {
    printk("===> WifiSysUpdatePortSecur called by (%s), wcid=%d, PortSecured=%d\n",
           "PeerPairMsg4Action",*(undefined2 *)(param_2 + 0xe0),2);
  }
  if (*(int *)(
              "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
              + (uint)*(byte *)(param_2 + 0xe4) * 0x5834 + param_1 + 0x2b) != 0) {
    WscInformFromWPA(param_2);
  }
  uVar9 = *param_3;
  if ((uVar9 & 0x120c0) == 0) {
    RTMPSetTimer(param_2 + 0x438,500);
    goto LAB_00120ef4;
  }
  if ((uVar9 & 0x10040) == 0) {
    if ((uVar9 & 0x2000) != 0) {
      set_sae_instance_removable("pci_sw_int_handler" + param_1,param_3 + 0xc9,(int)param_3 + 0x32a)
      ;
    }
  }
  else {
    local_7e = *(undefined4 *)((int)param_3 + 0x32a);
    builtin_strncpy(local_8c,"PMK Name",8);
    local_84 = param_3[0xc9];
    local_7a = *(undefined2 *)((int)param_3 + 0x32e);
    local_80 = (undefined2)param_3[0xca];
    if (((uVar9 & 0x30000) == 0) && ((char)param_3[0xa1] != '\x02')) {
      RT_HMAC_SHA1((int)param_3 + 0x18e,0x20,local_8c,0x14,&local_78,0x14);
      uVar3 = 0x20;
    }
    else {
      RT_HMAC_SHA384((int)param_3 + 0x18e,0x30,local_8c,0x14,&local_78,0x10);
      uVar3 = 0x30;
    }
    RTMPAddPMKIDCache(&DAT_003687fc + param_1,*(undefined1 *)(param_2 + 0xe4),
                      (undefined4 *)((int)param_3 + 0x32a),&local_78,(int)param_3 + 0x18e,uVar3);
    if (2 < DebugLevel) {
      printk("Calc PMKID=%02x:%02x:%02x:%02x:%02x:%02x\n",local_78,local_77,local_76,local_75,
             local_74,local_73);
    }
  }
  if (*(char *)(param_1 + uVar2 * 0x620 + 0x2f762) == '\x01') {
    MWDSAPPeerEnable(param_1,param_2);
  }
  if ((*(char *)(param_1 + 0x286285) == '\x01') && (*(char *)(param_2 + 0x13b0) == '\x01')) {
    iVar6 = *(int *)(param_2 + 0x13b8);
    Send_BTM_Req(param_1,iVar6 + 4,iVar6 + 0xe,*(undefined4 *)(iVar6 + 10));
    *(undefined1 *)(param_2 + 0x13b0) = 0;
    os_free_mem(iVar6);
    if (0 < DebugLevel) {
      printk("!!!!msg 4 send btm req\n");
      goto LAB_00120ebc;
    }
  }
  else {
LAB_00120ebc:
    if (0 < DebugLevel) {
      uVar7 = **(undefined4 **)(param_2 + 8);
      uVar3 = GetAuthModeStr(*param_3);
      uVar4 = GetEncryModeStr(param_3[0x52]);
      uVar5 = GetEncryModeStr(param_3[0x8a]);
      printk("AP SETKEYS DONE(%s) - AKMMap=%s, PairwiseCipher=%s, GroupCipher=%s, wcid=%d from %02x:%02x:%02x:%02x:%02x:%02x\n\n"
             ,uVar7,uVar3,uVar4,uVar5,*(undefined2 *)(param_2 + 0xe0),
             *(undefined1 *)(param_2 + 0xec),*(undefined1 *)(param_2 + 0xed),
             *(undefined1 *)(param_2 + 0xee),*(undefined1 *)(param_2 + 0xef),
             *(undefined1 *)(param_2 + 0xf0),*(undefined1 *)(param_2 + 0xf1));
    }
  }
  if (((*param_3 & 1) == 0) && (*(char *)(param_1 + uVar2 * 0x620 + 0x2f762) == '\x01')) {
    if (0 < DebugLevel) {
      printk(&_LC187);
    }
    iVar6 = DebugLevel;
    do {
      if (0 < iVar6) {
        printk(&_LC188,*puVar8);
        iVar6 = DebugLevel;
      }
      puVar8 = puVar8 + 1;
    } while (puVar8 != (undefined1 *)((int)param_3 + 0x20e));
    if (0 < iVar6) {
      printk(&_LC189);
    }
  }
LAB_00120ef4:
  log_time_end(2,"peer_msg4",1,auStack_a0);
  return;
}

