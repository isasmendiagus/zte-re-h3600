// module: mt7915.ko
// function: SetATEConTxETxBfInitProc @ 0x26a63c
// size: 4056 bytes
//

undefined4 SetATEConTxETxBfInitProc(int param_1,char *param_2)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  size_t sVar7;
  int iVar8;
  char *__format;
  int iVar9;
  uint uVar10;
  uint uVar11;
  undefined4 uVar12;
  uint uVar13;
  char cVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  bool bVar18;
  uint uVar19;
  uint local_c8;
  uint local_c4;
  uint local_c0;
  uint local_bc;
  uint local_b8;
  undefined4 local_a8;
  uint local_a0;
  uint local_9c;
  uint local_94;
  uint local_88;
  uint local_80;
  undefined4 local_78;
  undefined4 uStack_74;
  char *pcStack_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  
  iVar4 = net_ad_wrap_service();
  uVar13 = (uint)*(byte *)(iVar4 + 0x4cc);
  iVar4 = net_ad_wrap_service(param_1);
  iVar5 = net_ad_wrap_service(param_1);
  iVar6 = net_ad_wrap_service(param_1);
  if (param_2 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters!!\n","SetATEConTxETxBfInitProc");
    }
    return 0;
  }
  sVar7 = strlen(param_2);
  if (sVar7 != 0x21) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Wrong parameter format!!\n","SetATEConTxETxBfInitProc");
    return 0;
  }
  iVar8 = rstrtok(param_2,&_LC2);
  if (iVar8 == 0) {
    local_a8 = 1;
    cVar3 = '\0';
    local_c8 = 0;
    local_c4 = 0;
    local_c0 = 0;
    local_bc = 0;
    bVar2 = false;
    bVar18 = false;
    bVar1 = false;
    local_a0 = 0;
    local_9c = 0;
    local_94 = 0;
    local_88 = 0;
    local_80 = 0;
  }
  else {
    cVar14 = '\0';
    local_88 = 0;
    local_94 = 0;
    local_9c = 0;
    local_b8 = 0;
    local_c0 = 0;
    local_c4 = 0;
    cVar3 = '\0';
    local_a0 = 0;
    local_bc = 0;
    local_c8 = 0;
    local_a8 = 1;
    do {
      switch(cVar14) {
      case '\0':
        local_c8 = simple_strtol(iVar8,0,10);
        local_c8 = local_c8 & 0xff;
        break;
      case '\x01':
        local_9c = simple_strtol(iVar8,0,10);
        local_9c = local_9c & 0xff;
        break;
      case '\x02':
        local_bc = simple_strtol(iVar8,0,10);
        local_bc = local_bc & 0xff;
        break;
      case '\x03':
        local_a0 = simple_strtol(iVar8,0,10);
        local_a0 = local_a0 & 0xff;
        break;
      case '\x04':
        cVar3 = simple_strtol(iVar8,0,10);
        break;
      case '\x05':
        local_94 = simple_strtol(iVar8,0,10);
        local_94 = local_94 & 0xff;
        break;
      case '\x06':
        local_c4 = simple_strtol(iVar8,0,10);
        local_c4 = local_c4 & 0xff;
        break;
      case '\a':
        local_c0 = simple_strtol(iVar8,0,10);
        local_c0 = local_c0 & 0xff;
        break;
      case '\b':
        local_88 = simple_strtol(iVar8,0,10);
        local_88 = local_88 & 0xff;
        break;
      case '\t':
        local_b8 = simple_strtol(iVar8,0,10);
        local_b8 = local_b8 & 0xffff;
        break;
      default:
        if (DebugLevel < 0) {
          local_a8 = 0;
        }
        else {
          local_a8 = 0;
          printk("%s: Set wrong parameters\n","SetATEConTxETxBfInitProc");
        }
      }
      cVar14 = cVar14 + '\x01';
      iVar8 = rstrtok(0,&_LC2);
    } while (iVar8 != 0);
    bVar18 = (local_c8 - 4 & 0xfb) == 0;
    local_80 = local_b8;
    bVar1 = local_c8 == 4;
    bVar2 = local_c8 == 8;
  }
  if (((-1 < DebugLevel) &&
      (printk("%s: TxMode = %d, MCS = %d, BW = %d, VhtNss = %d, TRxStream = %d\n",
              "SetATEConTxETxBfInitProc",local_c8,local_9c,local_bc,local_a0,cVar3), -1 < DebugLevel
      )) && (uVar11 = local_c0, uVar10 = local_88, uVar19 = local_80,
            printk("%s: Power = %d, Channel = %d, Channel2 = %d, Channl_band = %d, TxPktLength = %d\n"
                   ,"SetATEConTxETxBfInitProc",local_94,local_c4,local_c0,local_88,local_80),
            0 < DebugLevel)) {
    printk("%s: control_band_idx = %d\n","SetATEConTxETxBfInitProc",uVar13,DebugLevel,uVar11,uVar10,
           uVar19);
  }
  iVar9 = uVar13 * 0xd18;
  iVar17 = iVar4 + iVar9;
  iVar15 = iVar5 + iVar9;
  iVar16 = iVar6 + iVar9;
  iVar8 = net_ad_wrap_service(param_1);
  memmove((void *)(iVar8 + iVar9 + 0x511),TemplateFrame,0x20);
  SetATE(param_1,"ATEAP");
  iVar8 = jiffies;
  SetATE(param_1,"ATESTART");
  CmdTxBfHwEnableStatusUpdate(param_1,1,0);
  os_move_mem((void *)(iVar17 + 0x531),&Addr1,6);
  snprintf((char *)&local_78,0x50,"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",
           (uint)*(byte *)(iVar4 + iVar9 + 0x531),(uint)*(byte *)(iVar17 + 0x532),
           (uint)*(byte *)(iVar17 + 0x533),(uint)*(byte *)(iVar17 + 0x534),
           (uint)*(byte *)(iVar17 + 0x535),(uint)*(byte *)(iVar17 + 0x536));
  SetATEDaByWtblTlv(param_1,&local_78);
  os_move_mem((void *)(iVar15 + 0x591),&Addr2,6);
  os_move_mem((void *)(iVar16 + 0x5f1),&Addr3,6);
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    AsicDevInfoUpdate(param_1,0,(void *)(iVar15 + 0x591),uVar13,1,1);
  }
  iVar9 = param_1 + 0xa77bb4;
  snprintf((char *)&local_78,0x50,"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",0,uVar13,
           (uint)*(byte *)(iVar6 + uVar13 * 0xd18 + 0x5f1),(uint)*(byte *)(iVar16 + 0x5f2),
           (uint)*(byte *)(iVar16 + 0x5f3),(uint)*(byte *)(iVar16 + 0x5f4),
           (uint)*(byte *)(iVar16 + 0x5f5),(uint)*(byte *)(iVar16 + 0x5f6));
  Set_BssInfoUpdate(param_1,&local_78);
  iVar4 = net_ad_wrap_service(param_1);
  iVar4 = iVar4 + uVar13 * 0xd18 + 0x510;
  memmove((void *)(iVar4 + 5),&Addr1,6);
  *(undefined4 *)(iVar4 + 0xb) = (undefined4)Addr2;
  *(undefined2 *)(iVar4 + 0xf) = Addr2._4_2_;
  *(undefined4 *)(iVar4 + 0x11) = (undefined4)Addr3;
  *(undefined2 *)(iVar4 + 0x15) = Addr3._4_2_;
  snprintf((char *)&local_78,0x50,"%d",local_c8);
  mt_agent_cli_set_dw("ATETXMODE",iVar9,&local_78);
  snprintf((char *)&local_78,0x50,"%d",local_9c);
  mt_agent_cli_set_dw("ATETXMCS",iVar9,&local_78);
  uVar11 = local_bc;
  snprintf((char *)&local_78,0x50,"%d:%d",local_bc,local_bc);
  mt_agent_cli_set_ext("ATETXBW",iVar9,&local_78);
  if (bVar18) {
    snprintf((char *)&local_78,0x50,"%d",local_a0,uVar11);
    mt_agent_cli_set_dw("ATETXNSS",iVar9,&local_78);
  }
  mt_agent_cli_set_dw("ATETXGI",iVar9,&_LC326);
  SetATETxLdpc(param_1,&_LC332);
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + uVar13 * 0xd18 + 0x1130) = (undefined1)local_c4;
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar4 + uVar13 * 0xd18 + 0x1143) = (undefined1)local_c0;
  snprintf((char *)&local_78,0x50,"%d",local_94);
  mt_agent_cli_set_ext("ATETXPOW0",iVar9,&local_78);
  if (0 < DebugLevel) {
    printk("%s(): DUT Init Time consumption : %lu sec\n","SetATEConTxETxBfInitProc",
           (uint)((jiffies - iVar8) * 1000) / 100);
  }
  snprintf((char *)&local_78,0x50,"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x:%.2x",0,
           (uint)*(byte *)(uVar13 * 0xd18 + iVar5 + 0x591),(uint)*(byte *)(iVar15 + 0x592),
           (uint)*(byte *)(iVar15 + 0x593),(uint)*(byte *)(iVar15 + 0x594),
           (uint)*(byte *)(iVar15 + 0x595),(uint)*(byte *)(iVar15 + 0x596),uVar13);
  Set_DevInfoUpdate(param_1,&local_78);
  Set_Stop_Sounding_Proc(param_1,&_LC332);
  SetATEEBfTx(param_1,&_LC332);
  snprintf((char *)&local_78,0x50,"%d:%d:0:%d",local_c4,local_88,local_c0);
  mt_agent_cli_set_ext("ATECHANNEL",iVar9,&local_78);
  RtmpOsMsDelay(1000);
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    if (cVar3 == '\x04') goto LAB_0026aff8;
    if (cVar3 == '\x03') goto LAB_0026b310;
    if (cVar3 == '\x02') {
      if (uVar13 == 1) {
        mt_agent_cli_set_ext("ATETXANT",iVar9,&_LC442);
        mt_agent_cli_set_ext("ATERXANT",iVar9,&_LC442);
      }
      else {
        mt_agent_cli_set_ext("ATETXANT",iVar9,&_LC443);
        mt_agent_cli_set_ext("ATERXANT",iVar9,&_LC443);
      }
    }
