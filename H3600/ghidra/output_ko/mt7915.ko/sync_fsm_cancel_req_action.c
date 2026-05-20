// module: mt7915.ko
// function: sync_fsm_cancel_req_action @ 0x10a750
// size: 412 bytes
//

void sync_fsm_cancel_req_action(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined1 uStack_23;
  undefined2 local_22 [3];
  
  uVar4 = 0;
  local_22[0] = 0;
  iVar1 = get_scan_ctrl_by_wdev();
  iVar2 = GetStaCfgByWdev(param_1,param_2);
  if (*(undefined4 **)(iVar1 + 0xaf5d0) != (undefined4 *)0x0 &&
      param_2 == *(undefined4 **)(iVar1 + 0xaf5d0)) {
    if (*(int *)(iVar1 + 0x90) == 1) {
      cntl_scan_conf(param_2,0x53);
      uVar4 = 1;
    }
    else if (*(int *)(iVar1 + 0x90) == 2) {
      cntl_join_start_conf(param_2,0x53);
      uVar4 = 1;
    }
    if (-1 < DebugLevel) {
      printk("%s [%s] Band(%d): [%s] ====================> CANCEL SYNC FSM FROM OUTSIDE (%d)\n",
             "sync_fsm_cancel_req_action",*param_2,*(undefined1 *)(iVar1 + 0x1c6),
             *(undefined4 *)(SYNC_FSM_STATE_STR + *(int *)(iVar1 + 0x90) * 4),uVar4);
    }
    if (iVar2 != 0) {
      RTMPCancelTimer(iVar2 + 0x211e4c,&uStack_23);
    }
    RTMPCancelTimer(iVar1 + 0x148,&uStack_23);
    *(undefined1 *)(iVar1 + 2) = 0;
    scan_next_channel(param_1,param_2,local_22);
    puVar3 = (undefined1 *)get_scan_ctrl_by_wdev(param_2[2],param_2);
    iVar1 = *(int *)(puVar3 + 0x90);
    *(undefined4 *)(puVar3 + 0x90) = 0;
    if (*(undefined4 **)(puVar3 + 0xaf5d0) == (undefined4 *)0x0) {
      if (-1 < DebugLevel) {
        printk("ScanCtrl->ScanReqwdev is NULL\n");
      }
    }
    else if (1 < DebugLevel) {
      printk("SYNC[%s, Band:%d, TYPE:%d]: [%s] ==============================================> [%s]\n"
             ,**(undefined4 **)(puVar3 + 0xaf5d0),puVar3[0x1c6],*puVar3,
             *(undefined4 *)(SYNC_FSM_STATE_STR + iVar1 * 4),SYNC_FSM_STATE_STR._0_4_);
    }
  }
  return;
}

