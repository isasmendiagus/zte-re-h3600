// module: mt7915.ko
// function: sync_fsm_join_timeout_action @ 0x108740
// size: 700 bytes
//

void sync_fsm_join_timeout_action(int param_1,int param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  
  iVar10 = *(int *)(param_2 + 0x92c);
  iVar3 = get_scan_tab_by_wdev(param_1,iVar10);
  iVar4 = GetStaCfgByWdev(param_1,iVar10);
  if (1 < DebugLevel) {
    printk("%s - ProbeTimeoutAtJoinAction\n","sync_fsm_join_timeout_action");
  }
  if (iVar4 == 0) {
    return;
  }
  cVar1 = *(char *)(iVar4 + 0x2123e9);
  if (2 < DebugLevel) {
    printk("APCLI_SYNC - MlmeAux.Bssid=%02x:%02x:%02x:%02x:%02x:%02x\n",
           *(undefined1 *)(iVar4 + 0x413a),*(undefined1 *)(iVar4 + 0x413b),
           *(undefined1 *)(iVar4 + 0x413c),*(undefined1 *)(iVar4 + 0x413d),
           *(undefined1 *)(iVar4 + 0x413e),*(undefined1 *)(iVar4 + 0x413f));
  }
  if (cVar1 != '\0') {
    if ((*(char *)(iVar4 + 0x213390) != '\x01') && ((&DAT_003678fc)[param_1] != '\x01')) {
LAB_00108824:
      bVar2 = true;
      goto LAB_001087b0;
    }
    iVar6 = BssTableSearch(iVar3,iVar4 + 0x413a,*(undefined1 *)(iVar4 + 0x1a));
    if (iVar6 == -1) {
      if (-1 < DebugLevel) {
        printk("%s[%d]Can not find BssEntry\n","sync_fsm_join_timeout_action",0x3ef);
      }
    }
    else {
      iVar9 = iVar6 * 0xaf4;
      iVar7 = ApCliAutoConnectBWAdjust(param_1,iVar4,iVar3 + iVar9 + 8);
      if (((2 < DebugLevel) &&
          (printk("%s[%d]Bssidx:%lu\n","sync_fsm_join_timeout_action",0x3df,iVar6),
          *(char *)(iVar3 + iVar9 + 0x9c) != '\0')) && (2 < DebugLevel)) {
        printk("Root AP SSID: %s\n",iVar3 + iVar9 + 0x9d);
      }
      if (iVar7 != 0) {
        if (iVar7 == 2) {
          if (2 < DebugLevel) {
            printk("Switch to channel :%d\n",*(undefined1 *)(iVar6 * 0xaf4 + iVar3 + 0x14));
          }
          bVar2 = true;
          rtmp_set_channel(param_1,iVar4,*(undefined1 *)(iVar6 * 0xaf4 + iVar3 + 0x14));
          goto LAB_001087b0;
        }
        goto LAB_00108824;
      }
    }
  }
  bVar2 = false;
LAB_001087b0:
  puVar5 = (undefined1 *)get_scan_ctrl_by_wdev(*(undefined4 *)(iVar10 + 8),iVar10);
  iVar3 = *(int *)(puVar5 + 0x90);
  *(undefined4 *)(puVar5 + 0x90) = 0;
  if (*(undefined4 **)(puVar5 + 0xaf5d0) == (undefined4 *)0x0) {
    if (-1 < DebugLevel) {
      printk("ScanCtrl->ScanReqwdev is NULL\n");
    }
  }
  else if (1 < DebugLevel) {
    printk("SYNC[%s, Band:%d, TYPE:%d]: [%s] ==============================================> [%s]\n"
           ,**(undefined4 **)(puVar5 + 0xaf5d0),puVar5[0x1c6],*puVar5,
           *(undefined4 *)(SYNC_FSM_STATE_STR + iVar3 * 4),SYNC_FSM_STATE_STR._0_4_);
  }
  if (bVar2) {
    uVar8 = 0;
  }
  else {
    uVar8 = 0x10;
  }
  cntl_join_start_conf(*(undefined4 *)(param_2 + 0x92c),uVar8);
  return;
}

