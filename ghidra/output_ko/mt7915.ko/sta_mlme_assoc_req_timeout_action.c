// module: mt7915.ko
// function: sta_mlme_assoc_req_timeout_action @ 0x7cf10
// size: 120 bytes
//

void sta_mlme_assoc_req_timeout_action(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_2 + 0x92c));
  uVar2 = *(undefined4 *)(param_2 + 0x92c);
  if (iVar1 != 0) {
    if (0 < DebugLevel) {
      printk("ASSOC - AssocTimeoutAction\n");
    }
    assoc_fsm_state_transition(uVar2,0);
    cntl_auth_assoc_conf(uVar2,3,0x10);
    return;
  }
  printk(&_LC1,0x9f6);
  dump_stack();
  return;
}

