// module: mt7915.ko
// function: sync_cntl_fsm_to_idle_when_scan_req @ 0x10be44
// size: 284 bytes
//

void sync_cntl_fsm_to_idle_when_scan_req(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined1 *puVar2;
  undefined1 uStack_11;
  
  if (*(int *)(param_2 + 0xca8) != 1) {
    return;
  }
  iVar1 = GetStaCfgByWdev();
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: fail to set scan parameters\n","sync_cntl_fsm_to_idle_when_scan_req");
    }
  }
  else {
    RTMPCancelTimer(iVar1 + 0x211e4c,&uStack_11);
    puVar2 = (undefined1 *)get_scan_ctrl_by_wdev(*(undefined4 *)(param_2 + 8),param_2);
    iVar1 = *(int *)(puVar2 + 0x90);
    *(undefined4 *)(puVar2 + 0x90) = 0;
    if (*(undefined4 **)(puVar2 + 0xaf5d0) == (undefined4 *)0x0) {
      if (-1 < DebugLevel) {
        printk("ScanCtrl->ScanReqwdev is NULL\n");
      }
    }
    else if (1 < DebugLevel) {
      printk("SYNC[%s, Band:%d, TYPE:%d]: [%s] ==============================================> [%s]\n"
             ,**(undefined4 **)(puVar2 + 0xaf5d0),puVar2[0x1c6],*puVar2,
             *(undefined4 *)(SYNC_FSM_STATE_STR + iVar1 * 4),SYNC_FSM_STATE_STR._0_4_);
    }
    cntl_fsm_state_transition(param_2,1,"sync_cntl_fsm_to_idle_when_scan_req");
    if (2 < DebugLevel) {
      printk("%s: success to set scan parameters\n","sync_cntl_fsm_to_idle_when_scan_req");
    }
  }
  return;
}

