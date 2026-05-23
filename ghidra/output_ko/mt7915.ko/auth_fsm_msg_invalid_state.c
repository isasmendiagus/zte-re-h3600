// module: mt7915.ko
// function: auth_fsm_msg_invalid_state @ 0x10e0f0
// size: 156 bytes
//

void auth_fsm_msg_invalid_state(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  char *pcVar2;
  
  puVar1 = *(undefined4 **)(param_2 + 0x92c);
  if (DebugLevel < 2) {
    cntl_auth_assoc_conf(puVar1,2,0x53);
    return;
  }
  pcVar2 = "(REPT)";
  if (puVar1[5] != 0x100) {
    pcVar2 = "(STA)";
  }
  printk("%s [%s %s]: [%s][%s] ====================> FSM MSG DROP\n","auth_fsm_msg_invalid_state",
         *puVar1,pcVar2,*(undefined4 *)(AUTH_FSM_STATE_STR + puVar1[0x38c] * 4),
         *(undefined4 *)(AUTH_FSM_MSG_STR + *(int *)(param_2 + 0x904) * 4));
  cntl_auth_assoc_conf(*(undefined4 *)(param_2 + 0x92c),2,0x53);
  return;
}

