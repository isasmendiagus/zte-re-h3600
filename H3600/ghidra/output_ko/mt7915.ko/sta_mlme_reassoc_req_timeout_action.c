// module: mt7915.ko
// function: sta_mlme_reassoc_req_timeout_action @ 0x7ce9c
// size: 116 bytes
//

void sta_mlme_reassoc_req_timeout_action(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_2 + 0x92c));
  if (iVar1 != 0) {
    if (2 < DebugLevel) {
      printk("ASSOC - ReassocTimeoutAction\n");
    }
    assoc_fsm_state_transition(*(undefined4 *)(param_2 + 0x92c),0);
    cntl_auth_assoc_conf(*(undefined4 *)(param_2 + 0x92c),4,0x10);
    return;
  }
  printk(&_LC1,0xa13);
  dump_stack();
  return;
}

