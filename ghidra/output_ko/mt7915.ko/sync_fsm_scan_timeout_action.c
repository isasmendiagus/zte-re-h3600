// module: mt7915.ko
// function: sync_fsm_scan_timeout_action @ 0x109404
// size: 1352 bytes
//

void sync_fsm_scan_timeout_action(int param_1,int param_2)

{
  undefined1 uVar1;
  bool bVar2;
  char cVar3;
  undefined1 uVar4;
  char *pcVar5;
  int iVar6;
  undefined4 uVar7;
  undefined1 *puVar8;
  char cVar9;
  undefined4 *puVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  undefined4 uVar14;
  undefined2 local_ce;
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
  char local_8b;
  
  iVar13 = *(int *)(param_2 + 0x92c);
  pcVar5 = (char *)get_scan_ctrl_by_wdev(param_1,iVar13);
  local_ce = 0;
  iVar6 = GetStaCfgByWdev(param_1,iVar13);
  if (iVar6 == 0) {
    bVar2 = true;
  }
  else if ((*(char *)(iVar13 + 0x1a) == pcVar5[2]) && (*pcVar5 == '\0')) {
    bVar2 = false;
    if ((*(uint *)(iVar6 + 0x212464) & 0x81) == 0x81) {
      uVar7 = GetAssociatedAPByWdev(param_1,iVar6);
      RTMPSendNullFrame(param_1,uVar7,*(undefined1 *)(param_1 + 0x794cd0),
                        (uint)(*(int *)(param_1 + 0x795124) << 0x17) >> 0x1f,1);
    }
  }
  else {
    bVar2 = false;
  }
  iVar6 = HcGetBandByWdev(iVar13);
  uVar7 = Channel2Index(param_1,pcVar5[2],iVar6);
  UpdateChannelInfo(param_1,uVar7,*(undefined4 *)(param_1 + (iVar6 + 0xdae0a) * 4),iVar13);
  if (*(int *)(pcVar5 + 0x5c) == 1) {
    if ((uint)(byte)pcVar5[0x55] - (uint)(byte)pcVar5[0x54] == 1) {
      if (-1 < DebugLevel) {
        printk("scanning complete\n");
      }
      pcVar5[2] = '\0';
      pcVar5[0x5c] = '\x02';
      pcVar5[0x5d] = '\0';
      pcVar5[0x5e] = '\0';
      pcVar5[0x5f] = '\0';
    }
  }
  else {
    cVar3 = scan_find_next_channel(param_1,pcVar5,pcVar5[2]);
    pcVar5[2] = cVar3;
  }
  if (bVar2) {
    iVar6 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar6);
    if (*(int *)(pcVar5 + 0x5c) == 1) {
      local_a3 = (&DAT_0036b861)[param_1];
      local_cb = *(undefined4 *)(pcVar5 + 0x2a);
      local_bf = *(undefined4 *)(pcVar5 + 0x36);
      local_90 = *(undefined4 *)(param_1 + (local_a3 + 0xa1824) * 4 + 4);
      local_c7 = *(undefined4 *)(pcVar5 + 0x2e);
      local_c3 = *(undefined4 *)(pcVar5 + 0x32);
      local_a0 = *(undefined4 *)(param_1 + 0x286088);
      local_cc = 0x23;
      local_98 = *(undefined4 *)(param_1 + 0x286080);
      local_a4 = (undefined1)*(undefined4 *)(param_1 + 0x286074);
      local_9c = *(undefined4 *)(param_1 + 0x28607c);
      local_94 = *(undefined4 *)(param_1 + 0x286084);
      local_8b = pcVar5[0x78];
      RtmpOSWrielessEventSend(*(undefined4 *)(param_1 + 4),1,0x955,0,&local_cc,0xa4);
      uVar11 = (byte)pcVar5[0x54] + 1;
      uVar12 = uVar11 & 0xff;
      pcVar5[(byte)pcVar5[0x54] + 0x4f] = '\0';
      pcVar5[0x54] = (char)uVar11;
      cVar3 = pcVar5[uVar12 + 0x56];
      *pcVar5 = cVar3;
      cVar9 = pcVar5[uVar12 + 0x4a];
      pcVar5[2] = cVar9;
      if (2 < DebugLevel) {
        printk("[%s][%d]:Next OFFChannel scan for : %d:Scan type =%d from given list\n",
               "sync_fsm_scan_timeout_action",0x473,cVar9,cVar3);
        cVar9 = pcVar5[2];
      }
      uVar4 = HcGetBandByChannel(param_1,cVar9);
      *(undefined1 *)(param_1 + 0x28608c) = uVar4;
      if ((byte)pcVar5[2] != 0) {
        *(uint *)(param_1 + 0x286074) = (uint)(byte)pcVar5[2];
      }
      uVar11 = (uint)(byte)(&DAT_0036b861)[param_1];
      if (*(int *)(pcVar5 + 0x5c) == 1) {
        uVar12 = uVar11 + 1;
        uVar11 = uVar12 & 0xff;
        (&DAT_0036b861)[param_1] = (char)uVar12;
      }
    }
    else {
      uVar11 = (uint)(byte)(&DAT_0036b861)[param_1];
    }
    if (uVar11 < *(byte *)(iVar6 + 0x49c)) {
      (&DAT_0036b860)[param_1] = *(undefined1 *)(iVar6 + uVar11 * 0x14);
    }
  }
  iVar6 = scan_next_channel(param_1,iVar13,&local_ce);
  if (iVar6 == 0) {
    if (-1 < DebugLevel) {
      printk("SYNC - MlmeScanReqAction before Startup\n");
    }
    puVar8 = (undefined1 *)get_scan_ctrl_by_wdev(*(undefined4 *)(iVar13 + 8),iVar13);
    iVar6 = *(int *)(puVar8 + 0x90);
    *(undefined4 *)(puVar8 + 0x90) = 0;
    if (*(undefined4 **)(puVar8 + 0xaf5d0) == (undefined4 *)0x0) {
      if (-1 < DebugLevel) {
        printk("ScanCtrl->ScanReqwdev is NULL\n");
      }
    }
    else if (1 < DebugLevel) {
      printk("SYNC[%s, Band:%d, TYPE:%d]: [%s] ==============================================> [%s]\n"
             ,**(undefined4 **)(puVar8 + 0xaf5d0),puVar8[0x1c6],*puVar8,
             *(undefined4 *)(SYNC_FSM_STATE_STR + iVar6 * 4),SYNC_FSM_STATE_STR._0_4_);
    }
    cntl_scan_conf(iVar13,0x52);
    return;
  }
  if ((char)local_ce == '\0') {
    return;
  }
  if (local_ce._1_1_ == '\0') {
    puVar8 = (undefined1 *)get_scan_ctrl_by_wdev(*(undefined4 *)(iVar13 + 8),iVar13);
    iVar6 = *(int *)(puVar8 + 0x90);
    *(undefined4 *)(puVar8 + 0x90) = 0;
    puVar10 = *(undefined4 **)(puVar8 + 0xaf5d0);
    if (puVar10 == (undefined4 *)0x0) {
LAB_00109768:
      if (-1 < DebugLevel) {
        printk("ScanCtrl->ScanReqwdev is NULL\n");
      }
      goto LAB_0010957c;
    }
    if (DebugLevel < 2) goto LAB_0010957c;
    uVar4 = puVar8[0x1c6];
    uVar1 = *puVar8;
    uVar14 = *(undefined4 *)(SYNC_FSM_STATE_STR + iVar6 * 4);
    uVar7 = SYNC_FSM_STATE_STR._0_4_;
  }
  else {
    puVar8 = (undefined1 *)get_scan_ctrl_by_wdev(*(undefined4 *)(iVar13 + 8),iVar13);
    iVar6 = *(int *)(puVar8 + 0x90);
    *(undefined4 *)(puVar8 + 0x90) = 3;
    puVar10 = *(undefined4 **)(puVar8 + 0xaf5d0);
    if (puVar10 == (undefined4 *)0x0) goto LAB_00109768;
    if (DebugLevel < 2) goto LAB_0010957c;
    uVar4 = puVar8[0x1c6];
    uVar1 = *puVar8;
    uVar14 = *(undefined4 *)(SYNC_FSM_STATE_STR + iVar6 * 4);
    uVar7 = SYNC_FSM_STATE_STR._12_4_;
  }
  printk("SYNC[%s, Band:%d, TYPE:%d]: [%s] ==============================================> [%s]\n",
         *puVar10,uVar4,uVar1,uVar14,uVar7);
LAB_0010957c:
  if ((((*(int *)(iVar13 + 0x12e4) != 0) && (*(char *)(iVar13 + 0x3cc8) == '\x01')) &&
      (*(int *)(iVar13 + 0x12e8) == 1)) && (*(int *)(iVar13 + 0xca8) == 0)) {
    cntl_fsm_state_transition(iVar13,1,"sync_fsm_scan_timeout_action");
  }
  iVar6 = *(int *)(param_2 + 0x92c);
  if (((local_ce._1_1_ == '\0') &&
      (*(undefined1 *)(iVar6 + 0xbb4) = 0, *(int *)(iVar6 + 0x3bc8) == 2)) &&
     (iVar13 = FUN_00108b10(param_1,param_2), iVar13 != 0)) {
    return;
  }
  cntl_scan_conf(iVar6,0);
  return;
}

