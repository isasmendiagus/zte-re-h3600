// module: mt7915.ko
// function: assoc_fsm_peer_reassoc_req_action @ 0x10c1e8
// size: 156 bytes
//

void assoc_fsm_peer_reassoc_req_action(undefined4 param_1,int param_2)

{
  code *UNRECOVERED_JUMPTABLE;
  
  if (*(int *)(param_2 + 0x92c) == 0) {
    printk(&_LC0,0x1ca);
    dump_stack();
    if (DebugLevel < 0) {
      return;
    }
    printk("[%s]: wdev %s\n","assoc_fsm_peer_reassoc_req_action",&_LC3);
    return;
  }
  UNRECOVERED_JUMPTABLE = *(code **)(*(int *)(*(int *)(param_2 + 0x92c) + 0xc98) + 0x1c);
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0010c204. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("[%s]: wdev %s , assoc_api->peer_reassoc_req_action %s\n",
         "assoc_fsm_peer_reassoc_req_action",&_LC2,&_LC3);
  return;
}

