// module: mt7915.ko
// function: Show_Rx_Statistic @ 0xec794
// size: 2420 bytes
//

undefined4 Show_Rx_Statistic(int *param_1,int param_2,int param_3)

{
  char *pcVar1;
  undefined4 uVar2;
  int iVar3;
  size_t sVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  int *piVar9;
  uint *puVar10;
  undefined1 auStack_d0 [4];
  int *local_cc;
  int *local_c8;
  char *local_c4;
  char *local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  uint local_ac;
  uint local_a8;
  uint local_a4;
  uint local_a0;
  uint local_98;
  uint local_94;
  uint local_90;
  uint local_8c;
  uint local_88;
  uint local_84;
  uint local_80;
  uint local_7c;
  uint local_78 [4];
  uint local_68 [4];
  int local_58;
  int local_54;
  int local_50;
  uint local_4c;
  uint local_48;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  
  if ((uint)*(byte *)((int)param_1 + 0x2b7242) <= (uint)*(byte *)(*param_1 + 0x3c)) {
    return 0;
  }
  uVar2 = HcGetBandByWdev(param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
  if ((2 < DebugLevel) && (printk("%s----------------->\n","Show_Rx_Statistic"), 2 < DebugLevel)) {
    printk("%s: BandIdx = %d\n","Show_Rx_Statistic",uVar2);
  }
  if (param_2 == 0) {
    os_alloc_mem(param_1,&local_bc,0x800);
    if (local_bc == (char *)0x0) {
      return 0;
    }
    __memzero(local_bc,0x800);
    local_bc[0] = '\n';
    local_bc[1] = '\0';
  }
  else {
    iVar3 = os_str_tol(param_2,0,10);
    os_alloc_mem(param_1,&local_bc,0x800);
    if (local_bc == (char *)0x0) {
      return 0;
    }
    __memzero(local_bc,0x800);
    pcVar7 = local_bc;
    local_bc[0] = '\n';
    local_bc[1] = '\0';
    if (iVar3 == 0) {
      sVar4 = strlen(local_bc);
      builtin_strncpy(pcVar7 + sVar4,"Reset counter !!\n",0x12);
      MtCmdSetPhyCounter(param_1,0,0);
      if (*(char *)((int)param_1 + 0x79504d) == '\x01') {
        MtCmdSetPhyCounter(param_1,0);
      }
      DAT_005f3630 = 0;
      param_1[0x29f08b] = 0;
      param_1[0x29f08c] = 0;
      param_1[0x29f08d] = 0;
      param_1[0x29f08e] = 0;
      DAT_005f3634 = 0;
      goto LAB_000ec8e8;
    }
  }
  local_c8 = param_1 + 0x1e5400;
  MtCmdSetPhyCounter(param_1,1,0);
  if (*(char *)((int)param_1 + 0x79504d) == '\x01') {
    MtCmdSetPhyCounter(param_1,1,1);
  }
  local_a0 = AsicGetRxStat(param_1,4);
  piVar9 = param_1 + 0x29eff4;
  local_a4 = local_a0 >> 0x10;
  local_a0 = local_a0 & 0xffff;
  local_94 = AsicGetRxStat(param_1,5);
  local_98 = local_94 >> 0x10;
  local_94 = local_94 & 0xffff;
  local_8c = AsicGetRxStat(param_1,6);
  local_90 = local_8c >> 0x10;
  local_8c = local_8c & 0xffff;
  local_84 = AsicGetRxStat(param_1,7);
  local_88 = local_84 >> 0x10;
  local_84 = local_84 & 0xffff;
  uVar2 = AsicGetRxStat(param_1,8);
  FUN_000d538c(param_1,&local_b8,8,uVar2);
  uVar2 = AsicGetRxStat(param_1,0xb);
  FUN_000d538c(param_1,&local_b8,0xb,uVar2);
  iVar3 = AsicGetRxStat(param_1,0xc);
  local_80 = (uint)(iVar3 << 0xd) >> 0x1f;
  iVar3 = AsicGetRxStat(param_1,0xd);
  local_7c = (uint)(iVar3 << 0xd) >> 0x1f;
  local_a8 = AsicGetRxStat(param_1,3);
  local_cc = param_1 + 0x29ec00;
  local_ac = local_a8 >> 0x10;
  if ((param_1[0xa5b19] & 0xffffU) == 0x7622) {
    local_a8 = (local_a8 << 0x10) >> 0x11;
  }
  else {
    local_a8 = local_a8 & 0xffff;
  }
  local_b8 = param_1[0x29f08b] - DAT_005f3630;
  local_b4 = param_1[0x29f08c] - DAT_005f3634;
  local_c4 = local_bc;
  local_b0 = local_b4 - local_b8;
  DAT_005f3630 = param_1[0x29f08b];
  DAT_005f3634 = param_1[0x29f08c];
  sVar4 = strlen(local_bc);
  sprintf(local_c4 + sVar4,"\x1b[41m%s : \x1b[m\n","Show_Rx_Statistic");
  local_c4 = local_bc;
  sVar4 = strlen(local_bc);
  sprintf(local_c4 + sVar4,"FreqOffsetFromRx   = %d\n",param_1[0x29efd1]);
  iVar3 = 0;
  do {
    pcVar7 = local_bc;
    sVar4 = strlen(local_bc);
    iVar8 = iVar3 + 1;
    piVar9 = piVar9 + 1;
    sprintf(pcVar7 + sVar4,"RCPI_%d             = %d\n",iVar3,*piVar9);
    iVar3 = iVar8;
  } while (iVar8 != 4);
  piVar9 = param_1 + 0x29eff8;
  iVar3 = 0;
  do {
    pcVar7 = local_bc;
    sVar4 = strlen(local_bc);
    iVar8 = iVar3 + 1;
    piVar9 = piVar9 + 1;
    sprintf(pcVar7 + sVar4,"FAGC_RSSI_IB_%d     = %d\n",iVar3,*piVar9);
    iVar3 = iVar8;
  } while (iVar8 != 4);
  piVar9 = param_1 + 0x29effc;
  iVar3 = 0;
  do {
    pcVar7 = local_bc;
    sVar4 = strlen(local_bc);
    iVar8 = iVar3 + 1;
    piVar9 = piVar9 + 1;
    sprintf(pcVar7 + sVar4,"FAGC_RSSI_WB_%d     = %d\n",iVar3,*piVar9);
    iVar3 = iVar8;
  } while (iVar8 != 4);
  puVar10 = &local_7c;
  iVar3 = 0;
  do {
    pcVar7 = local_bc;
    sVar4 = strlen(local_bc);
    iVar8 = iVar3 + 1;
    puVar10 = puVar10 + 1;
    sprintf(pcVar7 + sVar4,"Inst_IB_RSSI_%d     = %d\n",iVar3,*puVar10);
    iVar3 = iVar8;
  } while (iVar8 != 4);
  puVar10 = local_78 + 3;
  iVar3 = 0;
  do {
    pcVar7 = local_bc;
    sVar4 = strlen(local_bc);
    iVar8 = iVar3 + 1;
    puVar10 = puVar10 + 1;
    sprintf(pcVar7 + sVar4,"Inst_WB_RSSI_%d     = %d\n",iVar3,*puVar10);
    pcVar7 = local_bc;
    iVar3 = iVar8;
  } while (iVar8 != 4);
  sVar4 = strlen(local_bc);
  sprintf(pcVar7 + sVar4,"SNR                = %d\n",local_cc[0x3e5]);
  pcVar7 = local_bc;
  sVar4 = strlen(local_bc);
  sprintf(pcVar7 + sVar4,"ACIHitHigh         = %u\n",local_7c);
  pcVar7 = local_bc;
  sVar4 = strlen(local_bc);
  sprintf(pcVar7 + sVar4,"ACIHitLow          = %u\n",local_80);
  pcVar7 = local_bc;
  sVar4 = strlen(local_bc);
  pcVar1 = local_bc;
  builtin_strncpy(pcVar7 + sVar4,"\x1b[41mFor Band0Index : \x1b[m\n",0x1b);
  sVar4 = strlen(local_bc);
  sprintf(pcVar1 + sVar4,"MacMdrdyCount      = %u\n",local_b4);
  pcVar7 = local_bc;
  sVar4 = strlen(local_bc);
  sprintf(pcVar7 + sVar4,"MacFCSErrCount     = %u\n",local_b8);
  pcVar7 = local_bc;
  sVar4 = strlen(local_bc);
  sprintf(pcVar7 + sVar4,"MacFCSOKCount      = %u\n",local_b0);
  pcVar7 = local_bc;
  sVar4 = strlen(local_bc);
  sprintf(pcVar7 + sVar4,"CCK_PD             = %u\n",local_94);
  pcVar7 = local_bc;
  sVar4 = strlen(local_bc);
  sprintf(pcVar7 + sVar4,"CCK_SFD_Err        = %u\n",local_8c);
  pcVar7 = local_bc;
  sVar4 = strlen(local_bc);
  sprintf(pcVar7 + sVar4,"CCK_SIG_Err        = %u\n",local_90);
  pcVar7 = local_bc;
  sVar4 = strlen(local_bc);
  sprintf(pcVar7 + sVar4,"CCK_FCS_Err        = %u\n",local_a0);
  pcVar7 = local_bc;
  sVar4 = strlen(local_bc);
  sprintf(pcVar7 + sVar4,"OFDM_PD            = %u\n",local_98);
  pcVar7 = local_bc;
  sVar4 = strlen(local_bc);
  sprintf(pcVar7 + sVar4,"OFDM_SIG_Err       = %u\n",local_88);
  pcVar7 = local_bc;
  sVar4 = strlen(local_bc);
  sprintf(pcVar7 + sVar4,"OFDM_FCS_Err       = %u\n",local_a4);
  if (*(char *)((int)local_c8 + 0x4d) == '\x01') {
    local_58 = param_1[0x29f08d] - DAT_005f3638;
    local_54 = param_1[0x29f08e] - DAT_005f363c;
    local_50 = local_54 - local_58;
    DAT_005f3638 = param_1[0x29f08d];
    DAT_005f363c = param_1[0x29f08e];
    local_48 = AsicGetRxStat(param_1,0x14);
    local_4c = local_48 >> 0x10;
    local_48 = local_48 & 0xffff;
    local_3c = AsicGetRxStat(param_1,0x16);
    local_40 = local_3c >> 0x10;
    local_3c = local_3c & 0xffff;
    local_34 = AsicGetRxStat(param_1,0x17);
    local_38 = local_34 >> 0x10;
    local_34 = local_34 & 0xffff;
    local_2c = AsicGetRxStat(param_1,0x18);
    pcVar7 = local_bc;
    local_30 = local_2c >> 0x10;
    local_2c = local_2c & 0xffff;
    sVar4 = strlen(local_bc);
    pcVar1 = local_bc;
    builtin_strncpy(pcVar7 + sVar4,"\x1b[41mFor Band1Index : \x1b[m\n",0x1b);
    sVar4 = strlen(local_bc);
    sprintf(pcVar1 + sVar4,"MacMdrdyCount      = %u\n",local_54);
    pcVar7 = local_bc;
    sVar4 = strlen(local_bc);
    sprintf(pcVar7 + sVar4,"MacFCSErrCount     = %u\n",local_58);
    pcVar7 = local_bc;
    sVar4 = strlen(local_bc);
    sprintf(pcVar7 + sVar4,"MacFCSOKCount      = %u\n",local_50);
    pcVar7 = local_bc;
    sVar4 = strlen(local_bc);
    sprintf(pcVar7 + sVar4,"CCK_PD             = %u\n",local_3c);
    pcVar7 = local_bc;
    sVar4 = strlen(local_bc);
    sprintf(pcVar7 + sVar4,"CCK_SFD_Err        = %u\n",local_34);
    pcVar7 = local_bc;
    sVar4 = strlen(local_bc);
    sprintf(pcVar7 + sVar4,"CCK_SIG_Err        = %u\n",local_38);
    pcVar7 = local_bc;
    sVar4 = strlen(local_bc);
    sprintf(pcVar7 + sVar4,"OFDM_PD            = %u\n",local_40);
    pcVar7 = local_bc;
    sVar4 = strlen(local_bc);
    sprintf(pcVar7 + sVar4,"OFDM_SIG_Err       = %u\n",local_30);
  }
LAB_000ec8e8:
  pcVar7 = local_bc;
  sVar4 = strlen(local_bc);
  uVar5 = *(uint *)(param_3 + 0x10);
  *(short *)(param_3 + 0x14) = (short)sVar4;
  uVar6 = *(uint *)(((uint)auStack_d0 & 0xffffe000) + 8);
  if (!CARRY4(uVar5,sVar4 & 0xffff) && uVar5 + (sVar4 & 0xffff) <= uVar6) {
    uVar6 = 0;
  }
  if (uVar6 == 0) {
    __copy_to_user(uVar5,pcVar7);
    pcVar7 = local_bc;
  }
  os_free_mem(pcVar7);
  if (DebugLevel < 3) {
    return 1;
  }
  printk("%s<-----------------\n","Show_Rx_Statistic");
  return 1;
}

