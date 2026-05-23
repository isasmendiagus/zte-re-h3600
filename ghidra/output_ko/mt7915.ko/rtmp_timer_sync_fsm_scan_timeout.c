// module: mt7915.ko
// function: rtmp_timer_sync_fsm_scan_timeout @ 0x10b928
// size: 368 bytes
//

void rtmp_timer_sync_fsm_scan_timeout(int param_1)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  iVar5 = **(int **)(param_1 + 0x24);
  uVar4 = (uint)*(byte *)(*(int **)(param_1 + 0x24) + 2);
  iVar3 = *(int *)(uVar4 * 0xaf5d8 + iVar5 + 0x8d8840);
  if (2 < DebugLevel) {
    printk("AP SYNC - Scan Timeout\n");
  }
  if ((*(uint *)(iVar5 + 0xa39f84) & 0x40) == 0) {
    iVar1 = MlmeEnqueueWithWdev(iVar5,4,3,0,0,*(undefined1 *)(iVar3 + 0xe),iVar3);
    if (iVar1 != 0) {
      RtmpOsMlmeUp(iVar5 + 0x286298);
      goto LAB_0010ba04;
    }
  }
  *(undefined1 *)(uVar4 * 0xaf5d8 + iVar5 + 0x829272) = 0;
  puVar2 = (undefined1 *)get_scan_ctrl_by_wdev(*(undefined4 *)(iVar3 + 8),iVar3);
  iVar5 = *(int *)(puVar2 + 0x90);
  *(undefined4 *)(puVar2 + 0x90) = 0;
  if (*(undefined4 **)(puVar2 + 0xaf5d0) == (undefined4 *)0x0) {
    if (-1 < DebugLevel) {
      printk("ScanCtrl->ScanReqwdev is NULL\n");
    }
  }
  else if (1 < DebugLevel) {
    printk("SYNC[%s, Band:%d, TYPE:%d]: [%s] ==============================================> [%s]\n"
           ,**(undefined4 **)(puVar2 + 0xaf5d0),puVar2[0x1c6],*puVar2,
           *(undefined4 *)(SYNC_FSM_STATE_STR + iVar5 * 4),SYNC_FSM_STATE_STR._0_4_);
  }
  cntl_scan_conf(iVar3,0);
LAB_0010ba04:
  if (*(char *)(param_1 + 0x1f) == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20));
  return;
}

