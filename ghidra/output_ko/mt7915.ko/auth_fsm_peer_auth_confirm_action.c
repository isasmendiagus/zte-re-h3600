// module: mt7915.ko
// function: auth_fsm_peer_auth_confirm_action @ 0x10da58
// size: 156 bytes
//

void auth_fsm_peer_auth_confirm_action(undefined4 param_1,int param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  
  if (*(int *)(param_2 + 0x92c) == 0) {
    printk(&_LC0,0x123);
    dump_stack();
    if (DebugLevel < 0) {
      return;
    }
    printk("[%s]: wdev %s\n","auth_fsm_peer_auth_confirm_action",&_LC3);
    return;
  }
  UNRECOVERED_JUMPTABLE = *(code **)(*(int *)(*(int *)(param_2 + 0x92c) + 0xedc) + 0x14);
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0010da74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("[%s]: wdev %s , auth_api->peer_auth_confirm_action %s\n",
         "auth_fsm_peer_auth_confirm_action",&_LC2,&_LC3);
  return;
}

