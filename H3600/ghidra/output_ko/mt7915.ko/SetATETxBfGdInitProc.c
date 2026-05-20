// module: mt7915.ko
// function: SetATETxBfGdInitProc @ 0x269ffc
// size: 1596 bytes
//

undefined4 SetATETxBfGdInitProc(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  char acStack_78 [84];
  
  iVar1 = net_ad_wrap_service();
  uVar6 = (uint)*(byte *)(iVar1 + 0x4cc);
  iVar1 = net_ad_wrap_service(param_1);
  iVar4 = *(int *)(uVar6 * 0xd18 + iVar1 + 0x504);
  simple_strtol(param_2,0,10);
  iVar1 = jiffies;
  SetATE(param_1,"ATESTART");
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    SetATE(param_1,"ATEAP");
    if ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] == '\0') {
      set_ate_tx_policy(param_1,&_LC418);
    }
  }
  iVar2 = net_ad_wrap_service(param_1);
  iVar5 = uVar6 * 0xd18;
  *(undefined1 *)(iVar2 + iVar5 + 0x531) = 0;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x532) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x533) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x534) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x535) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x536) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x531) = 0;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x532) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x533) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x534) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x535) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x536) = 0x22;
  if ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] == '\0') {
    snprintf(acStack_78,0x50,"4-00:%.2x:%.2x:%.2x:%.2x:%.2x",0x22,0x22,0x22,0x22,0x22);
  }
  else {
    snprintf(acStack_78,0x50,"00:%.2x:%.2x:%.2x:%.2x:%.2x",0x22,0x22,0x22,0x22,0x22);
  }
  SetATEDaByWtblTlv(param_1,acStack_78);
  iVar2 = net_ad_wrap_service(param_1);
  iVar5 = uVar6 * 0xd18;
  *(undefined1 *)(iVar2 + iVar5 + 0x591) = 0;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x592) = 0x11;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x593) = 0x11;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x594) = 0x11;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x595) = 0x11;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x596) = 0x11;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x591) = 0;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x592) = 0x11;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x593) = 0x11;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x594) = 0x11;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x595) = 0x11;
  iVar5 = net_ad_wrap_service(param_1);
  iVar2 = DebugLevel;
  *(undefined1 *)(iVar5 + 0x596) = 0x11;
  if (0 < iVar2) {
    printk("%s: control_band_idx = %d\n","SetATETxBfGdInitProc",uVar6);
  }
  uVar3 = HcGetOmacIdx(param_1,iVar4);
  iVar5 = uVar6 * 0xd18;
  iVar2 = net_ad_wrap_service(param_1);
  AsicDevInfoUpdate(param_1,uVar3,iVar2 + iVar5 + 0x591,uVar6,1,1);
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x5f1) = 0;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x5f2) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x5f3) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x5f4) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x5f5) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + iVar5 + 0x5f6) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x5f1) = 0;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x5f2) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x5f3) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x5f4) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x5f5) = 0x22;
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + 0x5f6) = 0x22;
  uVar3 = HcGetOmacIdx(param_1,iVar4);
  snprintf(acStack_78,0x50,"%.2x:%.2x:00:%.2x:%.2x:%.2x:%.2x:%.2x",uVar3,
           (uint)*(byte *)(iVar4 + 0x999),0x22,0x22,0x22,0x22,0x22);
  if (0 < DebugLevel) {
    uVar3 = HcGetOmacIdx(param_1,iVar4);
    printk("%s: ownmac ID = %d, BSS index = %d\n","SetATETxBfGdInitProc",uVar3,
           *(undefined1 *)(iVar4 + 0x999));
  }
  iVar4 = param_1 + 0xa77bb4;
  Set_BssInfoUpdate(param_1,acStack_78);
  mt_agent_cli_set_dw("ATETXMODE",iVar4,&_LC423);
  mt_agent_cli_set_dw("ATETXMCS",iVar4,&_LC326);
  mt_agent_cli_set_ext("ATETXBW",iVar4,&_LC326);
  mt_agent_cli_set_dw("ATETXGI",iVar4,&_LC326);
  SetATETxCount(param_1,&_LC326);
  SetATETxLength(param_1,&_LC433);
  if (((byte)"Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] < 2) && (uVar6 != 0)) {
    mt_agent_cli_set_ext("ATETXANT",iVar4,&_LC434);
    mt_agent_cli_set_ext("ATERXANT",iVar4,&_LC434);
  }
  else {
    mt_agent_cli_set_ext("ATETXANT",iVar4,&_LC332);
    mt_agent_cli_set_ext("ATERXANT",iVar4,&_LC332);
  }
  SetATE(param_1,"TXCOMMIT");
  iVar4 = net_ad_wrap_service(param_1);
  iVar4 = uVar6 * 0xd18 + iVar4;
  snprintf(acStack_78,0x50,
           "mac:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x-type:ap-wtbl:1-ownmac:0-mode:aanac-bw:20-nss:1-pfmuId:0\n"
           ,(uint)*(byte *)(iVar4 + 0x531),(uint)*(byte *)(iVar4 + 0x532),
           (uint)*(byte *)(iVar4 + 0x533),(uint)*(byte *)(iVar4 + 0x534),
           (uint)*(byte *)(iVar4 + 0x535),(uint)*(byte *)(iVar4 + 0x536));
  if (0 < DebugLevel) {
    printk(&_LC324,acStack_78);
  }
  ate_set_manual_assoc(param_1,acStack_78);
  MtATESetMacTxRx(param_1,1,1,uVar6);
  if (0 < DebugLevel) {
    printk("%s: Time consumption : %lu sec\n","SetATETxBfGdInitProc",
           (uint)((jiffies - iVar1) * 1000) / 100);
  }
  return 1;
}

