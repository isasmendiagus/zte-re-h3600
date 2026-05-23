// module: mt7915.ko
// function: SetATEConTxETxBfGdProc @ 0x26b650
// size: 1968 bytes
//

undefined4 SetATEConTxETxBfGdProc(int param_1,char *param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  size_t sVar5;
  int iVar6;
  char cVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  uint local_a4;
  uint local_a0;
  undefined4 local_9c;
  undefined1 local_90;
  undefined1 local_8c;
  undefined4 local_7c;
  char acStack_78 [84];
  
  iVar2 = net_ad_wrap_service();
  cVar7 = '\0';
  uVar14 = (uint)*(byte *)(iVar2 + 0x4cc);
  local_7c = 0;
  iVar2 = net_ad_wrap_service(param_1);
  iVar3 = net_ad_wrap_service(param_1);
  iVar4 = net_ad_wrap_service(param_1);
  if (param_2 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters!!\n","SetATEConTxETxBfGdProc");
    }
    return 0;
  }
  sVar5 = strlen(param_2);
  if (sVar5 != 0x12) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Wrong parameter format!!\n","SetATEConTxETxBfGdProc");
    return 0;
  }
  iVar6 = rstrtok(param_2,&_LC2);
  if (iVar6 == 0) {
    local_a8 = 1;
    iVar11 = 0;
    local_b0 = 0;
    local_ac = 0;
    local_a4 = 0;
    local_a0 = 0;
    local_9c = 0;
    local_8c = 0;
    bVar1 = false;
  }
  else {
    local_a0 = 0;
    local_9c = 0;
    iVar11 = 0;
    local_a4 = 0;
    local_ac = 0;
    local_b0 = 0;
    local_a8 = 1;
    do {
      switch(cVar7) {
      case '\0':
        local_b0 = simple_strtol(iVar6,0,10);
        break;
      case '\x01':
        local_ac = simple_strtol(iVar6,0,10);
        break;
      case '\x02':
        iVar11 = simple_strtol(iVar6,0,10);
        break;
      case '\x03':
        local_9c = simple_strtol(iVar6,0,10);
        break;
      case '\x04':
        local_a4 = simple_strtol(iVar6,0,10);
        local_a4 = local_a4 & 0xff;
        break;
      case '\x05':
        local_a0 = simple_strtol(iVar6,0,10);
        local_a0 = local_a0 & 0xff;
        break;
      default:
        if (DebugLevel < 0) {
          local_a8 = 0;
        }
        else {
          local_a8 = 0;
          printk("%s: Set wrong parameters\n","SetATEConTxETxBfGdProc");
        }
      }
      cVar7 = cVar7 + '\x01';
      iVar6 = rstrtok(0,&_LC2);
    } while (iVar6 != 0);
    bVar1 = iVar11 == 3 || iVar11 == 6;
    local_8c = (undefined1)local_9c;
  }
  if (-1 < DebugLevel) {
    printk("%s:  TxMode = %d, MCS = %d, BW = %d, Channel = %d, Channel2 = %d, Channl_band = %d\n",
           "SetATEConTxETxBfGdProc",local_b0,local_ac,iVar11,local_9c,local_a4,local_a0);
  }
  iVar6 = jiffies;
  iVar12 = uVar14 * 0xd18;
  iVar10 = iVar2 + iVar12;
  iVar8 = iVar3 + iVar12;
  iVar13 = iVar4 + iVar12;
  SetATE(param_1,"ATEAP");
  SetATE(param_1,"ATESTART");
  os_move_mem((void *)(iVar10 + 0x531),&Addr2,6);
  iVar9 = param_1 + 0xa77bb4;
  snprintf(acStack_78,0x50,"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",(uint)*(byte *)(iVar2 + iVar12 + 0x531),
           (uint)*(byte *)(iVar10 + 0x532),(uint)*(byte *)(iVar10 + 0x533),
           (uint)*(byte *)(iVar10 + 0x534),(uint)*(byte *)(iVar10 + 0x535),
           (uint)*(byte *)(iVar10 + 0x536));
  SetATEDaByWtblTlv(param_1,acStack_78);
  os_move_mem((void *)(iVar8 + 0x591),&Addr1,6);
  os_move_mem((void *)(iVar13 + 0x5f1),&Addr3,6);
  snprintf(acStack_78,0x50,"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",0,
           (uint)*(byte *)(iVar3 + iVar12 + 0x591),(uint)*(byte *)(iVar8 + 0x592),
           (uint)*(byte *)(iVar8 + 0x593),(uint)*(byte *)(iVar8 + 0x594),
           (uint)*(byte *)(iVar8 + 0x595),(uint)*(byte *)(iVar8 + 0x596),uVar14);
  Set_DevInfoUpdate(param_1,acStack_78);
  snprintf(acStack_78,0x50,"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",0,uVar14,
           (uint)*(byte *)(iVar4 + iVar12 + 0x5f1),(uint)*(byte *)(iVar13 + 0x5f2),
           (uint)*(byte *)(iVar13 + 0x5f3),(uint)*(byte *)(iVar13 + 0x5f4),
           (uint)*(byte *)(iVar13 + 0x5f5),(uint)*(byte *)(iVar13 + 0x5f6));
  Set_BssInfoUpdate(param_1,acStack_78);
  snprintf(acStack_78,0x50,"%d",local_b0);
  mt_agent_cli_set_dw("ATETXMODE",iVar9,acStack_78);
  snprintf(acStack_78,0x50,"%d",local_ac);
  mt_agent_cli_set_dw("ATETXMCS",iVar9,acStack_78);
  snprintf(acStack_78,0x50,"%d:%d",iVar11,iVar11);
  mt_agent_cli_set_ext("ATETXBW",iVar9,acStack_78);
  mt_agent_cli_set_dw("ATETXGI",iVar9,&_LC326);
  if (((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) &&
     (*(char *)(param_1 + 0x79504d) != '\0')) {
    if (uVar14 == 1) {
      if (bVar1) {
        mt_agent_cli_set_ext("ATETXANT",iVar9,&_LC428);
        mt_agent_cli_set_ext("ATERXANT",iVar9,&_LC428);
      }
      else {
        mt_agent_cli_set_ext("ATETXANT",iVar9,&_LC434);
        mt_agent_cli_set_ext("ATERXANT",iVar9,&_LC434);
      }
      goto LAB_0026ba80;
    }
    if (bVar1) {
      mt_agent_cli_set_ext("ATETXANT",iVar9,&_LC426);
      mt_agent_cli_set_ext("ATERXANT",iVar9,&_LC426);
      goto LAB_0026ba80;
    }
  }
  else if (bVar1) {
    mt_agent_cli_set_ext("ATETXANT",iVar9,&_LC458);
    mt_agent_cli_set_ext("ATERXANT",iVar9,&_LC458);
    goto LAB_0026ba80;
  }
  mt_agent_cli_set_ext("ATETXANT",iVar9,&_LC332);
  mt_agent_cli_set_ext("ATERXANT",iVar9,&_LC332);
LAB_0026ba80:
  if (0 < DebugLevel) {
    printk("%s: SetATETxBfGdInitProc Time consumption : %lu sec\n","SetATEConTxETxBfGdProc",
           (uint)((jiffies - iVar6) * 1000) / 100);
  }
  phy_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x10280,0x8001);
  phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x10280,&local_7c);
  if (0 < DebugLevel) {
    printk("%s: <0x82070280> = 0x%x\n","SetATEConTxETxBfGdProc",local_7c);
  }
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar2 + uVar14 * 0xd18 + 0x1130) = local_8c;
  iVar2 = net_ad_wrap_service(param_1);
  local_90 = (undefined1)local_a4;
  *(undefined1 *)(iVar2 + uVar14 * 0xd18 + 0x1143) = local_90;
  snprintf(acStack_78,0x50,"%d:%d:0:%d",local_9c,local_a0,local_a4);
  mt_agent_cli_set_ext("ATECHANNEL",iVar9,acStack_78);
  SetATE(param_1,"TXCOMMIT");
  RtmpOsMsDelay(1000);
  SetATE(param_1,"RXFRAME");
  MtATESetMacTxRx(param_1,6,1,uVar14);
  MtATESetMacTxRx(param_1,1,1,uVar14);
  return local_a8;
}

