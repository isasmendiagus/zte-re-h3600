// module: mt7915.ko
// function: SetATETxBfDutInitProc @ 0x2698e4
// size: 1812 bytes
//

undefined4 SetATETxBfDutInitProc(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  char acStack_40 [28];
  
  iVar1 = net_ad_wrap_service();
  uVar9 = (uint)*(byte *)(iVar1 + 0x4cc);
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = net_ad_wrap_service(param_1);
  iVar7 = *(int *)(uVar9 * 0xd18 + iVar1 + 0x504);
  uVar3 = simple_strtol(param_2,0,10);
  iVar1 = jiffies;
  SetATE(param_1,"ATESTART");
  if (((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) &&
     (SetATE(param_1,"ATEAP"), "Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] == '\0')) {
    set_ate_tx_policy(param_1,&_LC418);
  }
  iVar4 = net_ad_wrap_service(param_1);
  iVar8 = uVar9 * 0xd18;
  *(undefined1 *)(iVar4 + iVar8 + 0x531) = 0;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x532) = 0x11;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x533) = 0x11;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x534) = 0x11;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x535) = 0x11;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x536) = 0x11;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x531) = 0;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x532) = 0x11;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x533) = 0x11;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x534) = 0x11;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x535) = 0x11;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x536) = 0x11;
  if ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] == '\0') {
    snprintf(acStack_40,0x18,"4-00:%.2x:%.2x:%.2x:%.2x:%.2x",0x11,0x11,0x11,0x11,0x11);
  }
  else {
    snprintf(acStack_40,0x18,"00:%.2x:%.2x:%.2x:%.2x:%.2x",0x11,0x11,0x11,0x11,0x11);
  }
  SetATEDaByWtblTlv(param_1,acStack_40);
  iVar4 = net_ad_wrap_service(param_1);
  iVar8 = uVar9 * 0xd18;
  *(undefined1 *)(iVar4 + iVar8 + 0x591) = 0;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x592) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x593) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x594) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x595) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x596) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x591) = 0;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x592) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x593) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x594) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x595) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x596) = 0x22;
  uVar5 = HcGetOmacIdx(param_1,iVar7);
  iVar4 = net_ad_wrap_service(param_1);
  AsicDevInfoUpdate(param_1,uVar5,iVar4 + iVar8 + 0x591,uVar9,1,1);
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x5f1) = 0;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x5f2) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x5f3) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x5f4) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x5f5) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + iVar8 + 0x5f6) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x5f1) = 0;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x5f2) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x5f3) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x5f4) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x5f5) = 0x22;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + 0x5f6) = 0x22;
  uVar5 = HcGetOmacIdx(param_1,iVar7);
  snprintf(acStack_40,0x18,"%.2x:%.2x:00:%.2x:%.2x:%.2x:%.2x:%.2x",uVar5,
           (uint)*(byte *)(iVar7 + 0x999),0x22,0x22,0x22,0x22,0x22);
  if (0 < DebugLevel) {
    uVar5 = HcGetOmacIdx(param_1,iVar7);
    printk("%s: ownmac ID = %d, BSS index = %d\n","SetATETxBfDutInitProc",uVar5,
           *(undefined1 *)(iVar7 + 0x999));
  }
  iVar7 = param_1 + 0xa77bb4;
  Set_BssInfoUpdate(param_1,acStack_40);
  mt_agent_cli_set_dw("ATETXMODE",iVar7,&_LC423);
  mt_agent_cli_set_ext("ATETXBW",iVar7,&_LC326);
  mt_agent_cli_set_dw("ATETXGI",iVar7,&_LC326);
  SetATEIpg(param_1,&_LC425);
  SetATETXBFProc(param_1,&_LC426);
  if ((uVar3 & 1) == 0) {
    bVar6 = (byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4;
    if (*(char *)(param_1 + 0x79504d) != '\0') {
      if (uVar9 == 0) {
        bVar6 = "SetPartProfileParameters"[param_1 + 0x1a];
      }
      else {
        bVar6 = "rtmp_read_vow_parms_from_file"[param_1];
      }
    }
    if (bVar6 == 2) {
      mt_agent_cli_set_ext("ATETXANT",iVar7,&_LC426);
      mt_agent_cli_set_ext("ATERXANT",iVar7,&_LC426);
      mt_agent_cli_set_dw("ATETXMCS",iVar7,&_LC427);
    }
    else if (bVar6 == 3) {
      mt_agent_cli_set_ext("ATETXANT",iVar7,&_LC429);
      mt_agent_cli_set_ext("ATERXANT",iVar7,&_LC429);
      mt_agent_cli_set_dw("ATETXMCS",iVar7,&_LC430);
    }
    else {
      mt_agent_cli_set_ext("ATETXANT",iVar7,&_LC427);
      mt_agent_cli_set_ext("ATERXANT",iVar7,&_LC427);
      mt_agent_cli_set_dw("ATETXMCS",iVar7,&_LC431);
    }
  }
  else {
    mt_agent_cli_set_dw("ATETXMCS",iVar7,&_LC427);
    if (((byte)"Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] < 2) && (uVar9 != 0)) {
      mt_agent_cli_set_ext("ATETXANT",iVar7,&_LC428);
      mt_agent_cli_set_ext("ATERXANT",iVar7,&_LC428);
    }
    else {
      mt_agent_cli_set_ext("ATETXANT",iVar7,&_LC426);
      mt_agent_cli_set_ext("ATERXANT",iVar7,&_LC426);
    }
  }
  iVar8 = net_ad_wrap_service(param_1);
  iVar4 = jiffies;
  iVar7 = DebugLevel;
  *(undefined1 *)(uVar9 * 0xd18 + iVar8 + 0x11ce) = 0;
  if (0 < iVar7) {
    printk("%s: Time consumption : %lu sec\n","SetATETxBfDutInitProc",
           (uint)((iVar4 - iVar1) * 1000) / 100);
  }
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    SetATE(param_1,"TXCOMMIT");
  }
  MtATESetMacTxRx(param_1,1,1,uVar9);
  if (*(code **)(iVar2 + 0x13c) != (code *)0x0) {
    (**(code **)(iVar2 + 0x13c))(param_1);
  }
  return 1;
}

