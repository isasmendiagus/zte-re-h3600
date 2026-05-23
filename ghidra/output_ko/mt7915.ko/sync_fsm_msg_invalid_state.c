// module: mt7915.ko
// function: sync_fsm_msg_invalid_state @ 0x108a5c
// size: 176 bytes
//

void sync_fsm_msg_invalid_state(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  undefined4 *puVar4;
  
  puVar4 = *(undefined4 **)(param_2 + 0x92c);
  iVar1 = get_scan_ctrl_by_wdev(param_1,puVar4);
  iVar2 = FUN_00108a00(puVar4,param_2);
  if (iVar2 == 1) {
    if (DebugLevel < 2) {
      return;
    }
    iVar2 = *(int *)(param_2 + 0x904);
    iVar1 = *(int *)(iVar1 + 0x90);
    pcVar3 = "%s [%s]: [%s][%s] ====================> state Recovery for CNTL\n";
  }
  else {
    if (DebugLevel < 2) {
      return;
    }
    iVar2 = *(int *)(param_2 + 0x904);
    iVar1 = *(int *)(iVar1 + 0x90);
    pcVar3 = "%s [%s]: [%s][%s] ====================> FSM MSG DROP\n";
  }
  printk(pcVar3,"sync_fsm_msg_invalid_state",*puVar4,*(undefined4 *)(SYNC_FSM_STATE_STR + iVar1 * 4)
         ,*(undefined4 *)(SYNC_FSM_MSG_STR + iVar2 * 4));
  return;
}