LAB_0026ac58:
    snprintf((char *)&local_78,0x50,"%d",local_80,local_88,local_c0);
    SetATETxLength(param_1,&local_78);
    SetATETxCount(param_1,&_LC326);
    SetATEIpg(param_1,&_LC434);
    SetATEQid(param_1,&_LC332);
    SetATE(param_1,"TXCOMMIT");
    snprintf((char *)&local_78,0x50,"%d",0);
    Set_TxBfProfileTag_PfmuIdx(param_1,&local_78);
    Set_TxBfProfileTag_BfType(param_1,&_LC332);
    snprintf((char *)&local_78,0x50,"%d",local_bc);
    Set_TxBfProfileTag_DBW(param_1,&local_78);
    Set_TxBfProfileTag_SuMu(param_1,&_LC326);
    local_78 = 0x303a3030;
    uStack_74 = 0x30303a30;
    pcStack_70 = (char *)0x3a31303a;
    uStack_6c = 0x303a3030;
    local_68 = 0x30303a32;
    uStack_64 = 0x33303a;
    Set_TxBfProfileTag_Mem(param_1,&local_78);
    if (bVar18) {
LAB_0026b128:
      if (local_bc == 3 || local_bc == 6) {
        if (cVar3 == '\x04') {
          uVar11 = 1;
        }
        else if (DebugLevel < 1) {
          uVar11 = 0;
        }
        else {
          uVar11 = 0;
          printk("%s: Invalid Configuration for BW160!! For BW160, TxStream number must be 4!!\n",
                 "SetATEConTxETxBfInitProc");
        }
        goto LAB_0026ad68;
      }
      if (cVar3 == '\x04') goto LAB_0026b25c;
      if (cVar3 == '\x03') goto LAB_0026b184;
    }
    uVar11 = (uint)(cVar3 == '\x02');
  }
  else if (cVar3 == '\x04') {
LAB_0026aff8:
    mt_agent_cli_set_ext("ATETXANT",iVar9,&_LC427);
    mt_agent_cli_set_ext("ATERXANT",iVar9,&_LC427);
    snprintf((char *)&local_78,0x50,"%d",local_80);
    SetATETxLength(param_1,&local_78);
    SetATETxCount(param_1,&_LC326);
    SetATEIpg(param_1,&_LC434);
    SetATEQid(param_1,&_LC332);
    SetATE(param_1,"TXCOMMIT");
    snprintf((char *)&local_78,0x50,"%d",0);
    Set_TxBfProfileTag_PfmuIdx(param_1,&local_78);
    Set_TxBfProfileTag_BfType(param_1,&_LC332);
    snprintf((char *)&local_78,0x50,"%d",local_bc);
    Set_TxBfProfileTag_DBW(param_1,&local_78);
    Set_TxBfProfileTag_SuMu(param_1,&_LC326);
    local_78 = 0x303a3030;
    uStack_74 = 0x30303a30;
    pcStack_70 = (char *)0x3a31303a;
    uStack_6c = 0x303a3030;
    local_68 = 0x30303a32;
    uStack_64 = 0x33303a;
    Set_TxBfProfileTag_Mem(param_1,&local_78);
    if (bVar18) goto LAB_0026b128;
LAB_0026b25c:
    uVar11 = 3;
  }
  else {
    if (cVar3 != '\x03') {
      if (cVar3 == '\x02') {
        mt_agent_cli_set_ext("ATETXANT",iVar9,&_LC426);
        mt_agent_cli_set_ext("ATERXANT",iVar9,&_LC426);
      }
      goto LAB_0026ac58;
    }
LAB_0026b310:
    mt_agent_cli_set_ext("ATETXANT",iVar9,&_LC429);
    mt_agent_cli_set_ext("ATERXANT",iVar9,&_LC429);
    snprintf((char *)&local_78,0x50,"%d",local_80);
    SetATETxLength(param_1,&local_78);
    SetATETxCount(param_1,&_LC326);
    SetATEIpg(param_1,&_LC434);
    SetATEQid(param_1,&_LC332);
    SetATE(param_1,"TXCOMMIT");
    snprintf((char *)&local_78,0x50,"%d",0);
    Set_TxBfProfileTag_PfmuIdx(param_1,&local_78);
    Set_TxBfProfileTag_BfType(param_1,&_LC332);
    snprintf((char *)&local_78,0x50,"%d",local_bc);
    Set_TxBfProfileTag_DBW(param_1,&local_78);
    Set_TxBfProfileTag_SuMu(param_1,&_LC326);
    local_78 = 0x303a3030;
    uStack_74 = 0x30303a30;
    pcStack_70 = (char *)0x3a31303a;
    uStack_6c = 0x303a3030;
    local_68 = 0x30303a32;
    uStack_64 = 0x33303a;
    Set_TxBfProfileTag_Mem(param_1,&local_78);
    if (bVar18) goto LAB_0026b128;
LAB_0026b184:
    uVar11 = 2;
  }
