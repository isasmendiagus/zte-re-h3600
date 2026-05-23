// module: mt7915.ko
// function: assoc_fsm_msg_invalid_state @ 0x10c77c
// size: 380 bytes
//

void assoc_fsm_msg_invalid_state(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = *(undefined4 **)(param_2 + 0x92c);
  iVar1 = get_scan_ctrl_by_wdev(param_1,puVar3);
  iVar2 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_2 + 0x92c));
  if (iVar2 == 0) {
    if (puVar3 == (undefined4 *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s:wdev=NULL\n","assoc_fsm_msg_invalid_state");
        return;
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s:wdev(type=%d,func_idx=%d\n","assoc_fsm_msg_invalid_state",puVar3[5],
             *(undefined1 *)((int)puVar3 + 0xe));
      return;
    }
  }
  else {
    iVar2 = *(int *)(param_2 + 0x904);
    if (iVar2 == 1) {
      cntl_auth_assoc_conf(*(undefined4 *)(param_2 + 0x92c),4,0x53);
    }
    else if (iVar2 == 0) {
      cntl_auth_assoc_conf(*(undefined4 *)(param_2 + 0x92c),3,0x53);
    }
    else {
      if (iVar2 != 2) {
        if (DebugLevel < 2) {
          return;
        }
        printk("%s [%s]: [%s][%s] ====================> FSM MSG DROP\n",
               "assoc_fsm_msg_invalid_state",*puVar3,
               *(undefined4 *)(ASSOC_FSM_STATE_STR + *(int *)(iVar1 + 0x90) * 4),
               *(undefined4 *)(ASSOC_FSM_MSG_STR + iVar2 * 4));
        return;
      }
      cntl_auth_assoc_conf(*(undefined4 *)(param_2 + 0x92c),7,0x53);
    }
    if (1 < DebugLevel) {
      printk("%s [%s]: [%s][%s] ====================> state Recovery for CNTL\n",
             "assoc_fsm_msg_invalid_state",*puVar3,
             *(undefined4 *)(ASSOC_FSM_STATE_STR + *(int *)(iVar1 + 0x90) * 4),
             *(undefined4 *)(ASSOC_FSM_MSG_STR + *(int *)(param_2 + 0x904) * 4));
    }
  }
  return;
}

