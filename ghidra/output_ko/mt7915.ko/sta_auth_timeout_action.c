// module: mt7915.ko
// function: sta_auth_timeout_action @ 0x752d4
// size: 228 bytes
//

void sta_auth_timeout_action(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_2 + 0x92c);
  bVar1 = *(byte *)(iVar3 + 0xe);
  if (2 < DebugLevel) {
    printk(&_LC0,"sta_auth_timeout_action");
  }
  if (iVar3 != 0) {
    if (((*(char *)(param_1 + 0x286285) == '\x01') && (*(int *)(iVar3 + 0x14) == 2)) &&
       (iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0)),
       *(byte *)(iVar2 + 0x14a) <= bVar1)) {
      return;
    }
    if (2 < DebugLevel) {
      printk("AUTH - AuthTimeoutAction\n");
    }
    auth_fsm_state_transition(iVar3,0,"sta_auth_timeout_action");
    cntl_auth_assoc_conf(*(undefined4 *)(param_2 + 0x92c),2,0x10);
    return;
  }
  printk(&_LC1,0x123);
  dump_stack();
  return;
}