LAB_0026ad68:
  if (bVar2) {
    uVar10 = 3;
  }
  else if (bVar1) {
    uVar10 = 2;
  }
  else {
    uVar10 = (uint)(local_c8 == 2);
  }
  snprintf((char *)&local_78,0x12,"%.2x:00:00:%.2x:00:00",uVar11,uVar10);
  Set_TxBfProfileTag_Matrix(param_1,&local_78);
  local_78 = 0x303a3030;
  uStack_74 = 0x30303a30;
  pcStack_70 = "(%d), timeout(%dms)\n";
  Set_TxBfProfileTag_SNR(param_1,&_LC329);
  Set_TxBfProfileTag_SmartAnt(param_1,&_LC326);
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    if (uVar13 == 1) {
      uVar12 = 0x19;
    }
    else {
      uVar12 = 0x18;
    }
  }
  else {
    uVar12 = 0;
  }
  snprintf((char *)&local_78,0x50,"%u",uVar12,uVar10);
  Set_TxBfProfileTag_SeIdx(param_1,&local_78);
  if (0 < DebugLevel) {
    printk("%s: u1Spe: %u\n","SetATEConTxETxBfInitProc",uVar12);
  }
  Set_TxBfProfileTag_RmsdThrd(param_1,&_LC326);
  local_78 = 0x303a3030;
  uStack_74 = 0x30303a30;
  pcStack_70 = (char *)0x3a30303a;
  uStack_6c = 0x303a3030;
  local_68 = CONCAT22(local_68._2_2_,0x30);
  Set_TxBfProfileTag_McsThrd(param_1,&local_78);
  Set_TxBfProfileTag_InValid(param_1,&_LC332);
  local_78 = CONCAT13(local_78._3_1_,0x3030);
  Set_TxBfProfileTagWrite(param_1,&local_78);
  if (bVar2) {
    snprintf((char *)&local_78,0x50,
             "%.2x:%.2x:%.2x:00:01:49:00:49:08:00:%.2x:%.2x:00:00:00:00:00:01:00:02:00:03:00",1,
             uVar13,0,uVar11,local_bc);
  }
  else {
    if (bVar1) {
      __format = "%.2x:%.2x:%.2x:00:01:09:00:09:04:00:%.2x:%.2x:00:00:00:00:00:01:00:02:00:03:00";
    }
    else {
      if (local_c8 != 2) goto LAB_0026aec4;
      if (cVar3 == '\x04') {
        __format = "%.2x:%.2x:%.2x:00:01:00:18:00:02:00:%.2x:%.2x:00:00:00:00:00:01:00:02:00:03:00";
      }
      else if (cVar3 == '\x03') {
        __format = "%.2x:%.2x:%.2x:00:01:00:10:00:02:00:%.2x:%.2x:00:00:00:00:00:01:00:02:00:03:00";
      }
      else {
        if (cVar3 != '\x02') goto LAB_0026aec4;
        __format = "%.2x:%.2x:%.2x:00:01:00:08:00:02:00:%.2x:%.2x:00:00:00:00:00:01:00:02:00:03:00";
      }
    }
    snprintf((char *)&local_78,0x50,__format,1,uVar13,0,uVar11,local_bc);
  }
LAB_0026aec4:
  Set_StaRecBfUpdate(param_1,&local_78);
  Set_TxBfTxApply(param_1,"01:01:00:00:00");
  Set_StaRecBfRead(param_1,&_LC332);
  Set_Trigger_Sounding_Proc(param_1,"00:01:00:01:00:00:00");
  Set_Trigger_Sounding_Proc(param_1,"02:01:FF:01:00:00:00");
  SetATE(param_1,"RXFRAME");
  return local_a8;
}

